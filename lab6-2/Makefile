obj-m :=demo.o

kernel_DIR :=/usr/src/linux-headers-4.9.201-tegra-ubuntu18.04_aarch64/kernel-4.9/

PWD := $(shell pwd)

all:
	g++ -o lab6 test.cpp	
	make -C $(kernel_DIR) SUBDIRS=$(PWD)
	sudo insmod demo.ko
clean:
	sudo rmmod demo.ko

.PHONY:
	clean