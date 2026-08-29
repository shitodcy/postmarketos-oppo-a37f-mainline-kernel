#!/bin/sh
# Automatically route internet over USB when connected via RNDIS (usb0)
IFACE=$1
ACTION=$2

if [ "$IFACE" = "usb0" ] && [ "$ACTION" = "up" ]; then
    ip route add default via 172.16.42.2 || true
    echo "nameserver 8.8.8.8" > /etc/resolv.conf || true
fi
