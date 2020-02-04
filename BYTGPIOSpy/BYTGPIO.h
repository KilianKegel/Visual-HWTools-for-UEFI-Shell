/*!
@copyright

    Copyright (c) 2020, Kilian Kegel. All rights reserved.
    This program and the accompanying materials are licensed and made 
    available under the terms and conditions of the BSD License
    which accompanies this distribution.  The full text of the license
    may be found at

    http://opensource.org/licenses/bsd-license.php

    THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
    WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

@file 
    BYTGPIO.h

@brief 
    project specific header file
@todo
*/
#ifndef _BAYTRAIL_GPIO_H_
#define _BAYTRAIL_GPIO_H_

typedef union _BAYTRAIL_GPIO_CONFIG {
    unsigned reg;
    struct {
        unsigned func_pin_mux : 3;      // 0:2
        unsigned RSVD0 : 4;             // 6:3
        unsigned pull_assign : 2;       // 8:7
        unsigned pull_str : 2;          // 10:9
        unsigned bypass_flop : 1;       // 11
        unsigned RSVD1 : 1;             // 12
        unsigned ihysctl : 2;           // 14:13
        unsigned RSVD2 : 1;             // 15
        unsigned fast_clkgate : 1;      // 16
        unsigned slow_clkgate : 1;      // 17
        unsigned filter_slow : 1;       // 18
        unsigned filter_en : 1;         // 19
        unsigned debounce : 1;          // 20
        unsigned RSVD3 : 2;             // 22:21
        unsigned RSVD4 : 1;             // 23
        unsigned gd_level : 1;          // 24
        unsigned gd_tpe : 1;            // 25
        unsigned gd_tne : 1;            // 26
        unsigned direct_irq_en : 1;     // 27
        unsigned RSVD5 : 1;             // 28
        unsigned disable_second_mask : 1;// 29
        unsigned RSVD6 : 1;             // 30
        unsigned RSVD7 : 1;             // 31
    }bit;
}BAYTRAIL_GPIO_CONFIG;

typedef union _BAYTRAIL_GPIO_MPX {
    unsigned reg;
    struct {
        unsigned dll_std_mux : 5;       // 4:0
        unsigned dll_hgh_mux : 5;       // 9:5
        unsigned dll_ddr_mux : 5;       // 14:10
        unsigned dll_cf_od : 1;         // 15
        unsigned RSVD : 16;             // 31:16
    }bit;
}BAYTRAIL_GPIO_MPX;

typedef union _BAYTRAIL_GPIO_VALUE {
    unsigned reg;
    struct {
        unsigned pad_val : 1;           // 0
        unsigned ioutenb : 1;           // 1
        unsigned iinenb : 1;            // 2
        unsigned RSVD : 29;             // 31:3
    }bit;
}BAYTRAIL_GPIO_VALUE;

typedef union _BAYTRAIL_GPIO_TEST {
    unsigned reg;
    struct {
        unsigned RSVD0 : 10;            // 9:0
        unsigned bscan_bypass : 1;      // 1
        unsigned RSVD1 : 21;            // 31:11
    }bit;
}BAYTRAIL_GPIO_TEST;

typedef struct _BAYTRAIL_GPIO {
    BAYTRAIL_GPIO_CONFIG cfg;
    BAYTRAIL_GPIO_MPX    mpx;
    BAYTRAIL_GPIO_VALUE  val;
    BAYTRAIL_GPIO_TEST   tst;
}BAYTRAIL_GPIO;



typedef struct _GPIOID2NAME {
    int nGpioOfs;
    char *szGpioName;
}GPIOID2NAME;

