#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

sem_t semaphore;

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
        sem_wait(&semaphore);
        if (i % 2 == 0) {
            printf("Status: %s\n", statusList);
        } else {
            printf("Status: %s\n", negativeList);
        }  
        sem_post(&semaphore);
        usleep(1000*500 + 1000 * (100 - frequent) * 10);
    }

    pthread_exit(NULL);
}

void* led_1() {
    int gpio = 396;
    int value = statusList[0] - '0';
    for (int i = 0; i < times * 2; i++) {
        sem_wait(&semaphore);
        gpio_set_value(gpio, value);
        printf("GPIO: %d status: %d\n", gpio, value);
        value = (value + 1) % 2;
        sem_post(&semaphore);
        usleep(1000*500 + 1000 * (100 - frequent) * 10);
    }

    pthread_exit(NULL);
}

void* led_2() {
    int gpio = 397;
    int value = statusList[1] - '0';
    for (int i = 0; i < times * 2; i++) {
        sem_wait(&semaphore);
        gpio_set_value(gpio, value);
        printf("GPIO: %d status: %d\n", gpio, value);
        value = (value + 1) % 2;
        sem_post(&semaphore);
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

    sem_init(&semaphore, 0, 0);

    pthread_t pthreadList[3];
    pthread_create(&pthreadList[0], NULL, status, NULL);
    pthread_create(&pthreadList[1], NULL, led_1, NULL);
    pthread_create(&pthreadList[2], NULL, led_2, NULL);

    for (int j = 0; j < 3; j++) {
        sem_post(&semaphore);
    } 

    for (int i = 0; i < 2; i++) {
        gpio_set_value(gpioPin[i], 0);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(pthreadList[i], NULL);
    }

    return 0;
}