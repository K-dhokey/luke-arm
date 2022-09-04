#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_attr.h"

#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"


#include <stdlib.h>
#include <string.h>

#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_now.h"
#define TAG "ESP_NOW"

uint8_t esp_1[6] = {0x3c, 0x61, 0x5, 0x12, 0xde, 0x94};
uint8_t esp_2[6] = {0x44, 0x17, 0x93, 0xe6, 0x34, 0x90};

char *mac_to_str(char *buffer, uint8_t *mac)
{
  sprintf(buffer, "%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return buffer;
}

void on_sent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  char buffer[13];
  switch (status)
  {
  case ESP_NOW_SEND_SUCCESS:
    ESP_LOGI(TAG, "message sent to %s", mac_to_str(buffer,(uint8_t *) mac_addr));
    break;
  case ESP_NOW_SEND_FAIL:
    ESP_LOGE(TAG, "message sent to %s failed", mac_to_str(buffer,(uint8_t *) mac_addr));
    break;
  }
}

void on_receive(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
  char buffer[13];
  ESP_LOGI(TAG, "got message from %s", mac_to_str(buffer, (uint8_t *)mac_addr));

  printf("message: %.*s\n", data_len, data);
}

//You can get these value from the datasheet of servo you use, in general pulse width varies between 1000 to 2000 mocrosecond
#define SERVO_MIN_PULSEWIDTH 1000 //Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH 2000 //Maximum pulse width in microsecond
#define SERVO_MAX_DEGREE 91 //Maximum angle in degree upto which servo can rotate





    


static void mcpwm_example_gpio_initialize(void)
{
    printf("initializing mcpwm servo control gpio......\n");
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, 18);    //Set GPIO 18 as PWM0A, to which servo is connected
}

/**
 * @brief Use this function to calcute pulse width for per degree rotation
 *
 * @param  degree_of_rotation the angle in degree to which servo has to rotate
 *
 * @return
 *     - calculated pulse width
 */
static uint32_t servo_per_degree_init(uint32_t degree_of_rotation)
{
    uint32_t cal_pulsewidth = 0;
    cal_pulsewidth = (SERVO_MIN_PULSEWIDTH + (((SERVO_MAX_PULSEWIDTH - SERVO_MIN_PULSEWIDTH) * (degree_of_rotation)) / (SERVO_MAX_DEGREE)));
    return cal_pulsewidth;
}

/**
 * @brief Configure MCPWM module
 */
void mcpwm_example_servo_control(void *arg)
{
    uint32_t angle, count;
    //1. mcpwm gpio initialization
    mcpwm_example_gpio_initialize();

    //2. initial mcpwm configuration
    printf("Configuring Initial Parameters of mcpwm......\n");
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 50;    //frequency = 50Hz, i.e. for every servo motor time period should be 20ms
    pwm_config.cmpr_a = 0;    //duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;    //duty cycle of PWMxb = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);    //Configure PWM0A & PWM0B with above settings
    while (1) {
        for (count = 0; count < SERVO_MAX_DEGREE; count++) {
            printf("Angle of rotation: %d\n", count);
            angle = servo_per_degree_init(count);
            printf("pulse width: %dus\n", angle);
            mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, angle);
            vTaskDelay(10);     //Add delay, since it takes time for servo to rotate, generally 100ms/60degree rotation at 5V
        }
    }
}


void app_main(void)
{
  uint8_t my_mac[6];
  esp_efuse_mac_get_default(my_mac);
  char my_mac_str[13];
  ESP_LOGI(TAG, "My mac %s", mac_to_str(my_mac_str, my_mac));
  bool is_current_esp1 = memcmp(my_mac, esp_1, 6) == 0;
  uint8_t *peer_mac = is_current_esp1 ? esp_2 : esp_1;

  nvs_flash_init();
  tcpip_adapter_init();
  ESP_ERROR_CHECK(esp_event_loop_create_default());
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&cfg));
  ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK(esp_wifi_start());

  ESP_ERROR_CHECK(esp_now_init());
  ESP_ERROR_CHECK(esp_now_register_send_cb(on_sent));
  ESP_ERROR_CHECK(esp_now_register_recv_cb(on_receive));

  esp_now_peer_info_t peer;
  memset(&peer, 0, sizeof(esp_now_peer_info_t));
  memcpy(peer.peer_addr, peer_mac, 6);

  esp_now_add_peer(&peer);

  char send_buffer[250];

  for (int i = 0; i < 200; i++)
  {
    sprintf(send_buffer, "Hello from %s message %d", my_mac_str, i);
    ESP_ERROR_CHECK(esp_now_send(NULL, (uint8_t *)send_buffer, strlen(send_buffer)));
    vTaskDelay(pdMS_TO_TICKS(1000));
  }


    printf("Testing servo motor.......\n");
    xTaskCreate(mcpwm_example_servo_control, "mcpwm_example_servo_control", 4096, NULL, 5, NULL);
    ESP_ERROR_CHECK(esp_now_deinit());
    ESP_ERROR_CHECK(esp_wifi_stop());
}
