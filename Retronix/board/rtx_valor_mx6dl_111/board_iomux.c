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
	IOMUX_PADS(PAD_DISP0_DAT9__WDOG2_B          | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* WDOG_B to reset pmic */
	
	IOMUX_PADS(PAD_EIM_D29__GPIO3_IO29          | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* PWR_RTN_SNS */
	IOMUX_PADS(PAD_NANDF_D2__GPIO2_IO02         | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* SW_POWER_OFF */
			
	/* i2c1 */
	IOMUX_PADS(PAD_CSI0_DAT9__I2C1_SCL          | MUX_PAD_CTRL(0x1b8b1)),
	IOMUX_PADS(PAD_CSI0_DAT8__I2C1_SDA          | MUX_PAD_CTRL(0x1b8b1)),
	IOMUX_PADS(PAD_NANDF_D7__GPIO2_IO07         | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* I2C1_EN */

	/* i2c2 */
	IOMUX_PADS(PAD_KEY_COL3__I2C2_SCL           | MUX_PAD_CTRL(0x1b8b1)),
	IOMUX_PADS(PAD_KEY_ROW3__I2C2_SDA           | MUX_PAD_CTRL(0x1b8b1)),

	/* i2c3 */
	IOMUX_PADS(PAD_GPIO_3__I2C3_SCL             | MUX_PAD_CTRL(0x1b8b1)),
	IOMUX_PADS(PAD_GPIO_6__I2C3_SDA             | MUX_PAD_CTRL(0x1b8b1)),

	/* i2c4 */
	IOMUX_PADS(PAD_GPIO_7__I2C4_SCL             | MUX_PAD_CTRL(0x1b8b1)),
	IOMUX_PADS(PAD_GPIO_8__I2C4_SDA             | MUX_PAD_CTRL(0x1b8b1)),
	
	/* uart 1 */
	IOMUX_PADS(PAD_SD3_DAT6__UART1_RX_DATA      | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_SD3_DAT7__UART1_TX_DATA      | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_KEY_ROW4__GPIO4_IO15         | MUX_PAD_CTRL(NO_PAD_CTRL)), /* UART1_EN*/
	IOMUX_PADS(PAD_SD3_DAT2__GPIO7_IO06         | MUX_PAD_CTRL(NO_PAD_CTRL)), /* PTR_RST*/

	/* uart 2 */
	IOMUX_PADS(PAD_SD3_DAT4__UART2_RX_DATA      | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_SD3_DAT5__UART2_TX_DATA      | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_GPIO_0__GPIO1_IO00           | MUX_PAD_CTRL(NO_PAD_CTRL)), /* UART2_EN*/
	
	/* uart 3 */
	IOMUX_PADS(PAD_EIM_D25__UART3_RX_DATA       | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_EIM_D24__UART3_TX_DATA       | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_SD3_RST__UART3_RTS_B         | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_SD3_DAT3__UART3_CTS_B        | MUX_PAD_CTRL(0x1b0b1)),
	
	/* uart 4 */
	IOMUX_PADS(PAD_CSI0_DAT13__UART4_RX_DATA    | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_CSI0_DAT12__UART4_TX_DATA    | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_CSI0_DAT17__UART4_CTS_B      | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_CSI0_DAT16__UART4_RTS_B      | MUX_PAD_CTRL(0x1b0b1)),
	
	/* uart5 */
	IOMUX_PADS(PAD_CSI0_DAT15__UART5_RX_DATA    | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_CSI0_DAT14__UART5_TX_DATA    | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_CSI0_DAT19__UART5_CTS_B      | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_CSI0_DAT18__UART5_RTS_B      | MUX_PAD_CTRL(0x1b0b1)),
	IOMUX_PADS(PAD_EIM_D31__GPIO3_IO31          | MUX_PAD_CTRL(NO_PAD_CTRL)), /* UART5_EN*/
	
	/*usb otg*/
	IOMUX_PADS(PAD_ENET_RX_ER__USB_OTG_ID       | MUX_PAD_CTRL(0x17059)),     /* USB_OTG_ID */
	IOMUX_PADS(PAD_EIM_D22__GPIO3_IO22          | MUX_PAD_CTRL(0x000b0)),	    /* USB_OTG_PWR_EN */
	IOMUX_PADS(PAD_EIM_D21__USB_OTG_OC          | MUX_PAD_CTRL(0x1b0b0)),		/* USB_OTG_OC */	

	/* usb h1*/
	IOMUX_PADS(PAD_ENET_TXD1__GPIO1_IO29        | MUX_PAD_CTRL(0x000b0)),		/* USB_H1_PWR_EN */
	IOMUX_PADS(PAD_EIM_D30__USB_H1_OC           | MUX_PAD_CTRL(0x1b0b0)),		/* USB_H1_OC */

	/*usdhc1*/
	IOMUX_PADS(PAD_GPIO_1__GPIO1_IO01           | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* SD1_CD */
	IOMUX_PADS(PAD_GPIO_9__GPIO1_IO09           | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* SD1_WP */
	IOMUX_PADS(PAD_SD1_CMD__SD1_CMD             | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD1_CLK__SD1_CLK             | MUX_PAD_CTRL(0x10059)),
	IOMUX_PADS(PAD_SD1_DAT0__SD1_DATA0          | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD1_DAT1__SD1_DATA1          | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD1_DAT2__SD1_DATA2          | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD1_DAT3__SD1_DATA3          | MUX_PAD_CTRL(0x17059)),

	/*usdhc2*/
	IOMUX_PADS(PAD_GPIO_4__GPIO1_IO04           | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* SD2_CD */
	IOMUX_PADS(PAD_GPIO_2__GPIO1_IO02           | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* SD2_CD */
	IOMUX_PADS(PAD_SD2_CMD__SD2_CMD             | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD2_CLK__SD2_CLK             | MUX_PAD_CTRL(0x10059)),
	IOMUX_PADS(PAD_SD2_DAT0__SD2_DATA0          | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD2_DAT1__SD2_DATA1          | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD2_DAT2__SD2_DATA2          | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD2_DAT3__SD2_DATA3          | MUX_PAD_CTRL(0x17059)),

	/*usdhc4*/
	IOMUX_PADS(PAD_SD4_CMD__SD4_CMD             | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD4_CLK__SD4_CLK             | MUX_PAD_CTRL(0x10059)),
	IOMUX_PADS(PAD_SD4_DAT0__SD4_DATA0          | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD4_DAT1__SD4_DATA1          | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD4_DAT2__SD4_DATA2          | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD4_DAT3__SD4_DATA3          | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD4_DAT4__SD4_DATA4          | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD4_DAT5__SD4_DATA5          | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD4_DAT6__SD4_DATA6          | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_SD4_DAT7__SD4_DATA7          | MUX_PAD_CTRL(0x17059)),
	IOMUX_PADS(PAD_GPIO_19__GPIO4_IO05          | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* EMMC_RST */

	/*pmic*/
	IOMUX_PADS(PAD_GPIO_18__GPIO7_IO13          | MUX_PAD_CTRL(NO_PAD_CTRL)),	/* PMIC INT */
};

void board_setup_pads(void)
{
	SETUP_IOMUX_PADS(iomux_v3_pads);
}