/*!
@copyright

    Copyright (c) 2019, MinnowWare. All rights reserved.
    This program and the accompanying materials are licensed and made 
    available under the terms and conditions of the BSD License
    which accompanies this distribution.  The full text of the license
    may be found at

    http://opensource.org/licenses/bsd-license.php

    THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
    WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

@file main.c

@brief 
    This module implements the GPIOSpy main program
@todo
    - add GPIO write feature

@mainpage
    GPIOSpy for BayTrail(BYT)

@section intro_sec Introduction
    This program is used to view and manipulate GPIO on\n
    the Intel BayTrail(BYT) - Platform.\n

@subsection ref_sec References
    @note <a href="https://www.intel.com/content/www/us/en/embedded/products/bay-trail/atom-e3800-family-datasheet.html">https://www.intel.com/content/www/us/en/embedded/products/bay-trail/atom-e3800-family-datasheet.html</a>\n
    download BayTrail specification in external browser\n

    @subsection Parm_sec Command line parameters
    1. GPIOSpy no parameter: read all SoC GPIO and binary settings\n
    2. GPIOSpy /list : list all GPIO names w/o actually access the GPIO
    3. GPIOSpy <gpio_name> : view bit fields of a particular GPIO (get gpio_name with /list command)

*/
#include <stdio.h>
#include <stdlib.h>
#include "BYTGPIO.h"
//
//https://www.intel.com/content/www/us/en/embedded/products/bay-trail/atom-e3800-family-datasheet.html
//
#define ELC(x) (sizeof(x) / sizeof(x[0]))

/*! 
    @fn int chkcmdln(int argc, char **argv)

    @brief checks the command line for /help and for "/all" parameter

    @details 
            The function checks command line for helprequest (and returns 1
            in theat case) or for additional, global parameters like "/all" or
            "/pcionly" (to display only 256 byte header for each PCIE function
    
    @param[in] argc : argument count
    @param[in] argv : argument vector

    @return 1 : helptext was shown
    @return 0 : otherwise

*/
int chkcmdln(int argc, char **argv) {
    int nRet = 0;
    int i,j;
    int ihlp;
    static char *helpstr[] = {"/h","/help","/hlp","-h","-help","--h","--help", "/?","-?","--?" };

    for (i = 0, ihlp = 0 ; ihlp == 0 && i < argc ; i++)
        for(j = 0 ; ihlp == 0 && j < ELC(helpstr); j++)
            ihlp = (0 == strcmp(argv[i], helpstr[j]) ? i : 0);

    if(0 != ihlp)
    {
        printf("    BayTrailGPIOSpy w/o parameter - dump all GPIO\n");
        printf("    BayTrailGPIOSpy /list         - list GPIO names supported by this program\n");
        printf("    BayTrailGPIOSpy /all          - displays current settings of all GPIO\n");
        printf("    BayTrailGPIOSpy gpio_name     - displays current settings of one particular GPIO\n");
        printf("    NOTE: to change GPIO settings during runtime, use a memory write tool.\nThe memory address of a given GPIO is provided by this tool.\n\n");
        nRet = 1;
    }
    return nRet;
}

