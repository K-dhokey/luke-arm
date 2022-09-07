//Transmitter Code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_now.h"

#define TAG "ESP_NOW"

uint8_t esp_1[6] = {0x3c, 0x61, 0x5, 0x12, 0xde, 0x94};
uint8_t esp_2[6] = {0x44, 0x17, 0x93, 0xe6, 0x34, 0x90};

int int_value;

typedef struct struct_message 
{
int a;
} struct_message;

// Create a struct_message called mydata
struct_message mydata;

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

  for (int i = 0; i < 1; i++)
  {
    sprintf(send_buffer, "Hello from %s message %d", my_mac_str, i);
    mydata.a = 30; 
    ESP_ERROR_CHECK(esp_now_send(esp_1,(uint8_t *)&mydata, sizeof(mydata)));
    vTaskDelay(pdMS_TO_TICKS(1000));
  }

}
