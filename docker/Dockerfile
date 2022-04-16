FROM ubuntu:18.04

RUN  apt-get update && \
     apt-get install --no-install-recommends --yes \
     gawk \ 
     wget \ 
     git-core \ 
     diffstat \ 
     unzip \ 
     texinfo \ 
     gcc-multilib \
     build-essential \
     chrpath \ 
     socat \ 
     cpio \ 
     python3 \ 
     python3-pip \
     python3-pexpect \
     xz-utils \
     debianutils \ 
     iputils-ping \ 
     python3-git \
     python3-jinja2 \
     libegl1-mesa \
     libsdl1.2-dev \
     pylint3 xterm \
     vim \
     sudo 

ARG USER=build

RUN useradd -s /bin/bash -G sudo $USER && \
    passwd -d $USER && \
    echo "%sudo ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers && \
    echo "alias ..='cd ..'" >> /home/$USER/.bashrc && \
    echo "alias ll='ls -l'" >> /home/$USER/.bashrc && \
    mkdir -p /home/$USER/workspace && \
    cd /home/$USER/workspace && \
    git clone https://git.yoctoproject.org/poky && \
    git clone https://git.openembedded.org/meta-openembedded && \
    git clone https://github.com/agherzan/meta-raspberrypi.git && \
    git clone https://github.com/burakgerz/meta-burak.git && \
    chown -R $USER /home/$USER 


ENTRYPOINT ["/bin/bash"]
