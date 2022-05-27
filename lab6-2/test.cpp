#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#include<iostream>
#include<map>
#include<string>
#include <fstream>

using namespace std;

void readGPIO(unsigned int gpio){
    cout << "input: " << gpio << endl;

    ifstream ifs;
    char buf[64];

    snprintf(buf, sizeof(buf),"/sys/class/gpio/gpio%d/value", gpio);

    ifs.open(buf);

    char value[2];

    ifs.read(value, 2);
    cout << "LED1(GPIO=" << gpio << ")Status : " << value[0] << endl;
    
    ifs.close();
    return;
}
int setGPIO(unsigned int gpio, string status){
    int io;
    FILE *fp = fopen("/dev/demo", "w+");
    if(fp == NULL) {
        printf("can't open device!\n");
        return 0;
    }
    char buf[3];
    if(status =="on"){
        strcpy(buf, (to_string(gpio) + "1").c_str());
    }
    else{
        strcpy(buf, (to_string(gpio) + "0").c_str());
    }
    fwrite(buf, sizeof(buf), 1, fp); //write
    fread(buf, sizeof(buf), 1, fp); //read
    fclose(fp);
    return 0;
}

int main(int argc, char *argv[]){
    if (argc == 2){
        if(std::string(argv[1]) == "LED1") readGPIO(396);

        if(std::string(argv[1]) == "LED2") readGPIO(397);

        if(std::string(argv[1]) == "LED3") readGPIO(398);

        if(std::string(argv[1]) == "LED4") readGPIO(254);
    }

    if (argc == 3){
        if(std::string(argv[1]) == "LED1") setGPIO(1, std::string(argv[2]));

        if(std::string(argv[1]) == "LED2") setGPIO(2, std::string(argv[2]));

        if(std::string(argv[1]) == "LED3") setGPIO(3, std::string(argv[2]));

        if(std::string(argv[1]) == "LED4") setGPIO(4, std::string(argv[2]));
    }
}