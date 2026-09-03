> [!WARNING]
> This device has been tested with postmarketOS, but **its device package has not yet been added to the postmarketOS repositories**.
> This means that it cannot be selected in `pmbootstrap`.
> 
> **Status:** *booting*

<div align="center">
  <img src="https://github.com/shitodcy/pmos/blob/main/assets/neofetch.jpeg" width="350" alt="postmarketOS booting on OPPO A37f">
  <p><i>Neofetch</i></p>
</div>

##  Device Specifications: Oppo A37

| | |
| :--- | :--- |
| **Manufacturer** | Oppo |
| **Name** | A37 |
| **Codename** | `oppo-a37f` |
| **Released** | 2016 |

### Hardware
| | |
| :--- | :--- |
| **Chipset** | Qualcomm Snapdragon 410 (MSM8916) |
| **CPU** | Quad-core 1.2 Ghz Cortex-A53 |
| **GPU** | Adreno 306 |
| **Display** | 720x1280 IPS LCD |
| **Storage** | 16 GB |
| **Memory** | 2 GB |
| **Architecture** | `aarch64` |

### Software & postmarketOS
| | |
| :--- | :--- |
| **Original software** | Android 5.1.1 |
| **Extended version** | Android |
| **Category** | testing |
| **Mainline** | yes |
| **pmOS kernel** | 6.12.1-msm8916 |

## Features Support Matrix

