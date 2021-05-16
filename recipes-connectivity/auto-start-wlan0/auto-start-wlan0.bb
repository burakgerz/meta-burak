DESCRIPTION = "yo"
LICENSE = "CLOSED"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

S = "${WORKDIR}"

inherit systemd
SYSTEMD_SERVICE_${PN} = "auto-start-wlan0.service"

SRC_URI_append = " file://auto-start-wlan0.service \
                   file://interfaces \
"

FILES_${PN} += "${systemd_unitdir}/system/* \
                ${sysconfdir}/network/* \
"

#ALLOW_EMPTY_${PN} = "1"
# if rpm package is empty, it fails with cannot invoke dnf

do_install_append() {
  install -d ${D}${systemd_unitdir}/system/
  install -m 0644 ${WORKDIR}/auto-start-wlan0.service ${D}${systemd_unitdir}/system/
  install -d ${D}${sysconfdir}/network/
  install -m 0644 ${WORKDIR}/interfaces ${D}${sysconfdir}/network/
}

