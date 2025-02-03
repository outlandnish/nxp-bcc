/*
 * Copyright 2016 - 2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef COMMON_H_
#define COMMON_H_

/*******************************************************************************
 * Definitions (depends on the utilized HW setup)
 ******************************************************************************/

/* Used BCC device */
#define MC33771C    /* Define MC33771C if FRDM33771CSPEVB or RD33771CDSTEVB is used. */
//#define MC33772C    /* Define MC33772C if FRDM33772CSPEVB or KIT33772CTPLEVB is used. */

/* Used HW setup. */
#define SPI         /* Define SPI if S32K144EVB + FRDM33771CSPEVB/FRDM33772CSPEVB is used. */
//#define TPL         /* Define TPL if S32K144EVB + FRDMDUAL33664EVB + RD33771CDSTEVB/KIT33772CTPLEVB is used. */

/* Number of MC3377xC devices connected (must be 1U for SPI). */
#define BCC_DEMO_BCC_CNT        1U

/* R_SHUNT value in [uOhm].
 * RD33771CDSTEVB: Current measurement is not supported (ISENSE+ and ISENSE- are
 *                 grounded).
 * FRDM33771CSPEVB: ISENSE+ connected to X2-2, ISENSE- to X2-1. SHUNT resistor (R41)
                    is not populated on the board.
 * KIT33772CTPLEVB: ISENSE+ connected to J12-31, ISENSE- to J12-32. SHUNT resistor
                    is not populated on the board.
 * FRDM33772CSPEVB: ISENSE+ connected to J12-31, ISENSE- to J12-32. SHUNT resistor
                    is not populated on the board. */
#define DEMO_RSHUNT             100000U

#if !defined(MC33771C) && !defined(MC33772C)
    #error "Select used BCC device by defining MC33771C or MC33772C."
#endif

#if defined(MC33771C) && defined(MC33772C)
    #error "Select only one type of BCC device."
#endif

#if !defined(SPI) && !defined(TPL)
    #error "Select used type of communication by defining SPI or TPL."
#endif

#if defined(SPI) && defined(TPL)
    #error "Select only one type of communication."
#endif

/*******************************************************************************
 * Initial register configuration
 ******************************************************************************/

/* Note: INIT register is initialized automatically by the BCC driver. */
/* Note: SYS_CFG_GLOBAL register contains only command GO2SLEEP (no initialization needed). */
/* Note: EEPROM_CTRL, FUSE_MIRROR_DATA and FUSE_MIRROR_CNTL registers are not initialized. */

/* Initial value of SYS_CFG1 register. */
#ifdef TPL
/* Disable current measurement for TPL board. */
#define MC33771C_SYS_CFG1_VALUE ( \
    MC33771C_SYS_CFG1_CYCLIC_TIMER(MC33771C_SYS_CFG1_CYCLIC_TIMER_DISABLED_ENUM_VAL) | \
    MC33771C_SYS_CFG1_DIAG_TIMEOUT(MC33771C_SYS_CFG1_DIAG_TIMEOUT_1S_ENUM_VAL) | \
    MC33771C_SYS_CFG1_I_MEAS_EN(MC33771C_SYS_CFG1_I_MEAS_EN_DISABLED_ENUM_VAL) | \
    MC33771C_SYS_CFG1_CB_DRVEN(MC33771C_SYS_CFG1_CB_DRVEN_DISABLED_ENUM_VAL) | \
    MC33771C_SYS_CFG1_GO2DIAG(MC33771C_SYS_CFG1_GO2DIAG_EXIT_ENUM_VAL) | \
    MC33771C_SYS_CFG1_CB_MANUAL_PAUSE(MC33771C_SYS_CFG1_CB_MANUAL_PAUSE_DISABLED_ENUM_VAL) | \
    MC33771C_SYS_CFG1_SOFT_RST(MC33771C_SYS_CFG1_SOFT_RST_DISABLED_ENUM_VAL) | \
    MC33771C_SYS_CFG1_FAULT_WAVE(MC33771C_SYS_CFG1_FAULT_WAVE_DISABLED_ENUM_VAL) | \
    MC33771C_SYS_CFG1_WAVE_DC_BITX(MC33771C_SYS_CFG1_WAVE_DC_BITX_500US_ENUM_VAL) \
)
#else

