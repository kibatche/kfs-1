FROM ubuntu:24.04

RUN apt-get update \
	&& apt-get install -y --no-install-recommends \
		build-essential \
		curl \
		git \
		make \
		qemu-system \
		qemu-system-gui \
		vim \
		xorriso \
	&& apt-get clean && rm -rf /var/lib/apt/lists/*

COPY i386-elf-gcc ./
RUN chmod +x i386-elf-gcc