| Feature | Status |
| :--- | :--- | 
| **Flashing** | ![](https://img.shields.io/badge/Works-success) |
| **USB Networking** | ![](https://img.shields.io/badge/Works-success) |
| **Battery** | ![](https://img.shields.io/badge/Works-success) |
| **Screen** | ![](https://img.shields.io/badge/Works-success) |
| **Touchscreen**| ![](https://img.shields.io/badge/Works-success) |
| **3D Acceleration**| *Untested* |
| **Audio** | ![](https://img.shields.io/badge/Works-success) |
| **Camera** | ![](https://img.shields.io/badge/Partial-orange) |
| **WiFi** | ![](https://img.shields.io/badge/Works-success) |
| **Bluetooth** | ![](https://img.shields.io/badge/Works-success) |
| **GPS** | *Untested* |
| **Calls** | *Untested* |
| **SMS** | *Untested* |
| **Mobile data**| ![](https://img.shields.io/badge/Partial-orange) |
| **FDE** | *Untested* |
| **USB OTG** | ![](https://img.shields.io/badge/Works-success) |
| **Accelerometer** | ![](https://img.shields.io/badge/Works-success) |
---

# postmarketOS on OPPO A37f (MSM8916)

This repository contains the working bootloader (`lk2nd`), kernel files, and a TWRP-flashable installer to successfully boot postmarketOS on the OPPO A37f (Snapdragon 410 / MSM8916).

## The Journey & Technical Findings

Porting postmarketOS to the OPPO A37f was challenging due to several strict security measures and firmware quirks:

1. **Bootloader Signature Verification (`aboot`)**:
   OPPO enforces signature verification on the `boot` partition. Normally, this rejects any non-stock kernel. However, by using a specialized build of `lk2nd` (acting as a secondary bootloader), we are able to hijack the boot process just before the stock `aboot` panics, allowing us to load unsigned Linux kernels.
   
2. **`lk2nd` Ext2 Bug / Kernel Panics**:
   While `lk2nd` can parse `ext2` filesystems to find `extlinux.conf`, we discovered that it **panics** when trying to read modern `ext2` filesystems created by newer versions of `mke2fs` (such as the one used internally by `pmbootstrap`). The solution was to format the `/boot` partition (`system` / `mmcblk0p24`) using **TWRP's legacy `mke2fs` (v1.43.3)**, which creates a simpler `ext2` structure that `lk2nd` can parse without crashing.

3. **Display Initialization (`cont-splash`)**:
   Attempting to force `lk2nd` to initialize the BOE ILI9881C panel directly resulted in a kernel panic because `lk2nd`'s PMIC WLED driver does not support the I2C-based TI LM3630 backlight IC used in the A37f. The solution was to rely on **`cont-splash`**. We let OPPO's stock `aboot` initialize the display, and `lk2nd` simply draws to the existing framebuffer without touching the panel driver.

4. **Early Kernel Panic (`nomodeset` & `console=tty0`)**:
   Initially, the screen would glitch out and freeze on `Jumping to kernel via monitor`. This was due to two things:
   - `pmbootstrap` injected `nomodeset` into `extlinux.conf`, disabling the DRM driver and leaving the screen completely dead.
   - The kernel was outputting logs exclusively to the serial console (`ttyMSM0`). By adding `console=tty0`, the Linux boot logs were forced onto the screen, and we removed `nomodeset` to allow the DRM driver to load properly.

5. **USB Networking & `sudo` Permissions**:
   - The device's battery charger driver (`bq24190`) was missing from the kernel configuration, which caused the Battery Management System (`pm8916-bms`) to hang indefinitely in deferred probing. As a result, the USB controller could never detect the cable connection (VBUS).
   - To force USB enumeration, we injected a hardware hack into the Device Tree (DTB) that repurposed the physical Volume Up button GPIO (`<&msmgpio 107 (GPIO_ACTIVE_HIGH)>`) into a `dummy_extcon` (virtual VBUS trigger).
   - During the overlay injection, using `cp -a` accidentally inherited the host user's ownership (1000:1000) into the rootfs `/etc` directory. This triggered a fatal `sudo: invalid configuration: /etc must be owned by root` lockout. It was resolved by injecting a `chown -R 0:0 /sysroot/etc` step directly into the `initramfs` hook to repair permissions before boot.
   - **How to apply the manual fix:** In case of a fresh installation, the `system` partition's default DTB and initramfs will overwrite our hacks. To re-apply the USB and `sudo` fixes, boot the device into TWRP and run the following ADB commands from your host machine to manually inject the patched files into the boot partition:
     ```bash
     adb shell "mkdir -p /mnt/pmos_boot && mount -t ext2 /dev/block/bootdevice/by-name/system /mnt/pmos_boot" && \
     adb push /tmp/msm8916-oppo-a37-fixed-v3.dtb /mnt/pmos_boot/msm8916-oppo-a37.dtb && \
     adb push /tmp/initramfs_fixed_v2 /mnt/pmos_boot/initramfs && \
     adb shell "sync && umount /mnt/pmos_boot"
     ```

6. **WiFi Hotspot & MAC Randomization**:
   - NetworkManager defaults to MAC Address Randomization (assigning MACs starting with `02:...`) when connecting to networks.
   - However, many mobile hotspots (Android/iOS) actively block or ignore DHCP requests from randomized MACs, resulting in timeouts (`IP configuration could not be reserved`).
   - The fix was to enforce the hardware's permanent MAC address by creating `/etc/NetworkManager/conf.d/disable-random-mac.conf` with `wifi.scan-rand-mac-address=no` and `wifi.cloned-mac-address=permanent`.

7. **USB Extcon Dependency Cycle & Black Screen**:
   - We faced a persistent bug where the USB gadget driver failed to load, leading to a black screen after the kernel jump and a `deferred probe pending` loop for the USB controller (`78d9000.usb`).
   - This was diagnosed as an extcon dependency cycle. The fix involved correcting our `dummy_extcon` driver initialization in the DTB. We changed the `compatible` string to `"linux,extcon-usb-gpio"` (instead of just `"extcon-usb-gpio"`) and updated the property to `vbus-gpios` (from the legacy `vbus-gpio`). This successfully initialized the UDC, breaking the cycle and enabling the `172.16.42.1` USB network tethering.

8. **Missing WiFi Firmware (`linux-firmware-qcom`)**:
   - The original port lacked the proprietary firmware required by the WCN3620 chip to initialize Wi-Fi (`wlan0`). When users generated a fresh rootfs via `pmbootstrap install`, Wi-Fi would silently fail.
   - We injected the `linux-firmware-qcom` package into the `device-oppo-a37f`'s `APKBUILD` dependencies to permanently bake the proprietary firmware into the `pmOS_root.img`. This ensures `wlan0` is always available out-of-the-box.


## Installation Instructions

We have provided a fully automated TWRP installer zip that handles the complex formatting and placement of files.

### Prerequisites
- Unlocked bootloader or EDL-bypassed OPPO A37f.
- TWRP Custom Recovery installed.
- The `pmos-oppo-a37f-installer.zip` and `pmOS_root.img` from this repository.

### Step-by-Step Guide

1. **Transfer Files**:
   Copy `pmos-oppo-a37f-installer.zip` and `pmOS_root.img` to an SD Card or push them to the device via ADB.
   
2. **Flash the Bootloader & Kernel (TWRP)**:
   In TWRP, go to **Install**, select `pmos-oppo-a37f-installer.zip`, and flash it.
   *What this script does:*
   - Flashes the working `lk2nd` to the `boot` partition (`mmcblk0p22`).
   - Formats the `system` partition (`mmcblk0p24`) to legacy `ext2` using TWRP's safe tools.
   - Installs the postmarketOS kernel (`vmlinuz`), `initramfs`, and Device Tree (`dtb`).
   - Dynamically injects the correct UUIDs into `extlinux.conf`.

3. **Flash the Root Filesystem (`pmOS_root.img`)**:
   In TWRP, you must overwrite the `userdata` partition with the postmarketOS root filesystem.
   Using ADB shell (or TWRP terminal):
   ```bash
   adb shell "dd if=/sdcard/pmOS_root.img of=/dev/block/bootdevice/by-name/userdata bs=4096"
   adb shell twrp install /sdcard/pmos-oppo-a37f-installer.zip
   ```

4. **Reboot**:
   Go to Reboot -> System. 
   You will briefly see the OPPO logo, followed by the `lk2nd` log (`Jumping to kernel via monitor`), and finally the postmarketOS booting sequence with the Buffyboard on-screen keyboard!

## Build from Source (pmbootstrap)

If you want to build the postmarketOS images from source yourself:

1. **Clone this repository**
   ```bash
   git clone https://github.com/shitodcy/pmos.git
   cd pmos
   ```

2. **Initialize pmbootstrap**
   ```bash
   pmbootstrap init
   ```
   *(Select any random device for now, we will re-initialize later).*

3. **Copy Porting Files**
   Copy the device and kernel packages into your local `pmaports` tree:
   ```bash
   cp -r device-oppo-a37f ~/.local/var/pmbootstrap/cache_git/pmaports/device/testing/
   cp -r linux-postmarketos-qcom-msm8916 ~/.local/var/pmbootstrap/cache_git/pmaports/device/testing/
   ```

4. **Update Checksums**
   ```bash
   pmbootstrap checksum device-oppo-a37f linux-postmarketos-qcom-msm8916
   ```

5. **Select Device**
   Run init again and select `oppo` -> `a37f` (and choose your preferred UI):
   ```bash
   pmbootstrap init
   ```

6. **Build and Export**
   ```bash
   pmbootstrap build device-oppo-a37f
   pmbootstrap install --split
   pmbootstrap export
   ```

7. **Create TWRP Installer**
   ```bash
   cd twrp_installer
   cp /tmp/postmarketOS-export/vmlinuz pmos_boot/
   cp /tmp/postmarketOS-export/initramfs pmos_boot/
   cp /tmp/postmarketOS-export/dtbs/msm8916-oppo-a37.dtb pmos_boot/
   
   zip -r9 ../pmos-oppo-a37f-installer.zip META-INF lk2nd.img pmos_boot
   ```
   You can now flash `pmos-oppo-a37f-installer.zip` and `/tmp/postmarketOS-export/oppo-a37f-root.img` as described in the Installation Instructions above.