/* Enable current measurement for SPI board. */
#define MC33771C_SYS_CFG1_VALUE ( \
    MC33771C_SYS_CFG1_CYCLIC_TIMER(MC33771C_SYS_CFG1_CYCLIC_TIMER_DISABLED_ENUM_VAL) | \
    MC33771C_SYS_CFG1_DIAG_TIMEOUT(MC33771C_SYS_CFG1_DIAG_TIMEOUT_1S_ENUM_VAL) | \
    MC33771C_SYS_CFG1_I_MEAS_EN(MC33771C_SYS_CFG1_I_MEAS_EN_ENABLED_ENUM_VAL) | \
    MC33771C_SYS_CFG1_CB_DRVEN(MC33771C_SYS_CFG1_CB_DRVEN_DISABLED_ENUM_VAL) | \
    MC33771C_SYS_CFG1_GO2DIAG(MC33771C_SYS_CFG1_GO2DIAG_EXIT_ENUM_VAL) | \
    MC33771C_SYS_CFG1_CB_MANUAL_PAUSE(MC33771C_SYS_CFG1_CB_MANUAL_PAUSE_DISABLED_ENUM_VAL) | \
    MC33771C_SYS_CFG1_SOFT_RST(MC33771C_SYS_CFG1_SOFT_RST_DISABLED_ENUM_VAL) | \
    MC33771C_SYS_CFG1_FAULT_WAVE(MC33771C_SYS_CFG1_FAULT_WAVE_DISABLED_ENUM_VAL) | \
    MC33771C_SYS_CFG1_WAVE_DC_BITX(MC33771C_SYS_CFG1_WAVE_DC_BITX_500US_ENUM_VAL) \
)
#endif

/* Enable current measurement for MC33772C boards. */
#define MC33772C_SYS_CFG1_VALUE ( \
    MC33772C_SYS_CFG1_CYCLIC_TIMER(MC33772C_SYS_CFG1_CYCLIC_TIMER_DISABLED_ENUM_VAL) | \
    MC33772C_SYS_CFG1_DIAG_TIMEOUT(MC33772C_SYS_CFG1_DIAG_TIMEOUT_1S_ENUM_VAL) | \
    MC33772C_SYS_CFG1_I_MEAS_EN(MC33772C_SYS_CFG1_I_MEAS_EN_ENABLED_ENUM_VAL) | \
    MC33772C_SYS_CFG1_CB_DRVEN(MC33772C_SYS_CFG1_CB_DRVEN_DISABLED_ENUM_VAL) | \
    MC33772C_SYS_CFG1_GO2DIAG(MC33772C_SYS_CFG1_GO2DIAG_EXIT_ENUM_VAL) | \
    MC33772C_SYS_CFG1_CB_MANUAL_PAUSE(MC33772C_SYS_CFG1_CB_MANUAL_PAUSE_DISABLED_ENUM_VAL) | \
    MC33772C_SYS_CFG1_SOFT_RST(MC33772C_SYS_CFG1_SOFT_RST_DISABLED_ENUM_VAL) | \
    MC33772C_SYS_CFG1_FAULT_WAVE(MC33772C_SYS_CFG1_FAULT_WAVE_DISABLED_ENUM_VAL) | \
    MC33772C_SYS_CFG1_WAVE_DC_BITX(MC33772C_SYS_CFG1_WAVE_DC_BITX_500US_ENUM_VAL) \
)

/* Initial value of SYS_CFG2 register. */
#define MC33771C_SYS_CFG2_VALUE ( \
    MC33771C_SYS_CFG2_FLT_RST_CFG(MC33771C_SYS_CFG2_FLT_RST_CFG_OSC_MON_RESET_ENUM_VAL) | \
    MC33771C_SYS_CFG2_TIMEOUT_COMM(MC33771C_SYS_CFG2_TIMEOUT_COMM_256MS_ENUM_VAL) | \
    MC33771C_SYS_CFG2_NUMB_ODD(MC33771C_SYS_CFG2_NUMB_ODD_EVEN_ENUM_VAL) | \
    MC33771C_SYS_CFG2_HAMM_ENCOD(MC33771C_SYS_CFG2_HAMM_ENCOD_DECODE_ENUM_VAL) \
)

/* Initial value of ADC_CFG register. */
#define MC33771C_ADC_CFG_VALUE ( \
    MC33771C_ADC_CFG_AVG(MC33771C_ADC_CFG_AVG_NO_AVERAGING_ENUM_VAL) | \
    MC33771C_ADC_CFG_PGA_GAIN(MC33771C_ADC_CFG_PGA_GAIN_AUTO_ENUM_VAL) | \
    MC33771C_ADC_CFG_ADC1_A_DEF(MC33771C_ADC_CFG_ADC1_A_DEF_16_BIT_ENUM_VAL) | \
    MC33771C_ADC_CFG_ADC1_B_DEF(MC33771C_ADC_CFG_ADC1_B_DEF_16_BIT_ENUM_VAL) | \
    MC33771C_ADC_CFG_ADC2_DEF(MC33771C_ADC_CFG_ADC2_DEF_16_BIT_ENUM_VAL) \
)

/* Initial value of ADC2_OFFSET_COMP register. */
#define MC33771C_ADC2_OFFSET_COMP_VALUE (\
    MC33771C_ADC2_OFFSET_COMP_CC_RST_CFG(MC33771C_ADC2_OFFSET_COMP_CC_RST_CFG_CC_RESET_ENUM_VAL) | \
    MC33771C_ADC2_OFFSET_COMP_FREE_CNT(MC33771C_ADC2_OFFSET_COMP_FREE_CNT_CLAMP_ENUM_VAL) | \
    MC33771C_ADC2_OFFSET_COMP_ALLCBOFFONSHORT(MC33771C_ADC2_OFFSET_COMP_ALLCBOFFONSHORT_SHORTED_ENUM_VAL) | \
    MC33771C_ADC2_OFFSET_COMP_ADC2_OFFSET_COMP(BCC_GET_ADC2_OFFSET(0)) \
)

