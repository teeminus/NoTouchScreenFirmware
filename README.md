# NoTouchScreenFirmware
Stripped down version of BIGTREETECH-TouchScreenFirmware which only supports ST7920 emulation (Marlin Mode)

# What it does and what not
This firmware only emulates a ST7920. There is no support for touch, fonts, icons, etc. ...
I only tested the firmware with the TFT35v3. Others might work - or not. If someone wants to add support for other screens as well, this is very welcome. Don't blame me if it does not work for your display, if it burns down your house or causes any other harm.

## Which BTT screen is working
Precompiled binares can be found in the [binares](binaries) folder.

| Environment                                              | Compile status         | Tested |
|----------------------------------------------------------|------------------------|--------|
| [BIGTREE_TFT24_V1_1](binaries/BIGTREE_TFT24_V1_1)        | SUCCESS                | NO     |
| BIGTREE_TFT28_V1_0                                       | FAILED (No ST7920_SPI) | -      |
| [BIGTREE_TFT28_V3_0](binaries/BIGTREE_TFT28_V3_0)        | SUCCESS                | NO     |
| [BIGTREE_TFT35_B1_V3_0](binaries/BIGTREE_TFT35_B1_V3_0)  | SUCCESS                | NO     |
| [BIGTREE_TFT35_E3_V3_0](binaries/BIGTREE_TFT35_E3_V3_0)  | SUCCESS                | NO     |
| BIGTREE_TFT35_V1_0                                       | FAILED (No ST7920_SPI) | -      |
| BIGTREE_TFT35_V1_1                                       | FAILED (No ST7920_SPI) | -      |
| BIGTREE_TFT35_V1_2                                       | FAILED (No ST7920_SPI) | -      |
| BIGTREE_TFT35_V2_0                                       | FAILED (No ST7920_SPI) | -      |
| [BIGTREE_TFT35_V3_0](binaries/BIGTREE_TFT35_V3_0)        | SUCCESS                | YES    |
| [BIGTREE_TFT43_V3_0](binaries/BIGTREE_TFT43_V3_0)        | SUCCESS                | NO     |
| [BIGTREE_TFT50_V3_0](binaries/BIGTREE_TFT50_V3_0)        | SUCCESS                | NO     |
| [BIGTREE_TFT70_V3_0](binaries/BIGTREE_TFT70_V3_0)        | SUCCESS                | NO     |
| [MKS_28_V1_0](binaries/MKS_28_V1_0)                      | SUCCESS                | NO     |
| [MKS_32_V1_4](binaries/MKS_32_V1_4)                      | SUCCESS                | NO     |
| [MKS_32_V1_4_NOBL](binaries/MKS_32_V1_4_NOBL)            | SUCCESS                | NO     |