GPIOID2NAME GpioID2Name[] = {
    {uart1_rts_b,"uart1_rts_b"},
    {uart1_txd,"uart1_txd"},
    {uart1_rxd,"uart1_rxd"},
    {i2c_nfc_scl,"i2c_nfc_scl"},
    {uart1_cts_b,"uart1_cts_b"},
    {i2c_nfc_sda,"i2c_nfc_sda"},
    {uart2_rxd,"uart2_rxd"},
    {uart2_txd,"uart2_txd"},
    {uart2_cts_b,"uart2_cts_b"},
    {uart2_rts_b,"uart2_rts_b"},
    {pwm0,"pwm0"},
    {pwm1,"pwm1"},
    {gp_ssp_2_fs,"gp_ssp_2_fs"},
    {gp_ssp_2_clk,"gp_ssp_2_clk"},
    {gp_ssp_2_txd,"gp_ssp_2_txd"},
    {gp_ssp_2_rxd,"gp_ssp_2_rxd"},
    {spi1_clk,"spi1_clk"},
    {spi1_cs0_b,"spi1_cs0_b"},
    {spi1_miso,"spi1_miso"},
    {spi1_mosi,"spi1_mosi"},
    {i2c5_scl,"i2c5_scl"},
    {i2c5_sda,"i2c5_sda"},
    {i2c6_scl,"i2c6_scl"},
    {i2c4_scl,"i2c4_scl"},
    {i2c6_sda,"i2c6_sda"},
    {i2c3_sda,"i2c3_sda"},
    {i2c4_sda,"i2c4_sda"},
    {i2c2_scl,"i2c2_scl"},
    {i2c3_scl,"i2c3_scl"},
    {i2c2_sda,"i2c2_sda"},
    {i2c1_scl,"i2c1_scl"},
    {i2c1_sda,"i2c1_sda"},
    {i2c0_scl,"i2c0_scl"},
    {i2c0_sda,"i2c0_sda"},
    {hda_rstb,"hda_rstb"},
    {hda_sdi1,"hda_sdi1"},
    {hda_clk,"hda_clk"},
    {hda_sync,"hda_sync"},
    {hda_sdo,"hda_sdo"},
    {hda_sdi0,"hda_sdi0"},
    {hda_dockrstb,"hda_dockrstb"},
    {sdmmc3_d1,"sdmmc3_d1"},
    {sdmmc3_d3,"sdmmc3_d3"},
    {sdmmc3_clk,"sdmmc3_clk"},
    {sdmmc3_cmd,"sdmmc3_cmd"},
    {sdmmc3_d2,"sdmmc3_d2"},
    {sdmmc3_d0,"sdmmc3_d0"},
    {sdmmc2_d1,"sdmmc2_d1"},
    {sdmmc2_cmd,"sdmmc2_cmd"},
    {sdmmc2_d3_cd_b,"sdmmc2_d3_cd_b"},
    {sdmmc2_clk,"sdmmc2_clk"},
    {mmc1_reset_b,"mmc1_reset_b"},
    {sdmmc2_d2,"sdmmc2_d2"},
    {sdmmc2_d0,"sdmmc2_d0"},
    {sdmmc1_d3_cd_b,"sdmmc1_d3_cd_b"},
    {mmc1_d6,"mmc1_d6"},
    {mmc1_d4_sd_we,"mmc1_d4_sd_we"},
    {sdmmc1_cmd,"sdmmc1_cmd"},
    {sdmmc3_cd_b,"sdmmc3_cd_b"},
    {sdmmc1_d2,"sdmmc1_d2"},
    {mmc1_d5,"mmc1_d5"},
    {sdmmc1_d0,"sdmmc1_d0"},
    {sdmmc1_clk,"sdmmc1_clk"},
    {mmc1_d7,"mmc1_d7"},
    {sdmmc1_d1,"sdmmc1_d1"},
    {lpc_clkout1,"lpc_clkout1"},
    {lpc_ad3,"lpc_ad3"},
    {lpc_ad2,"lpc_ad2"},
    {lpc_ad1,"lpc_ad1"},
    {lpc_frameb,"lpc_frameb"},
    {lpc_ad0,"lpc_ad0"},
    {lpc_clkout0,"lpc_clkout0"},
    {lpc_clkrunb,"lpc_clkrunb"},
    {hv_crt_ddc_clk,"hv_crt_ddc_clk"},
    {hv_crt_vsync,"hv_crt_vsync"},
    {hv_crt_hsync,"hv_crt_hsync"},
    {hv_crt_ddc_data,"hv_crt_ddc_data"},
    {mhsi_acdata,"mhsi_acdata"},
    {mhsi_acwake,"mhsi_acwake"},
    {mhsi_acflag,"mhsi_acflag"},
    {mhsi_caflag,"mhsi_caflag"},
    {mhsi_cadata,"mhsi_cadata"},
    {mhsi_caready,"mhsi_caready"},
    {mhsi_acready,"mhsi_acready"},
    {hda_dockenb,"hda_dockenb"},
    {sata_gp0,"sata_gp0"},
    {ilb_serirq,"ilb_serirq"},
    {plt_clk1,"plt_clk1"},
    {smb_clk,"smb_clk"},
    {sata_gp1,"sata_gp1"},
    {smb_data,"smb_data"},
    {plt_clk2,"plt_clk2"},
    {smb_alertb,"smb_alertb"},
    {sata_ledn,"sata_ledn"},
    {pmu_resetbutton_b,"pmu_resetbutton_b"},
    {sdmmc3_1p8_en,"sdmmc3_1p8_en"},
    {pcie_clkreq0b,"pcie_clkreq0b"},
    {plt_clk4,"plt_clk4"},
    {pcie_clkreq3b,"pcie_clkreq3b"},
    {pcie_clkreq1b,"pcie_clkreq1b"},
    {plt_clk5,"plt_clk5"},
    {pcie_clkreq4b,"pcie_clkreq4b"},
    {pcie_clkreq2b,"pcie_clkreq2b"},
    {spkr,"spkr"},
    {plt_clk3,"plt_clk3"},
    {sdmmc3_pwr_en_b,"sdmmc3_pwr_en_b"},
    {plt_clk0,"plt_clk0"},
    {vgpio_0,"vgpio_0"},
    {vgpio_1,"vgpio_1"},
    {vgpio_2,"vgpio_2"},
    {vgpio_3,"vgpio_3"},
    {vgpio_4,"vgpio_4"},
    {vgpio_5,"vgpio_5"},
    {vgpio_6,"vgpio_6"},
    {vgpio_7,"vgpio_7"},
    {vgpio_8,"vgpio_8"},
    {vgpio_9,"vgpio_9"},
    {vgpio_10,"vgpio_10"},
    {vgpio_11,"vgpio_11"},
    {vgpio_12,"vgpio_12"},
    {vgpio_13,"vgpio_13"},
    {vgpio_14,"vgpio_14"},
    {vgpio_15,"vgpio_15"},
    {vgpio_16,"vgpio_16"},
    {vgpio_17,"vgpio_17"},
    {vgpio_18,"vgpio_18"},
    {vgpio_19,"vgpio_19"},
    {vgpio_20,"vgpio_20"},
    {usb_oc1_b,"usb_oc1_b"},
    {pmu_wake_b,"pmu_wake_b"},
    {spi_cs1_b,"spi_cs1_b"},
    {spi_cs0_b,"spi_cs0_b"},
    {spi_clk,"spi_clk"},
    {spi_mosi,"spi_mosi"},
    {spi_miso,"spi_miso"},
    {suspwrdnack,"suspwrdnack"},
    {pmu_pwrbtn_b,"pmu_pwrbtn_b"},
    {pmu_batlow_b,"pmu_batlow_b"},
    {pmu_wake_lan_b,"pmu_wake_lan_b"},
    {pmu_susclk,"pmu_susclk"},
    {usb_oc0_b,"usb_oc0_b"},
    {pmu_slp_s3_b,"pmu_slp_s3_b"},
    {pmu_ac_present,"pmu_ac_present"},
    {pmu_slp_s4_b,"pmu_slp_s4_b"},
    {pmu_pltrst_b,"pmu_pltrst_b"},
    {pmu_slp_lan_b,"pmu_slp_lan_b"},
    {sec_gpio_sus10,"sec_gpio_sus10"},
    {sus_stat_b,"sus_stat_b"},
    {pmu_slp_s0ix_b,"pmu_slp_s0ix_b"},
    {gpio_dfx5,"gpio_dfx5"},
    {gpio_dfx4,"gpio_dfx4"},
    {gpio_dfx0,"gpio_dfx0"},
    {gpio_dfx6,"gpio_dfx6"},
    {gpio_dfx7,"gpio_dfx7"},
    {gpio_dfx8,"gpio_dfx8"},
    {gpio_dfx3,"gpio_dfx3"},
    {gpio_dfx2,"gpio_dfx2"},
    {gpio_sus0,"gpio_sus0"},
    {gpio_sus2,"gpio_sus2"},
    {gpio_sus3,"gpio_sus3"},
    {gpio_sus4,"gpio_sus4"},
    {gpio_sus1,"gpio_sus1"},
    {gpio_sus5,"gpio_sus5"},
    {gpio_sus7,"gpio_sus7"},
    {gpio_sus6,"gpio_sus6"},
    {sec_gpio_sus9,"sec_gpio_sus9"},
    {sec_gpio_sus8,"sec_gpio_sus8"},
    {gpio_dfx1,"gpio_dfx1"},
    {usb_ulpi_0_refclk,"usb_ulpi_0_refclk"},
    {tck,"tck"},
    {trst_b,"trst_b"},
    {tdi,"tdi"},
    {tms,"tms"},
    {cx_prdy_b,"cx_prdy_b"},
    {cx_preq_b,"cx_preq_b"},
    {tdo,"tdo"},
    {usb_ulpi_0_data4,"usb_ulpi_0_data4"},
    {usb_ulpi_0_data2,"usb_ulpi_0_data2"},
    {usb_ulpi_0_data6,"usb_ulpi_0_data6"},
    {usb_ulpi_0_clk,"usb_ulpi_0_clk"},
    {usb_ulpi_0_dir,"usb_ulpi_0_dir"},
    {usb_ulpi_0_nxt,"usb_ulpi_0_nxt"},
    {usb_ulpi_0_data1,"usb_ulpi_0_data1"},
    {usb_ulpi_0_data3,"usb_ulpi_0_data3"},
    {usb_ulpi_0_data0,"usb_ulpi_0_data0"},
    {usb_ulpi_0_data5,"usb_ulpi_0_data5"},
    {usb_ulpi_0_data7,"usb_ulpi_0_data7"},
    {usb_ulpi_0_stp,"usb_ulpi_0_stp"},
};

