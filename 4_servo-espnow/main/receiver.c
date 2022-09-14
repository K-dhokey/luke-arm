//Receiver Code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_now.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_attr.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"


typedef struct struct_message 
{
  int servo_1;
  int servo_2;
  int servo_3;
  int servo_4;

} struct_message;

// Create a structured object
struct_message ServoData;


 
#define SERVO_MIN_PULSEWIDTH 1000 //Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH 2000 //Maximum pulse width in microsecond
#define SERVO_MAX_DEGREE 90       //Defining to get the same pulsewidth

//Callback function executed when data is received
void on_receive(const uint8_t * mac, const uint8_t *incomingData, int len)
{
  if(mac == NULL || incomingData == NULL || len <= 0){
    printf("Error while receving data");
    vTaskDelay(100);
    return;
  }
  memcpy(&ServoData, incomingData, sizeof(ServoData));
  printf("Data received: ");
  printf("%d\n",len);
  printf("%d\n", ServoData.servo_1);
  printf("%d\n", ServoData.servo_2);
  printf("%d\n", ServoData.servo_3);
  printf("%d\n", ServoData.servo_4);
  
}



//GPIO PINS INTIALISATION
static void mcpwm_example_gpio_initialize_1 (void)
{
    printf("initializing mcpwm servo control gpio......\n");
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, 15);    //Set GPIO 15 as PWM0A, to which servo is connected

}

static void mcpwm_example_gpio_initialize_2 (void)
{
    printf("initializing mcpwm servo control gpio......\n");
    mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM0A, 18);    //Set GPIO 18 as PWM0A, to which servo is connected
}

static void mcpwm_example_gpio_initialize_3 (void)
{
    printf("initializing mcpwm servo control gpio......\n");
    mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM0A, 19);    //Set GPIO 19 as PWM0A, to which servo is connected
}

static void mcpwm_example_gpio_initialize_4 (void)
{
    printf("initializing mcpwm servo control gpio......\n");
    mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM0A, 5);    //Set GPIO 5 as PWM0A, to which servo is connected
}


static uint32_t servo_per_degree_init(uint32_t degree_of_rotation)
{
    uint32_t cal_pulsewidth = 0;
    cal_pulsewidth = (SERVO_MIN_PULSEWIDTH + (((SERVO_MAX_PULSEWIDTH - SERVO_MIN_PULSEWIDTH) * (degree_of_rotation)) / (SERVO_MAX_DEGREE)));
    return cal_pulsewidth;
}


void mcpwm_example_servo_1_control(void *arg)
{
    uint32_t angle, count;
    //1. mcpwm gpio initialization
    mcpwm_example_gpio_initialize_1();

    //2. initial mcpwm configuration
    printf("Configuring Initial Parameters of mcpwm......\n");
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 50;    //frequency = 50Hz, i.e. for every servo motor time period should be 20ms
    pwm_config.cmpr_a = 0;    //duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;    //duty cycle of PWMxb = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);    //Configure PWM0A & PWM0B with above settings
    printf("%d\n", ServoData.servo_1);
    while (1) {
        for (count = 0; count < ServoData.servo_1; count++) {
            //printf("Angle of rotation servo_1: %d\n", count);
            angle = servo_per_degree_init(count);
            //printf("pulse width: %dus\n", angle);
            mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, angle);
            vTaskDelay(10);     //Add delay, since it takes time for servo to rotate, generally 100ms/60degree rotation at 5V
        }
        // vTaskDelay(100);
    }
}



