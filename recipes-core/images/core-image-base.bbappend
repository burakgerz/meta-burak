IMAGE_FEATURES_append = " dev-pkgs \
			  tools-debug "

IMAGE_INSTALL_append = " \
			auto-start-wlan0 \
			openssh \
			util-linux \
			coreutils \
			procps \
			dtc \
			dbus \
			lsb_release \
			polkit \
			packagegroup-core-buildessential "
