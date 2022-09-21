// Receiver Code
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
#include "servo.h"
#include "driver/ledc.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "sra_board.h"

#define STRAIGHT 1;
#define BENT 0;

// typedef struct struct_message
// {
//   int servo_1;
//   int servo_2;
//   int servo_3;
//   int servo_4;

// } struct_message;

int State = STRAIGHT;
int LastRotation = STRAIGHT;

// Create a structured object
// struct_message ServoData;

int adc_value;
int Consec_straight = 0;
int Consec_bent = 0;

#define SERVO_MIN_PULSEWIDTH 1000 // Minimum pulse width in microsecond //1000
#define SERVO_MAX_PULSEWIDTH 2500 // Maximum pulse width in microsecond //2000
#define SERVO_MAX_DEGREE 91       // Defining to get the same pulsewidth

static void mcpwm_example_gpio_initialize_1(void)
{

  // printf("initializing mcpwm servo control gpio......\n");
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, 15); // Set GPIO 15 as PWM0A, to which servo is connected
  // // 1. mcpwm gpio initialization
  // mcpwm_example_gpio_initialize_1();

  // 2. initial mcpwm configuration
  // printf("Configuring Initial Parameters of mcpwm......\n");
  mcpwm_config_t pwm_config;
  pwm_config.frequency = 50; // frequency = 50Hz, i.e. for every servo motor time period should be 20ms
  pwm_config.cmpr_a = 0;     // duty cycle of PWMxA = 0
  pwm_config.cmpr_b = 0;     // duty cycle of PWMxb = 0
  pwm_config.counter_mode = MCPWM_UP_COUNTER;
  pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
  mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config); // Configure PWM0A & PWM0B with above settings

  // printf("works");
}

static void mcpwm_example_gpio_initialize_2(void)
{

  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, 18);

  mcpwm_config_t pwm_config;
  pwm_config.frequency = 50;
  pwm_config.cmpr_a = 0;
  pwm_config.cmpr_b = 0;
  pwm_config.counter_mode = MCPWM_UP_COUNTER;
  pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
  mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);
}

static void mcpwm_example_gpio_initialize_3(void)
{

  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, 19);

  mcpwm_config_t pwm_config;
  pwm_config.frequency = 50;
  pwm_config.cmpr_a = 0;
  pwm_config.cmpr_b = 0;
  pwm_config.counter_mode = MCPWM_UP_COUNTER;
  pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
  mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);
}

static void mcpwm_example_gpio_initialize_4(void)
{

  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, 5);

  mcpwm_config_t pwm_config;
  pwm_config.frequency = 50;
  pwm_config.cmpr_a = 0;
  pwm_config.cmpr_b = 0;
  pwm_config.counter_mode = MCPWM_UP_COUNTER;
  pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
  mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);
}

static uint32_t servo_per_degree_init(uint32_t degree_of_rotation)
{
  uint32_t cal_pulsewidth = 0;
  cal_pulsewidth = (SERVO_MIN_PULSEWIDTH + (((SERVO_MAX_PULSEWIDTH - SERVO_MIN_PULSEWIDTH) * (degree_of_rotation)) / (SERVO_MAX_DEGREE)));
  return cal_pulsewidth;
}

void mcpwm_example_servo_control(int State)
{

  uint32_t angle, count;
  if (State == 1 && LastRotation != 1)
  {
    printf("Straightening...");
    for (count = 0; count < 45; count += 3)
    {
      // printf("Angle of rotation servo_1: %d\n", count);
      angle = servo_per_degree_init(count);
      // printf("pulse width: %dus\n", angle);
      mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, angle);
      vTaskDelay(10);
    }
    LastRotation = 1;
  }
  else if (State == 0 && LastRotation != 0)
  {
    printf("Bending...");
    for (count = 45; count > 0; count += 3) // CHANGES TO BE MADE HERE!!
    {
      // printf("Angle of rotation servo_1: %d\n", count);
      angle = servo_per_degree_init(count);
      // printf("pulse width: %dus\n", angle);
      mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, angle);
      vTaskDelay(10);
    }
    LastRotation = 0;
  }
}

// Callback function executed when data is received
void on_receive(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  if (mac == NULL || incomingData == NULL || len <= 0)
  {
    printf("Error while receving data");
    vTaskDelay(100);
    return;
  }
  memcpy(&adc_value, incomingData, sizeof(adc_value));

  if (adc_value > 250)
  {
    if (Consec_straight >= 1)
    {
      State = STRAIGHT;
      mcpwm_example_servo_control(State);
      Consec_bent = 0;
      Consec_straight = 0;
    }
    else
    {
      Consec_straight++;
      Consec_bent = 0;
    }
  }
  else if (adc_value < 90)
  {
    if (Consec_bent >= 1)
    {
      State = BENT;
      mcpwm_example_servo_control(State);
      Consec_bent = 0;
      Consec_straight = 0;
    }
    else
    {
      Consec_bent++;
      Consec_straight = 0;
    }
  }

  printf("The state is %s\n", (State == 1 ? "Straight" : "Bent"));
  vTaskDelay(10);
}

// GPIO PINS INTIALISATION

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
  mcpwm_example_gpio_initialize_1();
  mcpwm_example_gpio_initialize_2();
  mcpwm_example_gpio_initialize_3();
  mcpwm_example_gpio_initialize_4();

  int a = adc_value;
  printf("%d\n", adc_value);

  // printf("Testing servo1 motor.......\n message received from 441793e63490 ");
  // xTaskCreate(mcpwm_example_servo_1_control, "mcpwm_example_servo_1_control", 4096, NULL, 5, NULL);
}

void loop()
{
  // vTaskDelay(10);
}
