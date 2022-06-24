#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

pthread_mutex_t mutex;

int gpioPin[2] = { 396, 397};
char statusList[3];
char negativeList[3];
int times; /*跑的次數*/
int frequent;

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

void* status(){
    for (int i = 0; i < times * 2; i++) {
        pthread_mutex_lock(&mutex);
        if (i % 2 == 0) {
            printf("Status: %s\n", statusList);
        } else {
            printf("Status: %s\n", negativeList);
        }  
        pthread_mutex_unlock(&mutex);
        usleep(1000*500 + 1000 * (100 - frequent) * 10);
    }

    pthread_exit(NULL);
}

void* led_1() {
    int gpio = 396;
    int value = statusList[0] - '0';
    for (int i = 0; i < times * 2; i++) {
        pthread_mutex_lock(&mutex);
        gpio_set_value(gpio, value);
        printf("GPIO: %d status: %d\n", gpio, value);
        value = (value + 1) % 2;
        pthread_mutex_unlock(&mutex);
        usleep(1000*500 + 1000 * (100 - frequent) * 10);
    }

    pthread_exit(NULL);
}

void* led_2() {
    int gpio = 397;
    int value = statusList[1] - '0';
    for (int i = 0; i < times * 2; i++) {
        pthread_mutex_lock(&mutex);
        gpio_set_value(gpio, value);
        printf("GPIO: %d status: %d\n", gpio, value);
        value = (value + 1) % 2;
        pthread_mutex_unlock(&mutex);
        usleep(1000*500 + 1000 * (100 - frequent) * 10);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < 2; i++) {
        statusList[i] = argv[1][i];
        negativeList[i] = statusList[i] == '0' ? '1' : '0';
    }

    times = argv[2][0] - '0';
	
    frequent = atoi(argv[3]);

    pthread_mutex_init(&mutex, 0);

    pthread_t pthreadList[3];
    pthread_create(&pthreadList[0], NULL, status, NULL);
    pthread_create(&pthreadList[1], NULL, led_1, NULL);
    pthread_create(&pthreadList[2], NULL, led_2, NULL);

    for (int i = 0; i < 2; i++) {
        gpio_set_value(gpioPin[i], 0);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(pthreadList[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}