#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#include<iostream>
int gpio_unexport(unsigned int gpio)
{
    int fd,len;
    char buf[64];

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if(fd < 0) {
        perror("gpio/export");
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);
    return 0;
}