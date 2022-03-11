#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<errno.h>
#include<unistd.h> // 在 linux 才找的到
#include<fcntl.h>
#include<iostream>
int gpio_set_value(unsigned int gpio, int value)
{
    int fd;
    char buf[64];

    snprintf(buf, sizeof(buf),"/sys/class/gpio/gpio%d/value", gpio);

    fd = open(buf, O_WRONLY);
    if(fd < 0) {
        perror("gpio/set-value");
        return fd;
    }
    if(value == 0)
        write(fd, "0", 2);
    else   
        write(fd, "1", 2);
    
    close(fd);
    return 0;
}