FILESEXTRAPATHS_prepend :="${THISDIR}/files:"
SRC_URI += "file://rpi_arm64_defconfig \
            file://0001-Add-Kconfig-option-to-enable-bcm2835_wdt-driver.patch \
	    file://bcm2835_wdt.c \
"


do_add_custom_defconfig_and_driver() {
    cp ${WORKDIR}/rpi_arm64_defconfig ${S}/configs/rpi_arm64_defconfig
    cp ${WORKDIR}/bcm2835_wdt.c ${S}/drivers/watchdog/bcm2835_wdt.c
}

addtask add_custom_defconfig_and_driver before do_configure after do_patch

