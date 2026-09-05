> [!WARNING]
> This device has been tested with postmarketOS, but **its device package has not yet been added to the postmarketOS repositories**.
> This means that it cannot be selected in `pmbootstrap`.
> 
> **Status:** *booting*

<div align="center">
  <table>
  <tr>
    <td align="center">
      <img src="https://github.com/shitodcy/pmos/blob/main/assets/neofetch.jpeg" width="350" alt="postmarketOS booting on OPPO A37f">
      <p>TTY</p>
    </td>
    <td align="center">
      <img src="https://github.com/shitodcy/pmos/blob/main/assets/phosh.png" width="350" alt="postmarketOS booting on OPPO A37f">
      <p>Phosh</p>
    </td>
  </tr>
</table>
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
| **Audio** | ![](https://img.shields.io/badge/Works-success) |
| **Camera** | *Broken* |
| **WiFi** | ![](https://img.shields.io/badge/Partial-orange) |
| **Bluetooth** | ![](https://img.shields.io/badge/Works-success) |
| **GPS** | *Untested* |
| **Calls** | *Untested* |
| **SMS** | ![](https://img.shields.io/badge/Works-success) |
| **Mobile data**| ![](https://img.shields.io/badge/Works-success) |
| **FDE** | *Untested* |
| **USB OTG** | ![](https://img.shields.io/badge/Works-success) |
| **Accelerometer** | ![](https://img.shields.io/badge/Works-success) |
| **Proximity sensor** | ![](https://img.shields.io/badge/Works-success) |
| **Light sensor** | ![](https://img.shields.io/badge/Works-success) |
| **Flashlight** | ![](https://img.shields.io/badge/Works-success) |
---

# postmarketOS on OPPO A37f (MSM8916)

This repository contains the working bootloader (`lk2nd`), kernel files, and a TWRP-flashable installer to successfully boot postmarketOS on the OPPO A37f (Snapdragon 410 / MSM8916).

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

> [!IMPORTANT]
> If you execute the command below and a reboot occurs, immediately return and run the command again.

   ```bash
   adb push pmos-oppo-a37f-installer.zip /sdcard
   cat pmOS_root.img | adb shell "dd of=/dev/block/bootdevice/by-name/userdata bs=1048576"
   adb shell twrp install /sdcard/pmos-oppo-a37f-installer.zip
   ```

4. **Reboot**:
   Go to Reboot -> System. 
   You will briefly see the OPPO logo, followed by the `lk2nd` log (`Jumping to kernel via monitor`), and finally the postmarketOS booting sequence with the Buffyboard on-screen keyboard!
   
    **Login Credentials (if required):**
    | | |
    | :--- | :--- | 
    | **Username** | user |
    | **Password** | 147147|

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

