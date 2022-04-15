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
			polkit \
			lsb-release \
			packagegroup-core-buildessential "