/* Initial value of OV_UV_EN register. */
#define MC33771C_OV_UV_EN_VALUE ( \
    MC33771C_OV_UV_EN_COMMON_UV_TH(MC33771C_OV_UV_EN_COMMON_UV_TH_COMMON_ENUM_VAL) | \
    MC33771C_OV_UV_EN_COMMON_OV_TH(MC33771C_OV_UV_EN_COMMON_OV_TH_COMMON_ENUM_VAL) | \
    /* CTs OV and UV enable (bit is 1) or disable (bit is 0). */ \
    MC33771C_OV_UV_EN_CT14_OVUV_EN(MC33771C_OV_UV_EN_CT14_OVUV_EN_ENABLED_ENUM_VAL) | \
    MC33771C_OV_UV_EN_CT13_OVUV_EN(MC33771C_OV_UV_EN_CT13_OVUV_EN_ENABLED_ENUM_VAL) | \
    MC33771C_OV_UV_EN_CT12_OVUV_EN(MC33771C_OV_UV_EN_CT12_OVUV_EN_ENABLED_ENUM_VAL) | \
    MC33771C_OV_UV_EN_CT11_OVUV_EN(MC33771C_OV_UV_EN_CT11_OVUV_EN_ENABLED_ENUM_VAL) | \
    MC33771C_OV_UV_EN_CT10_OVUV_EN(MC33771C_OV_UV_EN_CT10_OVUV_EN_ENABLED_ENUM_VAL) | \
    MC33771C_OV_UV_EN_CT9_OVUV_EN(MC33771C_OV_UV_EN_CT9_OVUV_EN_ENABLED_ENUM_VAL) | \
    MC33771C_OV_UV_EN_CT8_OVUV_EN(MC33771C_OV_UV_EN_CT8_OVUV_EN_ENABLED_ENUM_VAL) | \
    MC33771C_OV_UV_EN_CT7_OVUV_EN(MC33771C_OV_UV_EN_CT7_OVUV_EN_ENABLED_ENUM_VAL) | \
    MC33771C_OV_UV_EN_CT6_OVUV_EN(MC33771C_OV_UV_EN_CT6_OVUV_EN_ENABLED_ENUM_VAL) | \
    MC33771C_OV_UV_EN_CT5_OVUV_EN(MC33771C_OV_UV_EN_CT5_OVUV_EN_ENABLED_ENUM_VAL) | \
    MC33771C_OV_UV_EN_CT4_OVUV_EN(MC33771C_OV_UV_EN_CT4_OVUV_EN_ENABLED_ENUM_VAL) | \
    MC33771C_OV_UV_EN_CT3_OVUV_EN(MC33771C_OV_UV_EN_CT3_OVUV_EN_ENABLED_ENUM_VAL) | \
    MC33771C_OV_UV_EN_CT2_OVUV_EN(MC33771C_OV_UV_EN_CT2_OVUV_EN_ENABLED_ENUM_VAL) | \
    MC33771C_OV_UV_EN_CT1_OVUV_EN(MC33771C_OV_UV_EN_CT1_OVUV_EN_ENABLED_ENUM_VAL) \
)

#define MC33772C_OV_UV_EN_VALUE ( \
    MC33772C_OV_UV_EN_COMMON_UV_TH(MC33772C_OV_UV_EN_COMMON_UV_TH_COMMON_ENUM_VAL) | \
    MC33772C_OV_UV_EN_COMMON_OV_TH(MC33772C_OV_UV_EN_COMMON_OV_TH_COMMON_ENUM_VAL) | \
    /* CTs OV and UV enable (bit is 1) or disable (bit is 0). */ \
    MC33772C_OV_UV_EN_CT6_OVUV_EN(MC33772C_OV_UV_EN_CT6_OVUV_EN_ENABLED_ENUM_VAL) | \
    MC33772C_OV_UV_EN_CT5_OVUV_EN(MC33772C_OV_UV_EN_CT5_OVUV_EN_ENABLED_ENUM_VAL) | \
    MC33772C_OV_UV_EN_CT4_OVUV_EN(MC33772C_OV_UV_EN_CT4_OVUV_EN_ENABLED_ENUM_VAL) | \
    MC33772C_OV_UV_EN_CT3_OVUV_EN(MC33772C_OV_UV_EN_CT3_OVUV_EN_ENABLED_ENUM_VAL) | \
    MC33772C_OV_UV_EN_CT2_OVUV_EN(MC33772C_OV_UV_EN_CT2_OVUV_EN_ENABLED_ENUM_VAL) | \
    MC33772C_OV_UV_EN_CT1_OVUV_EN(MC33772C_OV_UV_EN_CT1_OVUV_EN_ENABLED_ENUM_VAL) \
)

