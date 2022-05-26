#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#include<iostream>
#include<map>
#include<string>

using namespace std;

void readGPIO(){

}
void setGPIO(unsigned int gpio, string status){
    int io;
    io = open("/dev/demo", O_WRONLY);
    if(io < 0){
        perror("gpio error");
        return;
    }
    char buf[10] = {0};
    if(status =="on"){
        strcpy(buf, (to_string(gpio) + "1").c_str());
    }
    else{
        strcpy(buf, (to_string(gpio) + "0").c_str());
    }
    cout << buf <<endl;
    write(io, buf, 5);
    close(io);
    return;
}

int main(int argc, char *argv[]){
    if (argc == 2) readGPIO();

    if (argc == 3){
        if(std::string(argv[1]) == "LED1") setGPIO(1, std::string(argv[2]));

        if(std::string(argv[1]) == "LED2") setGPIO(2, std::string(argv[2]));

        if(std::string(argv[1]) == "LED3") setGPIO(3, std::string(argv[2]));

        if(std::string(argv[1]) == "LED4") setGPIO(4, std::string(argv[2]));
    }
}