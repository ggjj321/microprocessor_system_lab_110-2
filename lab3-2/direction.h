#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<errno.h>
#include<unistd.h> // 在 linux 才找的到
#include<fcntl.h>
#include<iostream>
int gpio_set_dir(unsigned int gpio, std::string dirStatus)
{
    int fd;
    char buf[64];

    snprintf(buf, sizeof(buf),"/sys/class/gpio/gpio%d/direction", gpio);

    fd = open(buf, O_WRONLY);
    if(fd < 0) {
        perror("gpio/direction");
        return fd;
    }

    if (dirStatus == "out")
        write(fd, "out", 4);
    else
        write(fd, "in", 3);

    close(fd);
    return 0;
}