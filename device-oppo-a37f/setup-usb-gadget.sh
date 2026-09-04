#!/bin/sh
# setup-usb-gadget.sh — Configure USB gadget for OPPO A37f (MSM8916)
#
# This script sets up USB gadget networking (RNDIS + ECM) via configfs
# so the device is visible on the host PC and can be accessed via SSH.
#
# The device will appear as a USB network adapter on the host.
# Device IP: 172.16.42.1  |  Host IP (expected): 172.16.42.2

set -e

CONFIGFS="/sys/kernel/config"
GADGET_DIR="$CONFIGFS/usb_gadget/g1"
UDC=""
IFACE="usb0"
DEVICE_IP="172.16.42.1"
DEVICE_NETMASK="255.255.255.0"

log() {
    logger -t "usb-gadget" "$1"
    echo "[usb-gadget] $1"
}

# Find the UDC (USB Device Controller)
find_udc() {
    if [ -d /sys/class/udc ]; then
        UDC=$(ls /sys/class/udc/ 2>/dev/null | head -1)
    fi
    if [ -z "$UDC" ]; then
        # MSM8916 chipidea UDC name pattern
        for u in ci_hdrc.0 ci_hdrc.1 musb-hdrc.0; do
            if [ -d "/sys/class/udc/$u" ]; then
                UDC="$u"
                break
            fi
        done
    fi
}

# Load required kernel modules
load_modules() {
    log "Loading USB gadget modules..."
    modprobe configfs 2>/dev/null || true
    modprobe libcomposite 2>/dev/null || true
    modprobe usb_f_rndis 2>/dev/null || true
    modprobe usb_f_ecm 2>/dev/null || true
    modprobe usb_f_acm 2>/dev/null || true

    # Give modules time to initialize
    sleep 1

    # Also try to probe chipidea if not yet loaded
    modprobe ci_hdrc 2>/dev/null || true
    modprobe ci_hdrc_msm 2>/dev/null || true
    modprobe phy_qcom_usb_hs 2>/dev/null || true
    modprobe ulpi 2>/dev/null || true

    sleep 1
}

