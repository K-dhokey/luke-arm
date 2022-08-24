//Include all libraries
#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//LED connected to GPIO2
#define BG_LED_1 32 //pins definition in SRA board https://sravjti.in/sra-board-component/pin__defs_8h.html#a59d54556a3e0d1c8355a5081e7dea062
int led_on, led_off; // initializing variables


uint64_t bit_mask = (1ULL << BG_LED_1); //uint64_t is unsigned long long 
//BG_LED1 is greater than 1ULL

esp_err_t enable_LED()  //error handling function for esp while enabling LED
{
    esp_err_t error;  //string error message
    gpio_config_t gpio_config; //GPIO common configuration
    gpio_config.pin_bit_mask = bit_mask; //Bit masking is simply the process of storing data truly as bits
    gpio_config.mode = GPIO_MODE_OUTPUT; //output mode
    gpio_config.pull_up_en = 0; //
    gpio_config.pull_down_en = 0;
    error = gpio_config(&gpio_config);
    return error; //generate error

}

esp_err_t set_led_on()  //generate string error msgs
{
    esp_err_t error;
    error = gpio_set_level(BG_LED_1, 1);
    return error;

}

esp_err_t set_led_off() //generate string error msgs
{
    esp_err_t error;
    error = gpio_set_level(BG_LED_1, 0);
    return error;

}

void app_main()
{
    enable_LED(); //enable the LED
    uint8_t var = 0xFF; //for now, I have not added all LED pins so 0xFF wont work
    //main loop
    while(1)
    {
        set_led_on();  
        vTaskDelay(1000/portTICK_RATE_MS);
		set_led_off();
	    vTaskDelay(1000/portTICK_RATE_MS);


    } 

}
