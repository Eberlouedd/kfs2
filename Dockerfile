FROM ubuntu:20.04

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential gcc nasm \
    grub-pc-bin grub-common grub2-common \
    xorriso mtools qemu-system-x86 \
    grub-efi-ia32-bin

WORKDIR /kfs
COPY . .

CMD ["make"]
