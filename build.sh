#! /bin/sh

set -e

export ARCH=arm
#export CROSS_COMPILE=`pwd`/../gcc-linaro-arm-linux-gnueabihf-4.8-2014.04_linux/bin/arm-linux-gnueabihf-
#export CC=`pwd`/../gcc-linaro-arm-linux-gnueabihf-4.8-2014.04_linux/bin/arm-linux-gnueabihf-
#export CROSS_COMPILE=/opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/bin/arm-fsl-linux-gnueabi-
export CROSS_COMPILE=/opt/cross/arm-cortex_a9-linux-gnueabihf-linaro_4.9.2-2014.09/bin/arm-cortex_a9-linux-gnueabihf-
#export CROSS_COMPILE=/opt/cross/gcc-linaro-arm-linux-gnueabihf-4.9-2014.06_linux/bin/arm-linux-gnueabihf-

#U_BOOT_DEFAULT_CONFIG=rtx-a53-mx53_mfg_config
#U_BOOT_DEFAULT_CONFIG=rtx-a53-mx53_config
#U_BOOT_DEFAULT_CONFIG=rtx-bishop-mx53_mfg_config
#U_BOOT_DEFAULT_CONFIG=rtx-q7-mx6s_config
#U_BOOT_DEFAULT_CONFIG=rtx-q7-mx6s_mfg_config
#U_BOOT_DEFAULT_CONFIG=rtx-aeg200-mx51_mfg_config
#U_BOOT_DEFAULT_CONFIG=rtx-aeg200-mx51_config
U_BOOT_DEFAULT_CONFIG=rtx-valor111-mx6dl_config
#U_BOOT_DEFAULT_CONFIG=rtx-valor111-mx6dl_mfg_config
#U_BOOT_DEFAULT_CONFIG=rtx-valor111-mx6dl_iram_config
#U_BOOT_DEFAULT_CONFIG=rtx-smarc-mx6q_config

if [ ! -d out ] ; then
	mkdir -p out
fi

case "${1}" in
	"all")
		rm -rf out
		mkdir -p out
		make ${U_BOOT_DEFAULT_CONFIG}
		make -j8
		cp -f u-boot.imx out/.
		;;
	"clean")
		make clean
		;;
	"distclean")
		make distclean
		rm -rf out
		;;

	*) 
		echo "${0} [all/clean/disclean]"
		exit 1
		;;
esac