# Teardown existing gadget configuration
teardown_gadget() {
    if [ -d "$GADGET_DIR" ]; then
        log "Tearing down existing gadget..."
        # Disable UDC
        echo "" > "$GADGET_DIR/UDC" 2>/dev/null || true
        # Remove function links from configs
        for link in "$GADGET_DIR"/configs/*/rndis.usb0 \
                     "$GADGET_DIR"/configs/*/ecm.usb0 \
                     "$GADGET_DIR"/configs/*/acm.GS0; do
            rm -f "$link" 2>/dev/null || true
        done
        # Remove strings
        rmdir "$GADGET_DIR"/configs/*/strings/0x409 2>/dev/null || true
        rmdir "$GADGET_DIR"/configs/*/ 2>/dev/null || true
        rmdir "$GADGET_DIR"/functions/rndis.usb0 2>/dev/null || true
        rmdir "$GADGET_DIR"/functions/ecm.usb0 2>/dev/null || true
        rmdir "$GADGET_DIR"/functions/acm.GS0 2>/dev/null || true
        rmdir "$GADGET_DIR"/strings/0x409 2>/dev/null || true
        rmdir "$GADGET_DIR" 2>/dev/null || true
    fi
}

# Setup USB gadget via configfs
setup_configfs_gadget() {
    log "Setting up USB gadget via configfs..."

    # Ensure configfs is mounted
    if ! mountpoint -q "$CONFIGFS" 2>/dev/null; then
        mount -t configfs configfs "$CONFIGFS" 2>/dev/null || true
    fi

    if [ ! -d "$CONFIGFS/usb_gadget" ]; then
        log "ERROR: configfs usb_gadget not available"
        return 1
    fi

    # Create gadget
    mkdir -p "$GADGET_DIR"

    # Set vendor/product IDs (Linux Foundation USB gadget)
    echo "0x1d6b" > "$GADGET_DIR/idVendor"   # Linux Foundation
    echo "0x0104" > "$GADGET_DIR/idProduct"   # Multifunction Composite Gadget
    echo "0x0100" > "$GADGET_DIR/bcdDevice"
    echo "0x0200" > "$GADGET_DIR/bcdUSB"

    # Enable OS descriptors for Windows RNDIS
    echo "1" > "$GADGET_DIR/os_desc/use" 2>/dev/null || true
    echo "0xcd" > "$GADGET_DIR/os_desc/b_vendor_code" 2>/dev/null || true
    echo "MSFT100" > "$GADGET_DIR/os_desc/qw_sign" 2>/dev/null || true

    # Set device strings
    mkdir -p "$GADGET_DIR/strings/0x409"
    echo "postmarketOS" > "$GADGET_DIR/strings/0x409/manufacturer"
    echo "OPPO A37f USB Network" > "$GADGET_DIR/strings/0x409/product"
    echo "pmos-oppo-a37f" > "$GADGET_DIR/strings/0x409/serialnumber"

    # Create RNDIS function (Windows compatible)
    mkdir -p "$GADGET_DIR/functions/rndis.usb0"

    # Set fixed MAC addresses for consistent networking
    echo "12:63:81:ec:de:db" > "$GADGET_DIR/functions/rndis.usb0/host_addr" 2>/dev/null || true
    echo "52:80:48:f9:15:82" > "$GADGET_DIR/functions/rndis.usb0/dev_addr" 2>/dev/null || true

    # Set OS descriptor for RNDIS (Windows auto-detection)
    if [ -d "$GADGET_DIR/functions/rndis.usb0/os_desc" ]; then
        echo "RNDIS" > "$GADGET_DIR/functions/rndis.usb0/os_desc/interface.rndis/compatible_id" 2>/dev/null || true
        echo "5162001" > "$GADGET_DIR/functions/rndis.usb0/os_desc/interface.rndis/sub_compatible_id" 2>/dev/null || true
    fi

    # Create configuration
    mkdir -p "$GADGET_DIR/configs/c.1/strings/0x409"
    echo "RNDIS network" > "$GADGET_DIR/configs/c.1/strings/0x409/configuration"
    echo "500" > "$GADGET_DIR/configs/c.1/MaxPower"

    # Link function to configuration
    ln -sf "$GADGET_DIR/functions/rndis.usb0" "$GADGET_DIR/configs/c.1/rndis.usb0"

    # Link OS descriptors
    ln -sf "$GADGET_DIR/configs/c.1" "$GADGET_DIR/os_desc/c.1" 2>/dev/null || true

    return 0
}

# Bind gadget to UDC and configure network
bind_and_configure() {
    find_udc

    if [ -z "$UDC" ]; then
        log "ERROR: No UDC found! USB controller may not be initialized."
        log "Available devices in /sys/class/udc/:"
        ls -la /sys/class/udc/ 2>&1 | while read -r line; do log "  $line"; done
        return 1
    fi

    log "Binding gadget to UDC: $UDC"
    echo "$UDC" > "$GADGET_DIR/UDC"

    # Wait for interface to appear
    local i=0
    while [ $i -lt 20 ]; do
        if ip link show "$IFACE" >/dev/null 2>&1; then
            break
        fi
        sleep 0.5
        i=$((i + 1))
    done

    if ! ip link show "$IFACE" >/dev/null 2>&1; then
        log "ERROR: Interface $IFACE did not appear after binding"
        return 1
    fi

    log "Configuring network interface $IFACE..."
    ip addr flush dev "$IFACE" 2>/dev/null || true
    ip addr add "$DEVICE_IP/24" dev "$IFACE"
    ip link set "$IFACE" up

    log "USB gadget configured successfully!"
    log "  Interface: $IFACE"
    log "  Device IP: $DEVICE_IP"
    log "  UDC: $UDC"

    # Add default route via USB host and set DNS for internet access out-of-the-box
    log "Adding default route via 172.16.42.2..."
    ip route add default via 172.16.42.2 2>/dev/null || true
    echo "nameserver 8.8.8.8" > /etc/resolv.conf

    return 0
}

# Fallback: use legacy g_ether module
fallback_g_ether() {
    log "Trying fallback: g_ether module..."

    # Remove any loaded gadget modules first
    modprobe -r g_ether 2>/dev/null || true

    modprobe g_ether \
        host_addr="12:63:81:ec:de:db" \
        dev_addr="52:80:48:f9:15:82" \
        2>/dev/null

    if [ $? -ne 0 ]; then
        log "ERROR: g_ether module failed to load"
        return 1
    fi

    sleep 2

    if ip link show "$IFACE" >/dev/null 2>&1; then
        ip addr flush dev "$IFACE" 2>/dev/null || true
        ip addr add "$DEVICE_IP/24" dev "$IFACE"
        ip link set "$IFACE" up
        log "g_ether fallback configured successfully!"
        
        # Add default route via USB host and set DNS for internet access out-of-the-box
        log "Adding default route via 172.16.42.2..."
        ip route add default via 172.16.42.2 2>/dev/null || true
        echo "nameserver 8.8.8.8" > /etc/resolv.conf
        
        return 0
    else
        log "ERROR: g_ether loaded but no interface appeared"
        return 1
    fi
}

# Start SSH server if not running
ensure_ssh() {
    if command -v sshd >/dev/null 2>&1; then
        if ! pgrep -x sshd >/dev/null 2>&1; then
            log "Starting SSH daemon..."
            # Generate host keys if needed
            for keytype in rsa ecdsa ed25519; do
                keyfile="/etc/ssh/ssh_host_${keytype}_key"
                if [ ! -f "$keyfile" ]; then
                    ssh-keygen -t "$keytype" -f "$keyfile" -N "" 2>/dev/null || true
                fi
            done
            /usr/sbin/sshd 2>/dev/null || true
        fi
    fi
}

# Main
main() {
    log "=== USB Gadget Setup for OPPO A37f (MSM8916) ==="

    # Load modules
    load_modules

    # Check if already configured
    if ip link show "$IFACE" >/dev/null 2>&1; then
        local current_ip
        current_ip=$(ip -4 addr show "$IFACE" 2>/dev/null | grep -oP 'inet \K[\d.]+' || true)
        if [ "$current_ip" = "$DEVICE_IP" ]; then
            log "USB gadget already configured ($IFACE: $current_ip)"
            ensure_ssh
            return 0
        fi
    fi

    # Try configfs first
    teardown_gadget
    if setup_configfs_gadget; then
        if bind_and_configure; then
            ensure_ssh
            log "=== USB gadget setup complete (configfs) ==="
            return 0
        fi
    fi

    # Configfs failed, try g_ether fallback
    teardown_gadget
    if fallback_g_ether; then
        ensure_ssh
        log "=== USB gadget setup complete (g_ether fallback) ==="
        return 0
    fi

    log "=== USB gadget setup FAILED ==="
    log "Dumping diagnostics..."
    log "UDC devices:"
    ls -la /sys/class/udc/ 2>&1 | while read -r line; do log "  $line"; done
    log "USB related dmesg:"
    dmesg | grep -i "usb\|gadget\|ci_hdrc\|chipidea\|msm_hsusb" | tail -20 | while read -r line; do log "  $line"; done

    return 1
}

case "${1:-start}" in
    start)
        main
        ;;
    stop)
        teardown_gadget
        ip addr flush dev "$IFACE" 2>/dev/null || true
        ip link set "$IFACE" down 2>/dev/null || true
        log "USB gadget stopped"
        ;;
    restart)
        "$0" stop
        sleep 1
        "$0" start
        ;;
    status)
        if ip link show "$IFACE" >/dev/null 2>&1; then
            echo "USB gadget is UP"
            ip addr show "$IFACE"
            if [ -f "$GADGET_DIR/UDC" ]; then
                echo "UDC: $(cat "$GADGET_DIR/UDC")"
            fi
        else
            echo "USB gadget is DOWN"
        fi
        ;;
    *)
        echo "Usage: $0 {start|stop|restart|status}"
        exit 1
        ;;
esac