//
// PCU iLB GPIO S0 Memory Addressed Registers
//
#define /*Uart1 Rts B Pad Cfg           */uart1_rts_b          0x0000
#define /*Uart1 Txd Pad Cfg             */uart1_txd            0x0010
#define /*Uart1 Rxd Pad Cfg             */uart1_rxd            0x0020
#define /*I2c Nfc Scl Pad Cfg           */i2c_nfc_scl          0x0030
#define /*Uart1 Cts B Pad Cfg           */uart1_cts_b          0x0040
#define /*I2c Nfc Sda Pad Cfg           */i2c_nfc_sda          0x0050
#define /*Uart2 Rxd Pad Cfg             */uart2_rxd            0x0060
#define /*Uart2 Txd Pad Cfg             */uart2_txd            0x0070
#define /*Uart2 Cts B Pad Cfg           */uart2_cts_b          0x0080
#define /*Uart2 Rts B Pad Cfg           */uart2_rts_b          0x0090
#define /*Pwm0 Pad Cfg                  */pwm0                 0x00A0
#define /*Pwm1 Pad Cfg                  */pwm1                 0x00B0
#define /*Gp Ssp 2 Fs Pad Cfg           */gp_ssp_2_fs          0x00C0
#define /*Gp Ssp 2 Clk Pad Cfg          */gp_ssp_2_clk         0x00D0
#define /*Gp Ssp 2 Txd Pad Cfg          */gp_ssp_2_txd         0x00E0
#define /*Gp Ssp 2 Rxd Pad Cfg          */gp_ssp_2_rxd         0x00F0
#define /*Spi1 Clk Pad Cfg              */spi1_clk             0x0100
#define /*Spi1 Cs0 B Pad Cfg            */spi1_cs0_b           0x0110
#define /*Spi1 Miso Pad Cfg             */spi1_miso            0x0120
#define /*Spi1 Mosi Pad Cfg             */spi1_mosi            0x0130
#define /*I2c5 Scl Pad Cfg              */i2c5_scl             0x0140
#define /*I2c5 Sda Pad Cfg              */i2c5_sda             0x0150
#define /*I2c6 Scl Pad Cfg              */i2c6_scl             0x0160
#define /*I2c4 Scl Pad Cfg              */i2c4_scl             0x0170
#define /*I2c6 Sda Pad Cfg              */i2c6_sda             0x0180
#define /*I2c3 Sda Pad Cfg              */i2c3_sda             0x0190
#define /*I2c4 Sda Pad Cfg              */i2c4_sda             0x01A0
#define /*I2c2 Scl Pad Cfg              */i2c2_scl             0x01B0
#define /*I2c3 Scl Pad Cfg              */i2c3_scl             0x01C0
#define /*I2c2 Sda Pad Cfg              */i2c2_sda             0x01D0
#define /*I2c1 Scl Pad Cfg              */i2c1_scl             0x01E0
#define /*I2c1 Sda Pad Cfg              */i2c1_sda             0x01F0
#define /*I2c0 Scl Pad Cfg              */i2c0_scl             0x0200
#define /*I2c0 Sda Pad Cfg              */i2c0_sda             0x0210
#define /*Hda Rstb Pad Cfg              */hda_rstb             0x0220
#define /*Hda Sdi1 Pad Cfg              */hda_sdi1             0x0230
#define /*Hda Clk Pad Cfg               */hda_clk              0x0240
#define /*Hda Sync Pad Cfg              */hda_sync             0x0250
#define /*Hda Sdo Pad Cfg               */hda_sdo              0x0260
#define /*Hda Sdi0 Pad Cfg              */hda_sdi0             0x0270
#define /*Hda Dockrstb Pad Cfg          */hda_dockrstb         0x0280
#define /*Sdmmc3 D1 Pad Cfg             */sdmmc3_d1            0x0290
#define /*Sdmmc3 D3 Pad Cfg             */sdmmc3_d3            0x02A0
#define /*Sdmmc3 Clk Pad Cfg            */sdmmc3_clk           0x02B0
#define /*Sdmmc3 Cmd Pad Cfg            */sdmmc3_cmd           0x02C0
#define /*Sdmmc3 D2 Pad Cfg             */sdmmc3_d2            0x02D0
#define /*Sdmmc3 D0 Pad Cfg             */sdmmc3_d0            0x02E0
#define /*Sdmmc2 D1 Pad Cfg             */sdmmc2_d1            0x02F0
#define /*Sdmmc2 Cmd Pad Cfg            */sdmmc2_cmd           0x0300
#define /*Sdmmc2 D3 Cd B Pad Cfg        */sdmmc2_d3_cd_b       0x0310
#define /*Sdmmc2 Clk Pad Cfg            */sdmmc2_clk           0x0320
#define /*Mmc1 Reset B Pad Cfg          */mmc1_reset_b         0x0330
#define /*Sdmmc2 D2 Pad Cfg             */sdmmc2_d2            0x0340
#define /*Sdmmc2 D0 Pad Cfg             */sdmmc2_d0            0x0350
#define /*Sdmmc1 D3 Cd B Pad Cfg        */sdmmc1_d3_cd_b       0x0360
#define /*Mmc1 D6 Pad Cfg               */mmc1_d6              0x0370
#define /*Mmc1 D4 Sd We Pad Cfg         */mmc1_d4_sd_we        0x0380
#define /*Sdmmc1 Cmd Pad Cfg            */sdmmc1_cmd           0x0390
#define /*Sdmmc3 Cd B Pad Cfg           */sdmmc3_cd_b          0x03A0
#define /*Sdmmc1 D2 Pad Cfg              */sdmmc1_d2           0x03B0
#define /*Mmc1 D5 Pad Cfg                */mmc1_d5             0x03C0
#define /*Sdmmc1 D0 Pad Cfg              */sdmmc1_d0           0x03D0
#define /*Sdmmc1 Clk Pad Cfg             */sdmmc1_clk          0x03E0
#define /*Mmc1 D7 Pad Cfg                */mmc1_d7             0x03F0
#define /*Sdmmc1 D1 Pad Cfg              */sdmmc1_d1           0x0400
#define /*Lpc Clkout1 Pad Cfg            */lpc_clkout1         0x0410
#define /*Lpc Ad3 Pad Cfg                */lpc_ad3             0x0420
#define /*Lpc Ad2 Pad Cfg                */lpc_ad2             0x0430
#define /*Lpc Ad1 Pad Cfg                */lpc_ad1             0x0440
#define /*Lpc Frameb Pad Cfg             */lpc_frameb          0x0450
#define /*Lpc Ad0 Pad Cfg                */lpc_ad0             0x0460
#define /*Lpc Clkout0 Pad Cfg            */lpc_clkout0         0x0470
#define /*Lpc Clkrunb Pad Cfg            */lpc_clkrunb         0x0480
#define /*Hv Crt Ddc Clk Pad Cfg         */hv_crt_ddc_clk      0x0490
#define /*Hv Crt Vsync Pad Cfg           */hv_crt_vsync        0x04A0
#define /*Hv Crt Hsync Pad Cfg           */hv_crt_hsync        0x04B0
#define /*Hv Crt Ddc Data Pad Cfg        */hv_crt_ddc_data     0x04C0
#define /*Mhsi Acdata Pad Cfg            */mhsi_acdata         0x04D0
#define /*Mhsi Acwake Pad Cfg            */mhsi_acwake         0x04E0
#define /*Mhsi Acflag Pad Cfg            */mhsi_acflag         0x04F0
#define /*Mhsi Caflag Pad Cfg            */mhsi_caflag         0x0500
#define /*Mhsi Cadata Pad Cfg            */mhsi_cadata         0x0510
#define /*Mhsi Caready Pad Cfg           */mhsi_caready        0x0520
#define /*Mhsi Acready Pad Cfg           */mhsi_acready        0x0530
#define /*Hda Dockenb Pad Cfg            */hda_dockenb         0x0540
#define /*Sata Gp0 Pad Cfg               */sata_gp0            0x0550
#define /*Ilb Serirq Pad Cfg             */ilb_serirq          0x0560
#define /*Plt Clk1 Pad Cfg               */plt_clk1            0x0570
#define /*Smb Clk Pad Cfg                */smb_clk             0x0580
#define /*Sata Gp1 Pad Cfg               */sata_gp1            0x0590
#define /*Smb Data Pad Cfg               */smb_data            0x05A0
#define /*Plt Clk2 Pad Cfg               */plt_clk2            0x05B0
#define /*Smb Alertb Pad Cfg             */smb_alertb          0x05C0
#define /*Sata Ledn Pad Cfg              */sata_ledn           0x05D0
#define /*Pmu Resetbutton B Pad Cfg      */pmu_resetbutton_b   0x05E0
#define /*Sdmmc3 1p8 En Pad Cfg          */sdmmc3_1p8_en       0x05F0
#define /*Pcie Clkreq0b Pad Cfg          */pcie_clkreq0b       0x0600
#define /*Plt Clk4 Pad Cfg               */plt_clk4            0x0610
#define /*Pcie Clkreq3b Pad Cfg          */pcie_clkreq3b       0x0620
#define /*Pcie Clkreq1b Pad Cfg          */pcie_clkreq1b       0x0630
#define /*Plt Clk5 Pad Cfg               */plt_clk5            0x0640
#define /*Pcie Clkreq4b Pad Cfg          */pcie_clkreq4b       0x0650
#define /*Pcie Clkreq2b Pad Cfg          */pcie_clkreq2b       0x0660
#define /*Spkr Pad Cfg                   */spkr                0x0670
#define /*Plt Clk3 Pad Cfg               */plt_clk3            0x0680
#define /*Sdmmc3 Pwr En B Pad Cfg        */sdmmc3_pwr_en_b     0x0690
#define /*Plt Clk0 Pad Cfg               */plt_clk0            0x06A0
#define /*Vgpio 0 Pad Cfg                */vgpio_0             0x06B0
#define /*Vgpio 1 Pad Cfg                */vgpio_1             0x06C0
#define /*Vgpio 2 Pad Cfg                */vgpio_2             0x06D0
#define /*Vgpio 3 Pad Cfg                */vgpio_3             0x06E0
#define /*Vgpio 4 Pad Cfg                */vgpio_4             0x06F0
#define /*Vgpio 5 Pad Cfg                */vgpio_5             0x0700
#define /*Vgpio 6 Pad Cfg                */vgpio_6             0x0710
#define /*Vgpio 7 Pad Cfg                */vgpio_7             0x0720
#define /*Vgpio 8 Pad Cfg                */vgpio_8             0x0730
#define /*Vgpio 9 Pad Cfg                */vgpio_9             0x0740
#define /*Vgpio 10 Pad Cfg               */vgpio_10            0x0750
#define /*Vgpio 11 Pad Cfg               */vgpio_11            0x0760
#define /*Vgpio 12 Pad Cfg               */vgpio_12            0x0770
#define /*Vgpio 13 Pad Cfg               */vgpio_13            0x0780
#define /*Vgpio 14 Pad Cfg               */vgpio_14            0x0790
#define /*Vgpio 15 Pad Cfg               */vgpio_15            0x07A0
#define /*Vgpio 16 Pad Cfg               */vgpio_16            0x07B0
#define /*Vgpio 17 Pad Cfg               */vgpio_17            0x07C0
#define /*Vgpio 18 Pad Cfg               */vgpio_18            0x07D0
#define /*Vgpio 19 Pad Cfg               */vgpio_19            0x07E0
#define /*Vgpio 20 Pad Cfg               */vgpio_20            0x07F0
//
// PCU iLB GPIO S5 Memory Addressed Registers
//
#define /*Usb Oc1 B Pad Cfg           */usb_oc1_b           0x2000
#define /*Pmu Wake B Pad Cfg          */pmu_wake_b          0x2010
#define /*Spi Cs1 B Pad Cfg           */spi_cs1_b           0x2020
#define /*Spi Cs0 B Pad Cfg           */spi_cs0_b           0x2030
#define /*Spi Clk Pad Cfg             */spi_clk             0x2040
#define /*Spi Mosi Pad Cfg            */spi_mosi            0x2050
#define /*Spi Miso Pad Cfg            */spi_miso            0x2060
#define /*Suspwrdnack Pad Cfg         */suspwrdnack         0x2070
#define /*Pmu Pwrbtn B Pad Cfg        */pmu_pwrbtn_b        0x2080
#define /*Pmu Batlow B Pad Cfg        */pmu_batlow_b        0x2090
#define /*Pmu Wake Lan B Pad Cfg      */pmu_wake_lan_b      0x20A0
#define /*Pmu Susclk Pad Cfg          */pmu_susclk          0x20B0
#define /*Usb Oc0 B Pad Cfg           */usb_oc0_b           0x20C0
#define /*Pmu Slp S3 B Pad Cfg        */pmu_slp_s3_b        0x20D0
#define /*Pmu Ac Present Pad Cfg      */pmu_ac_present      0x20E0
#define /*Pmu Slp S4 B Pad Cfg        */pmu_slp_s4_b        0x20F0
#define /*Pmu Pltrst B Pad Cfg        */pmu_pltrst_b        0x2100
#define /*Pmu Slp Lan B Pad Cfg       */pmu_slp_lan_b       0x2110
#define /*Sec Gpio Sus10 Pad Cfg      */sec_gpio_sus10      0x2120
#define /*Sus Stat B Pad Cfg          */sus_stat_b          0x2130
#define /*Pmu Slp S0ix B Pad Cfg      */pmu_slp_s0ix_b      0x2140
#define /*Gpio Dfx5 Pad Cfg           */gpio_dfx5           0x2150
#define /*Gpio Dfx4 Pad Cfg           */gpio_dfx4           0x2160
#define /*Gpio Dfx0 Pad Cfg           */gpio_dfx0           0x2170
#define /*Gpio Dfx6 Pad Cfg           */gpio_dfx6           0x2180
#define /*Gpio Dfx7 Pad Cfg           */gpio_dfx7           0x2190
#define /*Gpio Dfx8 Pad Cfg           */gpio_dfx8           0x21A0
#define /*Gpio Dfx3 Pad Cfg           */gpio_dfx3           0x21B0
#define /*Gpio Dfx2 Pad Cfg           */gpio_dfx2           0x21C0
#define /*Gpio Sus0 Pad Cfg           */gpio_sus0           0x21D0
#define /*Gpio Sus2 Pad Cfg           */gpio_sus2           0x21E0
#define /*Gpio Sus3 Pad Cfg           */gpio_sus3           0x21F0
#define /*Gpio Sus4 Pad Cfg           */gpio_sus4           0x2200
#define /*Gpio Sus1 Pad Cfg           */gpio_sus1           0x2210
#define /*Gpio Sus5 Pad Cfg           */gpio_sus5           0x2220
#define /*Gpio Sus7 Pad Cfg           */gpio_sus7           0x2230
#define /*Gpio Sus6 Pad Cfg           */gpio_sus6           0x2240
#define /*Sec Gpio Sus9 Pad Cfg       */sec_gpio_sus9       0x2250
#define /*Sec Gpio Sus8 Pad Cfg       */sec_gpio_sus8       0x2260
#define /*Gpio Dfx1 Pad Cfg           */gpio_dfx1           0x2270
#define /*Usb Ulpi 0 Refclk Pad Cfg   */usb_ulpi_0_refclk   0x2280
#define /*Tck Pad Cfg                 */tck                 0x2290
#define /*Trst B Pad Cfg              */trst_b              0x22A0
#define /*Tdi Pad Cfg                 */tdi                 0x22B0
#define /*Tms Pad Cfg                 */tms                 0x22C0
#define /*Cx Prdy B Pad Cfg           */cx_prdy_b           0x22D0
#define /*Cx Preq B Pad Cfg           */cx_preq_b           0x22E0
#define /*Tdo Pad Cfg                 */tdo                 0x22F0
#define /*Usb Ulpi 0 Data4 Pad Cfg    */usb_ulpi_0_data4    0x2300
#define /*Usb Ulpi 0 Data2 Pad Cfg    */usb_ulpi_0_data2    0x2310
#define /*Usb Ulpi 0 Data6 Pad Cfg    */usb_ulpi_0_data6    0x2320
#define /*Usb Ulpi 0 Clk Pad Cfg      */usb_ulpi_0_clk      0x2330
#define /*Usb Ulpi 0 Dir Pad Cfg      */usb_ulpi_0_dir      0x2340
#define /*Usb Ulpi 0 Nxt Pad Cfg      */usb_ulpi_0_nxt      0x2350
#define /*Usb Ulpi 0 Data1 Pad Cfg    */usb_ulpi_0_data1    0x2360
#define /*Usb Ulpi 0 Data3 Pad Cfg    */usb_ulpi_0_data3    0x2370
#define /*Usb Ulpi 0 Data0 Pad Cfg    */usb_ulpi_0_data0    0x2380
#define /*Usb Ulpi 0 Data5 Pad Cfg    */usb_ulpi_0_data5    0x2390
#define /*Usb Ulpi 0 Data7 Pad Cfg    */usb_ulpi_0_data7    0x23A0
#define /*Usb Ulpi 0 Stp Pad Cfg      */usb_ulpi_0_stp      0x23B0

#endif//_BAYTRAIL_GPIO_H_