/* Initial value of CBx_CFG registers. */
#define MC33771C_CBX_CFG_VALUE ( \
    MC33771C_CB1_CFG_CB_EN(MC33771C_CB1_CFG_CB_EN_DISABLED_ENUM_VAL) | \
    MC33771C_CB1_CFG_CB_TIMER(0U) /* Cell balance timer in minutes. */ \
)

/* Initial value of GPIO_CFG1 register.
 * MC33771C EVBs expect NTC at all GPIOx pins.
 * MC33772C EVBs expect voltage measurement at GPIO5 and GPIO6. The rest of pins is
 *          supposed to be used for NTC.
 * Note: SPI EVBs no not use GPIO0 and GPIO2. */
#define MC33771C_GPIO_CFG1_VALUE ( \
    MC33771C_GPIO_CFG1_GPIO0_CFG(MC33771C_GPIO_CFG1_GPIO0_CFG_ANALOG_RATIO_ENUM_VAL) | \
    MC33771C_GPIO_CFG1_GPIO1_CFG(MC33771C_GPIO_CFG1_GPIO1_CFG_ANALOG_RATIO_ENUM_VAL) | \
    MC33771C_GPIO_CFG1_GPIO2_CFG(MC33771C_GPIO_CFG1_GPIO2_CFG_ANALOG_RATIO_ENUM_VAL) | \
    MC33771C_GPIO_CFG1_GPIO3_CFG(MC33771C_GPIO_CFG1_GPIO3_CFG_ANALOG_RATIO_ENUM_VAL) | \
    MC33771C_GPIO_CFG1_GPIO4_CFG(MC33771C_GPIO_CFG1_GPIO4_CFG_ANALOG_RATIO_ENUM_VAL) | \
    MC33771C_GPIO_CFG1_GPIO5_CFG(MC33771C_GPIO_CFG1_GPIO5_CFG_ANALOG_RATIO_ENUM_VAL) | \
    MC33771C_GPIO_CFG1_GPIO6_CFG(MC33771C_GPIO_CFG1_GPIO6_CFG_ANALOG_RATIO_ENUM_VAL) \
)

#define MC33772C_GPIO_CFG1_VALUE ( \
    MC33772C_GPIO_CFG1_GPIO0_CFG(MC33772C_GPIO_CFG1_GPIO0_CFG_ANALOG_RATIO_ENUM_VAL) | \
    MC33772C_GPIO_CFG1_GPIO1_CFG(MC33772C_GPIO_CFG1_GPIO1_CFG_ANALOG_RATIO_ENUM_VAL) | \
    MC33772C_GPIO_CFG1_GPIO2_CFG(MC33772C_GPIO_CFG1_GPIO2_CFG_ANALOG_RATIO_ENUM_VAL) | \
    MC33772C_GPIO_CFG1_GPIO3_CFG(MC33772C_GPIO_CFG1_GPIO3_CFG_ANALOG_RATIO_ENUM_VAL) | \
    MC33772C_GPIO_CFG1_GPIO4_CFG(MC33772C_GPIO_CFG1_GPIO4_CFG_ANALOG_RATIO_ENUM_VAL) | \
    MC33772C_GPIO_CFG1_GPIO5_CFG(MC33772C_GPIO_CFG1_GPIO5_CFG_ANALOG_ABS_ENUM_VAL) | \
    MC33772C_GPIO_CFG1_GPIO6_CFG(MC33772C_GPIO_CFG1_GPIO5_CFG_ANALOG_ABS_ENUM_VAL) \
)

/* Initial value of GPIO_CFG2 register. */
#define MC33771C_GPIO_CFG2_VALUE ( \
    MC33771C_GPIO_CFG2_GPIO2_SOC(MC33771C_GPIO_CFG2_GPIO2_SOC_ADC_TRG_DISABLED_ENUM_VAL) | \
    MC33771C_GPIO_CFG2_GPIO0_WU(MC33771C_GPIO_CFG2_GPIO0_WU_NO_WAKEUP_ENUM_VAL) | \
    MC33771C_GPIO_CFG2_GPIO0_FLT_ACT(MC33771C_GPIO_CFG2_GPIO0_FLT_ACT_DISABLED_ENUM_VAL) | \
    /* Note: GPIOx_DR are initialized to zero (low output level). */ \
    MC33771C_GPIO_CFG2_GPIO6_DR(MC33771C_GPIO_CFG2_GPIO6_DR_LOW_ENUM_VAL) | \
    MC33771C_GPIO_CFG2_GPIO5_DR(MC33771C_GPIO_CFG2_GPIO5_DR_LOW_ENUM_VAL) | \
    MC33771C_GPIO_CFG2_GPIO4_DR(MC33771C_GPIO_CFG2_GPIO4_DR_LOW_ENUM_VAL) | \
    MC33771C_GPIO_CFG2_GPIO3_DR(MC33771C_GPIO_CFG2_GPIO3_DR_LOW_ENUM_VAL) | \
    MC33771C_GPIO_CFG2_GPIO2_DR(MC33771C_GPIO_CFG2_GPIO2_DR_LOW_ENUM_VAL) | \
    MC33771C_GPIO_CFG2_GPIO1_DR(MC33771C_GPIO_CFG2_GPIO1_DR_LOW_ENUM_VAL) | \
    MC33771C_GPIO_CFG2_GPIO0_DR(MC33771C_GPIO_CFG2_GPIO0_DR_LOW_ENUM_VAL) \
)

