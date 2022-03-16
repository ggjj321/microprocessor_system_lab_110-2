#include "direction.h"
#include "export.h"
#include "unexport.h"
#include "value.h"
#include<string>

int main(int argc, char *argv[])
{
    gpio_export(396); // pin7, led1
    gpio_set_dir(396, "out");
    gpio_export(397); // pin 13, led2
    gpio_set_dir(397, "out");
    gpio_export(429); // pin 19, led3
    gpio_set_dir(429, "out");
    gpio_export(427); // pin 23, led4
    gpio_set_dir(427, "out");
    if (std::string(argv[1]) == "Mode_Shine")
    { // task2
        int times = std::stoi(std::string(argv[2]));
        std::cout << argv[2] << std::endl;
        for (int i = 0; i < times; times++)
        {
            gpio_set_value(396, 1);
            gpio_set_value(397, 1);
            gpio_set_value(429, 0);
            gpio_set_value(427, 0);

            sleep(0.3);

            gpio_set_value(396, 0);
            gpio_set_value(397, 0);
            gpio_set_value(429, 1);
            gpio_set_value(427, 1);
            
            sleep(0.3);
        }
    }
    else
    { // task1
        if (std::string(argv[1]) == "LED1")
        {
            if (std::string(argv[2]) == "on")
            {
                gpio_set_value(396, 1);
            }
            else
            {
                gpio_set_value(396, 0);
            }
        }
        else if (std::string(argv[1]) == "LED2")
        {
            if (std::string(argv[2]) == "on")
            {
                gpio_set_value(397, 1);
            }
            else
            {
                gpio_set_value(397, 0);
            }
        }
        else if (std::string(argv[1]) == "LED2")
        {
            if (std::string(argv[2]) == "on")
            {
                gpio_set_value(429, 1);
            }
            else
            {
                gpio_set_value(429, 0);
            }
        }
        else if (std::string(argv[1]) == "LED3")
        {
            if (std::string(argv[2]) == "on")
            {
                gpio_set_value(427, 1);
            }
            else
            {
                gpio_set_value(427, 0);
            }
        }
    }
    return 0;
}