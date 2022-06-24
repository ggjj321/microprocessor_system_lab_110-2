CROSS_COMPILE = aarch64-linux-gnu-
CXX = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)ld
CXXFLAGS = -std=c++11

obj-m :=demo.o

kernel_DIR :=/usr/src/linux-headers-4.9.201-tegra-ubuntu18.04_aarch64/kernel-4.9/

PWD := $(shell pwd)

all:
	g++ -o drive test.cpp	
	make -C $(kernel_DIR) SUBDIRS=$(PWD)
	sudo insmod demo.ko
	gcc semaphore.c -lpthread -o sempahore
	gcc mutex.c -lpthread -o mutex
	sudo python3 app.py
clean:
	sudo rmmod demo.ko

.PHONY:
	clean