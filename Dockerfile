FROM randomdude/gcc-cross-x86_64-elf

RUN apt-get update

RUN apt-get upgrade -y

RUN apt-get install -y nasm
RUN apt-get install -y qemu-system
RUN apt-get install -y gdb

VOLUME /root/env
WORKDIR /root/env