> [!WARNING]
> This device has been tested with postmarketOS, but **its device package has not yet been added to the postmarketOS repositories**.
> This means that it cannot be selected in `pmbootstrap`.
> 
> **Status:** *booting*

<div align="center">
  <!-- Ganti URL_GAMBAR_KAMU_DISINI dengan path gambar/foto HP kamu di repositori (misal: images/neofetch.png) -->
  <img src="URL_GAMBAR_KAMU_DISINI" width="350" alt="postmarketOS booting on OPPO A37f">
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
| **Flashing** | ✅ Works |
| **USB Networking** | ❓ *Untested* |
| **Battery** | ❓ *Untested* |
| **Screen** | ✅ Works |
| **Touchscreen**| ✅ Works |
| **3D Acceleration**| ❓ *Untested* |
| **Audio** | ❓ *Untested* |
| **Camera** | ❓ *Untested* |
| **WiFi** | ❓ *Untested* |
| **Bluetooth** | ❓ *Untested* |
| **GPS** | ❓ *Untested* |
| **Calls** | ❓ *Untested* |
| **SMS** | ❓ *Untested* |
| **Mobile data**| ❓ *Untested* |
| **FDE** | ❓ *Untested* |
| **USB OTG** | ❓ *Untested* |
| **Accelerometer** | ❓ *Untested* | | |

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
   dd if=/sdcard/pmOS_root.img of=/dev/block/bootdevice/by-name/userdata bs=4096
   ```

4. **Reboot**:
   Go to Reboot -> System. 
   You will briefly see the OPPO logo, followed by the `lk2nd` log (`Jumping to kernel via monitor`), and finally the postmarketOS booting sequence with the Buffyboard on-screen keyboard!