void mcpwm_example_servo_2_control(void *arg)
{
    uint32_t angle_1, count_1;
    mcpwm_example_gpio_initialize_2();

    printf("Configuring Initial Parameters of mcpwm......\n");
     mcpwm_config_t pwm_config;
     pwm_config.frequency = 50;    //frequency = 50Hz, i.e. for every servo motor time period should be 20ms
     pwm_config.cmpr_a = 0;    //duty cycle of PWMxA = 0
     pwm_config.cmpr_b = 0;    
     pwm_config.counter_mode = MCPWM_UP_COUNTER;
     pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_1 , MCPWM_TIMER_0, &pwm_config);    
    printf("%d\n", ServoData.servo_2);
    while (1) {
        
        for (count_1 = 0; count_1 < ServoData.servo_2; count_1++) {
            
            angle_1 = servo_per_degree_init(count_1);
            
            mcpwm_set_duty_in_us(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_A, angle_1);
            vTaskDelay(10);     
        }
    }
}


void mcpwm_example_servo_3_control(void *arg)
{
    uint32_t angle_2, count_2;
    mcpwm_example_gpio_initialize_3();

    printf("Configuring Initial Parameters of mcpwm......\n");
     mcpwm_config_t pwm_config;
     pwm_config.frequency = 50;    //frequency = 50Hz, i.e. for every servo motor time period should be 20ms
     pwm_config.cmpr_a = 0;    //duty cycle of PWMxA = 0
     pwm_config.cmpr_b = 0;    
     pwm_config.counter_mode = MCPWM_UP_COUNTER;
     pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_1 , MCPWM_TIMER_0, &pwm_config);    
    printf("%d\n", ServoData.servo_3);
    while (1) {
        
        for (count_2 = 0; count_2 < ServoData.servo_3; count_2++) {
            
            angle_2 = servo_per_degree_init(count_2);
            
            mcpwm_set_duty_in_us(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_A, angle_2);
            vTaskDelay(10);     
        }
    }
}


void mcpwm_example_servo_4_control(void *arg)
{
    uint32_t angle_3, count_3;
    mcpwm_example_gpio_initialize_4();

    printf("Configuring Initial Parameters of mcpwm......\n");
     mcpwm_config_t pwm_config;
     pwm_config.frequency = 50;    //frequency = 50Hz, i.e. for every servo motor time period should be 20ms
     pwm_config.cmpr_a = 0;    //duty cycle of PWMxA = 0
     pwm_config.cmpr_b = 0;    
     pwm_config.counter_mode = MCPWM_UP_COUNTER;
     pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_1 , MCPWM_TIMER_0, &pwm_config);    
    printf("%d\n", ServoData.servo_4);
    while (1) {
        
        for (count_3 = 0; count_3 < ServoData.servo_4; count_3++) {
            
            angle_3 = servo_per_degree_init(count_3);
            
            mcpwm_set_duty_in_us(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_A, angle_3);
            vTaskDelay(10);     
        }
    }
}

void app_main(void)
{
  nvs_flash_init();
  tcpip_adapter_init();
  ESP_ERROR_CHECK(esp_event_loop_create_default());
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&cfg));
  ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK(esp_wifi_start());

  ESP_ERROR_CHECK(esp_now_init());
  ESP_ERROR_CHECK(esp_now_register_recv_cb(on_receive));

    
    printf("Testing servo1 motor.......\n message received from 441793e63490 ");
    xTaskCreate(mcpwm_example_servo_1_control, "mcpwm_example_servo_1_control", 4096, NULL, 5, NULL);
    
    printf("Testing servo2 motor.......\n message received from 441793e63490 ");
    xTaskCreate(mcpwm_example_servo_2_control, "mcpwm_example_servo_2_control", 4096, NULL, 6, NULL);

    printf("Testing servo2 motor.......\n message received from 441793e63490 ");
    xTaskCreate(mcpwm_example_servo_3_control, "mcpwm_example_servo_3_control", 4096, NULL, 7, NULL);

    printf("Testing servo2 motor.......\n message received from 441793e63490 ");
    xTaskCreate(mcpwm_example_servo_4_control, "mcpwm_example_servo_4_control", 4096, NULL, 8, NULL);



}

void loop() 
{
  vTaskDelay(10);
}
