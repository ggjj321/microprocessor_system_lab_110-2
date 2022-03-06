#include"direction.h"
#include"export.h"
#include"unexport.h"
#include"value.h"
#include <vector>
#include <unistd.h>

int main(int argc, char *argv[])
{
    while (1)
    {
        std::string input;
        std::getline(std::cin, input);
        if(input == "b") break;

        std::string space_delimiter = " ";
        std::vector<std::string> words{};
        size_t pos = 0;

        while ((pos = input.find(space_delimiter)) != std::string::npos) {
            words.push_back(input.substr(0, pos));
            input.erase(0, pos + space_delimiter.length());
        }
        words.push_back(input.substr(0, pos));
        input.erase(0, pos + space_delimiter.length());
    
        gpio_export(396); // pin7, led1
        gpio_set_dir(396, "out");
        gpio_export(397); // pin 13, led2
        gpio_set_dir(397, "out");
        gpio_export(429); // pin 19, led3
        gpio_set_dir(429, "out");
        gpio_export(427); // pin 23, led4
        gpio_set_dir(427, "out");

        if(words[0] == "Mode_Shine"){ // task2
            int times = std::stoi(words[1]);
            for(int i = 0; i < times; times ++){
                gpio_set_value(396, 1);
                gpio_set_value(397, 1);
                gpio_set_value(429, 0);
                gpio_set_value(427, 0);

                sleep(0.5);

                gpio_set_value(396, 0);
                gpio_set_value(397, 0);
                gpio_set_value(429, 1);
                gpio_set_value(427, 1);
            }
        }else{ // task1
            if(words[0] == "LED1"){
                if(words[1] == "on"){
                    gpio_set_value(396, 1);
                }else{
                    gpio_set_value(396, 0);
                }
            }
            else if(words[0] == "LED2"){
                if(words[1] == "on"){
                
                    gpio_set_value(397, 1);
                }else{
                    gpio_set_value(397, 0);
                }
            }
            else if(words[0] == "LED2"){
                if(words[1] == "on"){
                    gpio_set_value(429, 1);
                }else{
                    gpio_set_value(429, 0);
                }
            }
            else if(words[0] == "LED3"){
                if(words[1] == "on"){
                    gpio_set_value(427, 1);
                }else{
                    gpio_set_value(427, 0);
                }
            }
        }
    }  
    return 0;
}