/*! 
    @fn int main(int argc, char **argv)

    @brief The PCIESpy main

    @details
    
    @param[in] argc
    @param[in] argv

    @return 0  : success
    @return !0 : failure
*/
int main(int argc, char **argv) {

    unsigned gpiobase;// PCI 0/1F/0/4C[31:2]
    char fPrintAll = 0;
    int i;
    BAYTRAIL_GPIO gpiobuf;

    //
    // get the GPIO base from the LPC device 0/1F/0 register 0x4C
    //
    outpd(0xCF8, 0x80000000 + (0 << 16) + (0x1F << 11) + (0 << 8) + 0x4C);
    gpiobase = ~3 & inpd(0xCFC);

    do {
        if (chkcmdln(argc, argv))
            break;
//
// "/list" - list all GPIO know to the program
//
        if (0 == strcmp("/list", argv[1])) {

            printf("list!, ELC == %d\n",(int) ELC(GpioID2Name));

            for (i = 0; i < ELC(GpioID2Name); i++) {
                printf("%s\n", GpioID2Name[i].szGpioName);
            }
            break;
        }
        
        if (0 == strcmp("/all", argv[1])) {
            printf("all!, ELC == %d\n", (int)ELC(GpioID2Name));
            fPrintAll = 1;
        }
//
// gpio_name - display one particular GPIO
//
        if (1 == fPrintAll || argc > 1) {

            for (i = 0; i < ELC(GpioID2Name); i++) {
                BAYTRAIL_GPIO *pGpio = (BAYTRAIL_GPIO *)(gpiobase + GpioID2Name[i].nGpioOfs);

                if (1 == fPrintAll || 0 == strcmp(GpioID2Name[i].szGpioName, argv[1])) {

                    gpiobuf.cfg.reg = pGpio->cfg.reg;
                    gpiobuf.mpx.reg = pGpio->mpx.reg;
                    gpiobuf.val.reg = pGpio->val.reg;
                    gpiobuf.tst.reg = pGpio->tst.reg;

                    printf("%s %p: %08X %08X %08X %08X\n", GpioID2Name[i].szGpioName, pGpio, gpiobuf.cfg.reg, gpiobuf.mpx.reg, gpiobuf.val.reg, gpiobuf.tst.reg);

                    printf("cfg.func_pin_mux       2:0: 0x%X       val.pad_val              0: 0x%X\n", gpiobuf.cfg.bit.func_pin_mux, gpiobuf.val.bit.pad_val);
                    printf("cfg.RSVD0              6:3: 0x%X       val.ioutenb              1: 0x%X\n", gpiobuf.cfg.bit.RSVD0, gpiobuf.val.bit.ioutenb);
                    printf("cfg.pull_assign        8:7: 0x%X       val.iinenb               2: 0x%X\n", gpiobuf.cfg.bit.pull_assign, gpiobuf.val.bit.iinenb);
                    printf("cfg.pull_str          10:9: 0x%X       val.RSVD              31:3: 0x%X\n", gpiobuf.cfg.bit.pull_str, gpiobuf.val.bit.RSVD);
                    printf("cfg.bypass_flop         11: 0x%X       \n", gpiobuf.cfg.bit.bypass_flop);
                    printf("cfg.RSVD1               12: 0x%X       mpx.dll_std_mux        4:0: 0x%X\n", gpiobuf.cfg.bit.RSVD1, gpiobuf.mpx.bit.dll_std_mux);
                    printf("cfg.ihysctl          14:13: 0x%X       mpx.dll_hgh_mux        9:5: 0x%X\n", gpiobuf.cfg.bit.ihysctl, gpiobuf.mpx.bit.dll_hgh_mux);
                    printf("cfg.RSVD2               15: 0x%X       mpx.dll_ddr_mux      14:10: 0x%X\n", gpiobuf.cfg.bit.RSVD2, gpiobuf.mpx.bit.dll_ddr_mux);
                    printf("cfg.fast_clkgate        16: 0x%X       mpx.dll_cf_od           15: 0x%X\n", gpiobuf.cfg.bit.fast_clkgate, gpiobuf.mpx.bit.dll_cf_od);
                    printf("cfg.slow_clkgate        17: 0x%X       mpx.RSVD             31:16: 0x%X\n", gpiobuf.cfg.bit.slow_clkgate, gpiobuf.mpx.bit.RSVD);
                    printf("cfg.filter_slow         18: 0x%X       \n", gpiobuf.cfg.bit.filter_slow);
                    printf("cfg.filter_en           19: 0x%X       tst.RSVD0              9:0: 0x%X\n", gpiobuf.cfg.bit.filter_en, gpiobuf.tst.bit.RSVD0);
                    printf("cfg.debounce            20: 0x%X       tst.bscan_bypass         1: 0x%X\n", gpiobuf.cfg.bit.debounce, gpiobuf.tst.bit.bscan_bypass);
                    printf("cfg.RSVD3            22:21: 0x%X       tst.RSVD1            31:11: 0x%X\n", gpiobuf.cfg.bit.RSVD3, gpiobuf.tst.bit.RSVD1);
                    printf("cfg.RSVD4               23: 0x%X       \n", gpiobuf.cfg.bit.RSVD4);
                    printf("cfg.gd_level            24: 0x%X       \n", gpiobuf.cfg.bit.gd_level);
                    printf("cfg.gd_tpe              25: 0x%X       \n", gpiobuf.cfg.bit.gd_tpe);
                    printf("cfg.gd_tne              26: 0x%X       \n", gpiobuf.cfg.bit.gd_tne);
                    printf("cfg.direct_irq_en       27: 0x%X       \n", gpiobuf.cfg.bit.direct_irq_en);
                    printf("cfg.RSVD5               28: 0x%X       \n", gpiobuf.cfg.bit.RSVD5);
                    printf("cfg.disable_second_mask 29: 0x%X       \n", gpiobuf.cfg.bit.disable_second_mask);
                    printf("cfg.RSVD6               30: 0x%X       \n", gpiobuf.cfg.bit.RSVD6);
                    printf("cfg.RSVD7               31: 0x%X       \n\n", gpiobuf.cfg.bit.RSVD7);
                }
            }
            break;
        }
//
// dump all, if no parameter
//
        for (i = 0; i < ELC(GpioID2Name); i++) {
            BAYTRAIL_GPIO *pGpio = (BAYTRAIL_GPIO *)(gpiobase + GpioID2Name[i].nGpioOfs);

            gpiobuf.cfg.reg = pGpio->cfg.reg;
            gpiobuf.mpx.reg = pGpio->mpx.reg;
            gpiobuf.val.reg = pGpio->val.reg;
            gpiobuf.tst.reg = pGpio->tst.reg;
    
            printf("%20s %p: %08X %08X %08X %08X\n", GpioID2Name[i].szGpioName, pGpio, gpiobuf.cfg.reg, gpiobuf.mpx.reg, gpiobuf.val.reg, gpiobuf.tst.reg);
        }

    } while (0);

    return 0;
}
