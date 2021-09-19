FILESEXTRAPATHS_prepend :="${THISDIR}/files:"
SRC_URI += "file://rpi_3_defconfig"


do_add_custom_defconfig() {
    cp ${WORKDIR}/rpi_3_defconfig ${S}/configs/rpi_3_defconfig
}

addtask add_custom_defconfig before do_configure after do_patch
