#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

sem_t semaphore;

int gpioPin[4] = { 396, 397, 398, 254 };
char statusList[5];
char negativeList[5];
int times; /*跑的次數*/

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
        sleep(1); 
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
        sleep(1);
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
        sleep(1);
    }

    pthread_exit(NULL);
}

void* led_3() {
    int gpio = 398;
    int value = statusList[2] - '0';
    for (int i = 0; i < times * 2; i++) {
        sem_wait(&semaphore);
        gpio_set_value(gpio, value);
        printf("GPIO: %d status: %d\n", gpio, value);
        value = (value + 1) % 2;
        sleep(1);
    }

    pthread_exit(NULL);
}

void* led_4() {
    int gpio = 254;
    int value = statusList[3] - '0';
    for (int i = 0; i < times * 2; i++) {
        sem_wait(&semaphore);
        gpio_set_value(gpio, value);
        printf("GPIO: %d status: %d\n", gpio, value);
        value = (value + 1) % 2;
        sleep(1);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 0;
    }

    for (int i = 0; i < 4; i++) {
        statusList[i] = argv[1][i];
        negativeList[i] = statusList[i] == '0' ? '1' : '0';
    }

    times = argv[2][0] - '0';

    sem_init(&semaphore, 0, 0);

    pthread_t pthreadList[5];
    pthread_create(&pthreadList[0], NULL, status, NULL);
    pthread_create(&pthreadList[1], NULL, led_1, NULL);
    pthread_create(&pthreadList[2], NULL, led_2, NULL);
    pthread_create(&pthreadList[3], NULL, led_3, NULL);
    pthread_create(&pthreadList[4], NULL, led_4, NULL);

    for (int i = 0; i < times * 2; i++) {
        for (int j = 0; j < 5; j++) {
            sem_post(&semaphore);
        }  
    }

    for (int i = 0; i < 4; i++) {
        gpio_set_value(gpioPin[i], 0);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(pthreadList[i], NULL);
    }

    return 0;
}