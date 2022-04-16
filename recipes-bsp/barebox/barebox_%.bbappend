FILESEXTRAPATHS_prepend :="${THISDIR}/files:"
SRC_URI += "file://rpi_defconfig "

export ARCH="arm"

do_add_custom_defconfig() {
    export ARCH="arm"
    cp ${WORKDIR}/rpi_defconfig ${S}/arch/arm/configs/rpi_defconfig
}
addtask add_custom_defconfig before do_configure after do_patch

COMPATIBLE_MACHINE = "raspberrypi3-64"
