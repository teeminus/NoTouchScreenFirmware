# NoTouchScreenFirmware
Stripped down version of BIGTREETECH-TouchScreenFirmware which only supports ST7920 emulation (Marlin Mode). This project only uses peripheral drivers supplied by the screen manufacturer and uses it's own library to parse the ST7920 commands.

# What it does and what not
This firmware only emulates a ST7920. There is no support for touch, fonts, icons, etc. ...
I only tested the firmware with the TFT35v3. Others might work - or not. If someone wants to add support for other screens as well, this is very welcome. Don't blame me if it does not work for your display, if it burns down your house or causes any other harm.

## Supported BTT screens
Precompiled binares can be found in the [binares](binaries) folder.

| Environment                                              | Tested |
|----------------------------------------------------------|--------|
| [BIGTREE_TFT24_V1_1](binaries/BIGTREE_TFT24_V1_1)        | NO     |
| [BIGTREE_TFT28_V3_0](binaries/BIGTREE_TFT28_V3_0)        | NO     |
| [BIGTREE_TFT35_B1_V3_0](binaries/BIGTREE_TFT35_B1_V3_0)  | NO     |
| [BIGTREE_TFT35_E3_V3_0](binaries/BIGTREE_TFT35_E3_V3_0)  | YES    |
| [BIGTREE_TFT35_V3_0](binaries/BIGTREE_TFT35_V3_0)        | YES    |
| [BIGTREE_TFT43_V3_0](binaries/BIGTREE_TFT43_V3_0)        | NO     |
| [BIGTREE_TFT50_V3_0](binaries/BIGTREE_TFT50_V3_0)        | NO     |
| [BIGTREE_TFT70_V3_0](binaries/BIGTREE_TFT70_V3_0)        | NO     |
| [MKS_28_V1_0](binaries/MKS_28_V1_0)                      | NO     |
| [MKS_32_V1_4](binaries/MKS_32_V1_4)                      | NO     |
| [MKS_32_V1_4_NOBL](binaries/MKS_32_V1_4_NOBL)            | NO     |

## Installation and configuration
Check out the wiki for installation instructions and example configurations.

# Further development
This project is ment not to be BTT exclusive. To achieve this goal we need to move away from the BTT sources and on to a more flexible framework. If you want your screen to be supported, feel free to create a MR.

# Support
If you like this project and/or want to support further development you might consider to <a href="https://www.buymeacoffee.com/teeminus" target="_blank"><img src="https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png" alt="Buy Me A Coffee" style="height: 41px !important;width: 174px !important;box-shadow: 0px 3px 2px 0px rgba(190, 190, 190, 0.5) !important;-webkit-box-shadow: 0px 3px 2px 0px rgba(190, 190, 190, 0.5) !important;" ></a> or [![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/L3L03JDC5)
