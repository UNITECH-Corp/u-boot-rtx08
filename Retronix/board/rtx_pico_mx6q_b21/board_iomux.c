/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 *
 * Author: Fabio Estevam <fabio.estevam@freescale.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm/arch/clock.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/iomux.h>
#include <asm/arch/mx6-pins.h>
#include <linux/errno.h>
#include <asm/imx-common/iomux-v3.h>

static iomux_v3_cfg_t const iomux_v3_pads[] = {
	
	IOMUX_PADS(PAD_DISP0_DAT9__WDOG2_B        | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* WDOG_B to reset pmic */
	IOMUX_PADS(PAD_EIM_D31__GPIO3_IO31        | MUX_PAD_CTRL(NO_PAD_CTRL)), /* 3.3V Enable */
	IOMUX_PADS(PAD_EIM_OE__GPIO2_IO25         | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* USB_LAN_RESET_B */
	IOMUX_PADS(PAD_EIM_D22__GPIO3_IO22        | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* 3234_EN */

	/* LVDS */
	IOMUX_PADS(PAD_SD1_DAT2__GPIO1_IO19       | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* LVDS_BLEN */
	IOMUX_PADS(PAD_SD1_DAT3__PWM1_OUT         | MUX_PAD_CTRL(0x1b0b1)),
				
	/* GPIO */
	IOMUX_PADS(PAD_EIM_A25__GPIO5_IO02        | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* GPIO1 */
	IOMUX_PADS(PAD_EIM_D18__GPIO3_IO18        | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* GPIO2 */
				
	/* Audio Codec */
	IOMUX_PADS(PAD_GPIO_0__CCM_CLKO1	      | MUX_PAD_CTRL(0x130b0)),		/* SGTL5000 sys_mclk */
	IOMUX_PADS(PAD_SD3_RST__GPIO7_IO08        | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* HEADPHONE_DET */
	IOMUX_PADS(PAD_GPIO_9__GPIO1_IO09         | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* MICROPHONE_DET */
	IOMUX_PADS(PAD_KEY_COL2__GPIO4_IO10       | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* AUD_AMP_STBY_B */

	/* audmux */
	IOMUX_PADS(PAD_CSI0_DAT7__AUD3_RXD        | MUX_PAD_CTRL(0x130b0)),
	IOMUX_PADS(PAD_CSI0_DAT4__AUD3_TXC        | MUX_PAD_CTRL(0x130b0)),
	IOMUX_PADS(PAD_CSI0_DAT5__AUD3_TXD        | MUX_PAD_CTRL(0x110b0)),
	IOMUX_PADS(PAD_CSI0_DAT6__AUD3_TXFS       | MUX_PAD_CTRL(0x130b0)),

	/* enet */
	IOMUX_PADS(PAD_ENET_MDIO__ENET_MDIO	      | MUX_PAD_CTRL(0x1b0b0)),
	IOMUX_PADS(PAD_ENET_MDC__ENET_MDC	      | MUX_PAD_CTRL(0x1b0b0)),
	IOMUX_PADS(PAD_RGMII_TXC__RGMII_TXC	      | MUX_PAD_CTRL(0x1b0b0)),
	IOMUX_PADS(PAD_RGMII_TD0__RGMII_TD0	      | MUX_PAD_CTRL(0x1b0b0)),
	IOMUX_PADS(PAD_RGMII_TD1__RGMII_TD1	      | MUX_PAD_CTRL(0x1b0b0)),
	IOMUX_PADS(PAD_RGMII_TD2__RGMII_TD2	      | MUX_PAD_CTRL(0x1b0b0)),
	IOMUX_PADS(PAD_RGMII_TD3__RGMII_TD3	      | MUX_PAD_CTRL(0x1b0b0)),
	IOMUX_PADS(PAD_RGMII_TX_CTL__RGMII_TX_CTL | MUX_PAD_CTRL(0x1b0b0)),
	IOMUX_PADS(PAD_ENET_REF_CLK__ENET_TX_CLK  | MUX_PAD_CTRL(0x1b0b0)),
	IOMUX_PADS(PAD_RGMII_RXC__RGMII_RXC	      | MUX_PAD_CTRL(0x1b0b0)),
	IOMUX_PADS(PAD_RGMII_RD0__RGMII_RD0	      | MUX_PAD_CTRL(0x1b0b0)),
	IOMUX_PADS(PAD_RGMII_RD1__RGMII_RD1	      | MUX_PAD_CTRL(0x1b0b0)),
	IOMUX_PADS(PAD_RGMII_RD2__RGMII_RD2	      | MUX_PAD_CTRL(0x1b0b0)),
	IOMUX_PADS(PAD_RGMII_RD3__RGMII_RD3	      | MUX_PAD_CTRL(0x1b0b0)),
	IOMUX_PADS(PAD_RGMII_RX_CTL__RGMII_RX_CTL | MUX_PAD_CTRL(0x1b0b0)),
	IOMUX_PADS(PAD_ENET_RXD1__GPIO1_IO26      | MUX_PAD_CTRL(0x000b1)),  /* RGMII_INT */
	IOMUX_PADS(PAD_ENET_CRS_DV__GPIO1_IO25    | MUX_PAD_CTRL(0x1b0b0)),  /* RGMII_nRST */
	/* hdmi */
	IOMUX_PADS(PAD_KEY_ROW2__HDMI_TX_CEC_LINE | MUX_PAD_CTRL(0x1f8b0)),

	/* i2c1 */
	IOMUX_PADS(PAD_CSI0_DAT8__I2C1_SDA        | MUX_PAD_CTRL(0x1b8b1)),
	IOMUX_PADS(PAD_CSI0_DAT9__I2C1_SCL        | MUX_PAD_CTRL(0x1b8b1)),

	/* i2c2 */
	IOMUX_PADS(PAD_KEY_COL3__I2C2_SCL         | MUX_PAD_CTRL(0x1b8b1)),
	IOMUX_PADS(PAD_KEY_ROW3__I2C2_SDA         | MUX_PAD_CTRL(0x1b8b1)),

	/* i2c3 */
	IOMUX_PADS(PAD_GPIO_3__I2C3_SCL           | MUX_PAD_CTRL(0x1b8b1)),
	IOMUX_PADS(PAD_GPIO_6__I2C3_SDA           | MUX_PAD_CTRL(0x1b8b1)),
	
	/* uart 1 */
	IOMUX_PADS(PAD_CSI0_DAT10__UART1_TX_DATA  | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_CSI0_DAT11__UART1_RX_DATA  | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_EIM_D19__UART1_RTS_B       | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_EIM_D20__UART1_CTS_B       | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_EIM_D24__GPIO3_IO24        | MUX_PAD_CTRL(NO_PAD_CTRL)), /* UART1_TM   */
	IOMUX_PADS(PAD_EIM_D23__GPIO3_IO23        | MUX_PAD_CTRL(NO_PAD_CTRL)), /* UART1_M0   */
	IOMUX_PADS(PAD_EIM_D25__GPIO3_IO25        | MUX_PAD_CTRL(NO_PAD_CTRL)), /* UART1_M1   */
	IOMUX_PADS(PAD_KEY_ROW1__GPIO4_IO09       | MUX_PAD_CTRL(NO_PAD_CTRL)), /* UART1_SLEW */

	/* uart 2 */
	IOMUX_PADS(PAD_EIM_D26__UART2_TX_DATA     | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_EIM_D27__UART2_RX_DATA     | MUX_PAD_CTRL(0x1b0b1)),
	
	/* uart5 */
	IOMUX_PADS(PAD_CSI0_DAT15__UART5_TX_DATA  | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_CSI0_DAT14__UART5_RX_DATA  | MUX_PAD_CTRL(0x1b0b1)),
	
	IOMUX_PADS(PAD_NANDF_CS3__GPIO6_IO16      | MUX_PAD_CTRL(NO_PAD_CTRL)), /* UART5_TM   */
	IOMUX_PADS(PAD_NANDF_CLE__GPIO6_IO07      | MUX_PAD_CTRL(NO_PAD_CTRL)), /* UART5_M0   */
	IOMUX_PADS(PAD_NANDF_CS1__GPIO6_IO14      | MUX_PAD_CTRL(NO_PAD_CTRL)), /* UART5_M1   */
	IOMUX_PADS(PAD_KEY_COL1__GPIO4_IO08       | MUX_PAD_CTRL(NO_PAD_CTRL)), /* UART5_SLEW */
	
	/*usb otg*/
	IOMUX_PADS(PAD_GPIO_1__USB_OTG_ID         | MUX_PAD_CTRL(0x17059)),     /* USB_OTG_ID */
	IOMUX_PADS(PAD_KEY_ROW4__USB_OTG_PWR      | MUX_PAD_CTRL(0x000b0)),	    /* USB_OTG_PWR_EN */
	IOMUX_PADS(PAD_EIM_D21__USB_OTG_OC        | MUX_PAD_CTRL(0x1b0b0)),		/* USB_OTG_OC */	

	/* usb h1*/
	IOMUX_PADS(PAD_KEY_COL0__GPIO4_IO06       | MUX_PAD_CTRL(0x000b0)),		/* USB_H1_PWR_EN */
	IOMUX_PADS(PAD_EIM_D30__USB_H1_OC         | MUX_PAD_CTRL(0x1b0b0)),		/* USB_H1_OC */
	IOMUX_PADS(PAD_EIM_CS0__GPIO2_IO23        | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* USB_HUB_RESET_B */

	/*usdhc3*/
	IOMUX_PADS(PAD_NANDF_D0__GPIO2_IO00       | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* SD3_CD */
	IOMUX_PADS(PAD_NANDF_D1__GPIO2_IO01       | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* SD3_WP */
	IOMUX_PADS(PAD_SD3_CMD__SD3_CMD           | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD3_CLK__SD3_CLK           | MUX_PAD_CTRL(0x10059)),
	IOMUX_PADS(PAD_SD3_DAT0__SD3_DATA0        | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD3_DAT1__SD3_DATA1        | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD3_DAT2__SD3_DATA2        | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD3_DAT3__SD3_DATA3        | MUX_PAD_CTRL(0x17059)),

	/*usdhc4*/
	IOMUX_PADS(PAD_SD4_CMD__SD4_CMD           | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD4_CLK__SD4_CLK           | MUX_PAD_CTRL(0x10059)),
	IOMUX_PADS(PAD_SD4_DAT0__SD4_DATA0        | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD4_DAT1__SD4_DATA1        | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD4_DAT2__SD4_DATA2        | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD4_DAT3__SD4_DATA3        | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD4_DAT4__SD4_DATA4        | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD4_DAT5__SD4_DATA5        | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD4_DAT6__SD4_DATA6        | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD4_DAT7__SD4_DATA7        | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_NANDF_ALE__GPIO6_IO08      | MUX_PAD_CTRL(NO_PAD_CTRL)), /* SD4_RESETn */

	/*pcie*/
	IOMUX_PADS(PAD_CSI0_DATA_EN__GPIO5_IO20   | MUX_PAD_CTRL(0x1b0b0)),		/* PCIE_WAKE_B */
	IOMUX_PADS(PAD_GPIO_16__GPIO7_IO11        | MUX_PAD_CTRL(0x1b0b0)),		/* PCIE_DIS_B */
	IOMUX_PADS(PAD_GPIO_17__GPIO7_IO12        | MUX_PAD_CTRL(0x1b0b0)),		/* PCIE_RST */	

	/*mcu*/
	IOMUX_PADS(PAD_NANDF_RB0__GPIO6_IO10      | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* MCU Reset */
	IOMUX_PADS(PAD_NANDF_WP_B__GPIO6_IO09     | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* MCU_UPDATE_PWR_ON */
	IOMUX_PADS(PAD_NANDF_CS0__GPIO6_IO11      | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* MCU_BOOT_EN */
	IOMUX_PADS(PAD_GPIO_4__GPIO1_IO04         | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* MCU_INT */	

	/*pmic*/
	IOMUX_PADS(PAD_GPIO_18__GPIO7_IO13        | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* PMIC INT */

	/*cspi4*/
	IOMUX_PADS(PAD_DISP0_DAT0__ECSPI3_SCLK    | MUX_PAD_CTRL(0x1b0b0)),		/* CSPI3_CLK */
	IOMUX_PADS(PAD_DISP0_DAT1__ECSPI3_MOSI    | MUX_PAD_CTRL(0x1b0b0)),		/* CSPI3_MOSI */
	IOMUX_PADS(PAD_DISP0_DAT2__ECSPI3_MISO    | MUX_PAD_CTRL(0x1b0b0)),		/* CSPI3_MISO */
	IOMUX_PADS(PAD_DISP0_DAT3__GPIO4_IO24     | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* CSPI3_CS0 */
	
	/*flex can1*/
	IOMUX_PADS(PAD_GPIO_7__FLEXCAN1_TX        | MUX_PAD_CTRL(0x1b0b0)),		/* CAN1_TX */
	IOMUX_PADS(PAD_GPIO_8__FLEXCAN1_RX        | MUX_PAD_CTRL(0x1b0b0)),		/* CAN1_RX */
	IOMUX_PADS(PAD_GPIO_5__GPIO1_IO05         | MUX_PAD_CTRL(0x1b0b0)),		/* CAN1_STBY */
	
	/* key */
	IOMUX_PADS(PAD_EIM_D29__GPIO3_IO29        | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* PWR_BTN_SNS */
};

void board_setup_pads(void)
{
	SETUP_IOMUX_PADS(iomux_v3_pads);
}