/* Initial value of FAULT_MASK1 register. */
#define MC33771C_FAULT_MASK1_VALUE ( \
    MC33771C_FAULT_MASK1_VPWR_OV_FLT_MASK_12_F(MC33771C_FAULT_MASK1_VPWR_OV_FLT_MASK_12_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK1_VPWR_LV_FLT_MASK_11_F(MC33771C_FAULT_MASK1_VPWR_LV_FLT_MASK_11_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK1_COM_LOSS_FLT_MASK_10_F(MC33771C_FAULT_MASK1_COM_LOSS_FLT_MASK_10_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK1_COM_ERR_FLT_MASK_9_F(MC33771C_FAULT_MASK1_COM_ERR_FLT_MASK_9_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK1_CSB_WUP_FLT_MASK_8_F(MC33771C_FAULT_MASK1_CSB_WUP_FLT_MASK_8_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK1_GPIO0_WUP_FLT_MASK_7_F(MC33771C_FAULT_MASK1_GPIO0_WUP_FLT_MASK_7_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK1_I2C_ERR_FLT_MASK_6_F(MC33771C_FAULT_MASK1_I2C_ERR_FLT_MASK_6_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK1_IS_OL_FLT_MASK_5_F(MC33771C_FAULT_MASK1_IS_OL_FLT_MASK_5_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK1_IS_OC_FLT_MASK_4_F(MC33771C_FAULT_MASK1_IS_OC_FLT_MASK_4_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK1_AN_OT_FLT_MASK_3_F(MC33771C_FAULT_MASK1_AN_OT_FLT_MASK_3_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK1_AN_UT_FLT_MASK_2_F(MC33771C_FAULT_MASK1_AN_UT_FLT_MASK_2_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK1_CT_OV_FLT_MASK_1_F(MC33771C_FAULT_MASK1_CT_OV_FLT_MASK_1_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK1_CT_UV_FLT_MASK_0_F(MC33771C_FAULT_MASK1_CT_UV_FLT_MASK_0_F_NOT_MASKED_ENUM_VAL) \
)

/* Initial value of FAULT_MASK2 register. */
#define MC33771C_FAULT_MASK2_VALUE ( \
    MC33771C_FAULT_MASK2_VCOM_OV_FLT_MASK_15_F(MC33771C_FAULT_MASK2_VCOM_OV_FLT_MASK_15_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK2_VCOM_UV_FLT_MASK_14_F(MC33771C_FAULT_MASK2_VCOM_UV_FLT_MASK_14_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK2_VANA_OV_FLT_MASK_13_F(MC33771C_FAULT_MASK2_VANA_OV_FLT_MASK_13_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK2_VANA_UV_FLT_MASK_12_F(MC33771C_FAULT_MASK2_VANA_UV_FLT_MASK_12_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK2_ADC1_B_FLT_MASK_11_F(MC33771C_FAULT_MASK2_ADC1_B_FLT_MASK_11_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK2_ADC1_A_FLT_MASK_10_F(MC33771C_FAULT_MASK2_ADC1_A_FLT_MASK_10_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK2_GND_LOSS_FLT_MASK_9_F(MC33771C_FAULT_MASK2_GND_LOSS_FLT_MASK_9_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK2_AN_OPEN_FLT_MASK_6_F(MC33771C_FAULT_MASK2_AN_OPEN_FLT_MASK_6_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK2_GPIO_SHORT_FLT_MASK_5_F(MC33771C_FAULT_MASK2_GPIO_SHORT_FLT_MASK_5_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK2_CB_SHORT_FLT_MASK_4_F(MC33771C_FAULT_MASK2_CB_SHORT_FLT_MASK_4_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK2_CB_OPEN_FLT_MASK_3_F(MC33771C_FAULT_MASK2_CB_OPEN_FLT_MASK_3_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK2_OSC_ERR_FLT_MASK_2_F(MC33771C_FAULT_MASK2_OSC_ERR_FLT_MASK_2_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK2_DED_ERR_FLT_MASK_1_F(MC33771C_FAULT_MASK2_DED_ERR_FLT_MASK_1_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK2_FUSE_ERR_FLT_MASK_0_F(MC33771C_FAULT_MASK2_FUSE_ERR_FLT_MASK_0_F_NOT_MASKED_ENUM_VAL) \
)

/* Initial value of FAULT_MASK3 register. */
#define MC33771C_FAULT_MASK3_VALUE ( \
    MC33771C_FAULT_MASK3_CC_OVR_FLT_MASK_15_F(MC33771C_FAULT_MASK3_CC_OVR_FLT_MASK_15_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK3_DIAG_TO_FLT_MASK_14_F(MC33771C_FAULT_MASK3_DIAG_TO_FLT_MASK_14_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK3_EOT_CB14_MASK_13_F(MC33771C_FAULT_MASK3_EOT_CB14_MASK_13_F_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK3_EOT_CB13_MASK_12_F(MC33771C_FAULT_MASK3_EOT_CB13_MASK_12_F_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK3_EOT_CB12_MASK_11_F(MC33771C_FAULT_MASK3_EOT_CB12_MASK_11_F_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK3_EOT_CB11_MASK_10_F(MC33771C_FAULT_MASK3_EOT_CB11_MASK_10_F_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK3_EOT_CB10_MASK_9_F(MC33771C_FAULT_MASK3_EOT_CB10_MASK_9_F_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK3_EOT_CB9_MASK_8_F(MC33771C_FAULT_MASK3_EOT_CB9_MASK_8_F_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK3_EOT_CB8_MASK_7_F(MC33771C_FAULT_MASK3_EOT_CB8_MASK_7_F_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK3_EOT_CB7_MASK_6_F(MC33771C_FAULT_MASK3_EOT_CB7_MASK_6_F_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK3_EOT_CB6_MASK_5_F(MC33771C_FAULT_MASK3_EOT_CB6_MASK_5_F_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK3_EOT_CB5_MASK_4_F(MC33771C_FAULT_MASK3_EOT_CB5_MASK_4_F_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK3_EOT_CB4_MASK_3_F(MC33771C_FAULT_MASK3_EOT_CB4_MASK_3_F_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK3_EOT_CB3_MASK_2_F(MC33771C_FAULT_MASK3_EOT_CB3_MASK_2_F_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK3_EOT_CB2_MASK_1_F(MC33771C_FAULT_MASK3_EOT_CB2_MASK_1_F_MASKED_ENUM_VAL) | \
    MC33771C_FAULT_MASK3_EOT_CB1_MASK_0_F(MC33771C_FAULT_MASK3_EOT_CB1_MASK_0_F_MASKED_ENUM_VAL) \
)

#define MC33772C_FAULT_MASK3_VALUE ( \
    MC33772C_FAULT_MASK3_CC_OVR_FLT_MASK_15_F(MC33772C_FAULT_MASK3_CC_OVR_FLT_MASK_15_F_NOT_MASKED_ENUM_VAL) | \
    MC33772C_FAULT_MASK3_DIAG_TO_FLT_MASK_14_F(MC33772C_FAULT_MASK3_DIAG_TO_FLT_MASK_14_F_NOT_MASKED_ENUM_VAL) | \
    MC33772C_FAULT_MASK3_VCP_UV_MASK_13_F(MC33772C_FAULT_MASK3_VCP_UV_MASK_13_F_NOT_MASKED_ENUM_VAL) | \
    MC33772C_FAULT_MASK3_EOT_CB6_MASK_5_F(MC33772C_FAULT_MASK3_EOT_CB6_MASK_5_F_MASKED_ENUM_VAL) | \
    MC33772C_FAULT_MASK3_EOT_CB5_MASK_4_F(MC33772C_FAULT_MASK3_EOT_CB5_MASK_4_F_MASKED_ENUM_VAL) | \
    MC33772C_FAULT_MASK3_EOT_CB4_MASK_3_F(MC33772C_FAULT_MASK3_EOT_CB4_MASK_3_F_MASKED_ENUM_VAL) | \
    MC33772C_FAULT_MASK3_EOT_CB3_MASK_2_F(MC33772C_FAULT_MASK3_EOT_CB3_MASK_2_F_MASKED_ENUM_VAL) | \
    MC33772C_FAULT_MASK3_EOT_CB2_MASK_1_F(MC33772C_FAULT_MASK3_EOT_CB2_MASK_1_F_MASKED_ENUM_VAL) | \
    MC33772C_FAULT_MASK3_EOT_CB1_MASK_0_F(MC33772C_FAULT_MASK3_EOT_CB1_MASK_0_F_MASKED_ENUM_VAL) \
)

/* Initial value of WAKEUP_MASK1 register. */
#define MC33771C_WAKEUP_MASK1_VALUE ( \
    MC33771C_WAKEUP_MASK1_VPWR_OV_FLT_MASK_12_F(MC33771C_WAKEUP_MASK1_VPWR_OV_FLT_MASK_12_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK1_VPWR_LV_FLT_MASK_11_F(MC33771C_WAKEUP_MASK1_VPWR_LV_FLT_MASK_11_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK1_GPIO0_WUP_FLT_MASK_7_F(MC33771C_WAKEUP_MASK1_GPIO0_WUP_FLT_MASK_7_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK1_IS_OC_FLT_MASK_4_F(MC33771C_WAKEUP_MASK1_IS_OC_FLT_MASK_4_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK1_AN_OT_FLT_MASK_3_F(MC33771C_WAKEUP_MASK1_AN_OT_FLT_MASK_3_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK1_AN_UT_FLT_MASK_2_F(MC33771C_WAKEUP_MASK1_AN_UT_FLT_MASK_2_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK1_CT_OV_FLT_MASK_1_F(MC33771C_WAKEUP_MASK1_CT_OV_FLT_MASK_1_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK1_CT_UV_FLT_MASK_0_F(MC33771C_WAKEUP_MASK1_CT_UV_FLT_MASK_0_F_NOT_MASKED_ENUM_VAL) \
)

/* Initial value of WAKEUP_MASK2 register. */
#define MC33771C_WAKEUP_MASK2_VALUE ( \
    MC33771C_WAKEUP_MASK2_VCOM_OV_FLT_MASK_15_F(MC33771C_WAKEUP_MASK2_VCOM_OV_FLT_MASK_15_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK2_VCOM_UV_FLT_MASK_14_F(MC33771C_WAKEUP_MASK2_VCOM_UV_FLT_MASK_14_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK2_VANA_OV_FLT_MASK_13_F(MC33771C_WAKEUP_MASK2_VANA_OV_FLT_MASK_13_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK2_VANA_UV_FLT_MASK_12_F(MC33771C_WAKEUP_MASK2_VANA_UV_FLT_MASK_12_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK2_ADC1_B_FLT_MASK_11_F(MC33771C_WAKEUP_MASK2_ADC1_B_FLT_MASK_11_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK2_ADC1_A_FLT_MASK_10_F(MC33771C_WAKEUP_MASK2_ADC1_A_FLT_MASK_10_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK2_GND_LOSS_FLT_MASK_9_F(MC33771C_WAKEUP_MASK2_GND_LOSS_FLT_MASK_9_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK2_IC_TSD_FLT_MASK_8_F(MC33771C_WAKEUP_MASK2_IC_TSD_FLT_MASK_8_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK2_GPIO_SHORT_FLT_MASK_5_F(MC33771C_WAKEUP_MASK2_GPIO_SHORT_FLT_MASK_5_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK2_CB_SHORT_FLT_MASK_4_F(MC33771C_WAKEUP_MASK2_CB_SHORT_FLT_MASK_4_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK2_OSC_ERR_FLT_MASK_2_F(MC33771C_WAKEUP_MASK2_OSC_ERR_FLT_MASK_2_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK2_DED_ERR_FLT_MASK_1_F(MC33771C_WAKEUP_MASK2_DED_ERR_FLT_MASK_1_F_NOT_MASKED_ENUM_VAL) \
)

/* Initial value of WAKEUP_MASK3 register. */
#define MC33771C_WAKEUP_MASK3_VALUE ( \
    MC33771C_WAKEUP_MASK3_CC_OVR_FLT_MASK_15_F(MC33771C_WAKEUP_MASK3_CC_OVR_FLT_MASK_15_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK3_EOT_CB14_MASK_13_F(MC33771C_WAKEUP_MASK3_EOT_CB14_MASK_13_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK3_EOT_CB13_MASK_12_F(MC33771C_WAKEUP_MASK3_EOT_CB13_MASK_12_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK3_EOT_CB12_MASK_11_F(MC33771C_WAKEUP_MASK3_EOT_CB12_MASK_11_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK3_EOT_CB11_MASK_10_F(MC33771C_WAKEUP_MASK3_EOT_CB11_MASK_10_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK3_EOT_CB10_MASK_9_F(MC33771C_WAKEUP_MASK3_EOT_CB10_MASK_9_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK3_EOT_CB9_MASK_8_F(MC33771C_WAKEUP_MASK3_EOT_CB9_MASK_8_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK3_EOT_CB8_MASK_7_F(MC33771C_WAKEUP_MASK3_EOT_CB8_MASK_7_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK3_EOT_CB7_MASK_6_F(MC33771C_WAKEUP_MASK3_EOT_CB7_MASK_6_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK3_EOT_CB6_MASK_5_F(MC33771C_WAKEUP_MASK3_EOT_CB6_MASK_5_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK3_EOT_CB5_MASK_4_F(MC33771C_WAKEUP_MASK3_EOT_CB5_MASK_4_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK3_EOT_CB4_MASK_3_F(MC33771C_WAKEUP_MASK3_EOT_CB4_MASK_3_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK3_EOT_CB3_MASK_2_F(MC33771C_WAKEUP_MASK3_EOT_CB3_MASK_2_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK3_EOT_CB2_MASK_1_F(MC33771C_WAKEUP_MASK3_EOT_CB2_MASK_1_F_NOT_MASKED_ENUM_VAL) | \
    MC33771C_WAKEUP_MASK3_EOT_CB1_MASK_0_F(MC33771C_WAKEUP_MASK3_EOT_CB1_MASK_0_F_NOT_MASKED_ENUM_VAL) \
)

#define MC33772C_WAKEUP_MASK3_VALUE ( \
    MC33772C_WAKEUP_MASK3_CC_OVR_FLT_MASK_15_F(MC33772C_WAKEUP_MASK3_CC_OVR_FLT_MASK_15_F_NOT_MASKED_ENUM_VAL) | \
    MC33772C_WAKEUP_MASK3_VCP_UV_MASK_13_F(MC33772C_WAKEUP_MASK3_VCP_UV_MASK_13_F_NOT_MASKED_ENUM_VAL) | \
    MC33772C_WAKEUP_MASK3_EOT_CB6_MASK_5_F(MC33772C_WAKEUP_MASK3_EOT_CB6_MASK_5_F_NOT_MASKED_ENUM_VAL) | \
    MC33772C_WAKEUP_MASK3_EOT_CB5_MASK_4_F(MC33772C_WAKEUP_MASK3_EOT_CB5_MASK_4_F_NOT_MASKED_ENUM_VAL) | \
    MC33772C_WAKEUP_MASK3_EOT_CB4_MASK_3_F(MC33772C_WAKEUP_MASK3_EOT_CB4_MASK_3_F_NOT_MASKED_ENUM_VAL) | \
    MC33772C_WAKEUP_MASK3_EOT_CB3_MASK_2_F(MC33772C_WAKEUP_MASK3_EOT_CB3_MASK_2_F_NOT_MASKED_ENUM_VAL) | \
    MC33772C_WAKEUP_MASK3_EOT_CB2_MASK_1_F(MC33772C_WAKEUP_MASK3_EOT_CB2_MASK_1_F_NOT_MASKED_ENUM_VAL) | \
    MC33772C_WAKEUP_MASK3_EOT_CB1_MASK_0_F(MC33772C_WAKEUP_MASK3_EOT_CB1_MASK_0_F_NOT_MASKED_ENUM_VAL) \
)

/* Initial value of TH_ALL_CT register. */
#define MC33771C_TH_ALL_CT_VALUE ( \
    MC33771C_TH_ALL_CT_ALL_CT_OV_TH(BCC_GET_TH_CTX(4200U))  /* CT OV threshold is 4200 mV. It is enabled/disabled through OV_UV_EN register. */ | \
    MC33771C_TH_ALL_CT_ALL_CT_UV_TH(BCC_GET_TH_CTX(2500U))  /* CT UV threshold is 2500 mV. It is enabled/disabled through OV_UV_EN register. */ \
)

/* Initial value of TH_CTx registers. */
#define MC33771C_TH_CTX_VALUE ( \
    MC33771C_TH_CT1_CT_OV_TH(BCC_GET_TH_CTX(4195U))  /* CT OV threshold is 4195 mV. It is enabled/disabled through OV_UV_EN register. */ | \
    MC33771C_TH_CT1_CT_UV_TH(BCC_GET_TH_CTX(2509U))  /* CT UV threshold is 2509 mV. It is enabled/disabled through OV_UV_EN register. */ \
)

/* Initial value of TH_ANx_OT registers. */
#define MC33771C_TH_ANX_OT_VALUE ( \
    MC33771C_TH_AN1_OT_AN_OT_TH(BCC_GET_TH_ANX(1160U))  /* AN OT threshold is 1160 mV. It is enabled/disabled through FAULT_MASK1 register. */ \
)

/* Initial value of TH_ANx_UT registers. */
#define MC33771C_TH_ANX_UT_VALUE ( \
    MC33771C_TH_AN1_UT_AN_UT_TH(BCC_GET_TH_ANX(3820U))  /* AN UT threshold is 3820 mV. It is enabled/disabled through FAULT_MASK1 register. */ \
)

/* Initial value of TH_ISENSE_OC register. */
#define MC33771C_TH_ISENSE_OC_VALUE ( \
    MC33771C_TH_ISENSE_OC_TH_ISENSE_OC(BCC_GET_TH_ISENSE_OC(0U)) \
)

/* Initial value of TH_COULOMB_CNT_MSB register. */
#define MC33771C_TH_COULOMB_CNT_MSB_VALUE ( \
    MC33771C_TH_COULOMB_CNT_MSB_TH_COULOMB_CNT_MSB(BCC_GET_TH_COULOMB_CNT_MSB((uint32_t)0U)) \
)

/* Initial value of TH_COULOMB_CNT_LSB register. */
#define MC33771C_TH_COULOMB_CNT_LSB_VALUE ( \
    MC33771C_TH_COULOMB_CNT_LSB_TH_COULOMB_CNT_LSB(BCC_GET_TH_COULOMB_CNT_LSB((uint32_t)0U)) \
)

/*******************************************************************************
 * Structure definition
 ******************************************************************************/

/* Structure containing all data related to the Battery Cell Controller. */
typedef struct
{
    bcc_drv_config_t drvConfig;           /* BCC driver configuration. */
} bcc_data_t;

/*******************************************************************************
 * Global variables
 ******************************************************************************/

extern bcc_data_t g_bccData;

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief This function tries to send NOP command to all CIDs.
 * No error is returned.
 */
void sendNops();

/*!
 * @brief This function prints content of registers configured in initialization
 * phase to serial console output.
 *
 * @param cid Cluster Identification Address.
 *
 * @return bcc_status_t Error code.
 */
bcc_status_t printInitialSettings(uint8_t cid);

/*!
 * @brief This function prints content of fault registers to serial console
 * output.
 *
 * @param cid Cluster Identification Address.
 *
 * @return bcc_status_t Error code.
 */
bcc_status_t printFaultRegisters(uint8_t cid);

#endif /* COMMON_H_ */
