#include "sra_board.h"
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

#define TAG "MCPWM_SERVO_CONTROL"

#define SERVO_E;																																																																																											 16
#define STRAIGHT 1;
#define BENT 0;

int State = STRAIGHT;
int LastRotation = STRAIGHT;
int adc_value;
int Consec_straight = 0;
int Consec_bent = 0;

//Setting Configuration of Servo Motors
servo_config servo_a = {
	.servo_pin = SERVO_A,
	.min_pulse_width = CONFIG_SERVO_A_MIN_PULSEWIDTH,
	.max_pulse_width = CONFIG_SERVO_A_MAX_PULSEWIDTH,
	.max_degree = CONFIG_SERVO_A_MAX_DEGREE,
	.mcpwm_num = MCPWM_UNIT_0,
	.timer_num = MCPWM_TIMER_0,
	.gen = MCPWM_OPR_A,
};

servo_config servo_b = {
	.servo_pin = SERVO_B,
	.min_pulse_width = CONFIG_SERVO_B_MIN_PULSEWIDTH,
	.max_pulse_width = CONFIG_SERVO_B_MAX_PULSEWIDTH,
	.max_degree = CONFIG_SERVO_B_MAX_DEGREE,
	.mcpwm_num = MCPWM_UNIT_0,
	.timer_num = MCPWM_TIMER_0,
	.gen = MCPWM_OPR_B,
};

servo_config servo_c = {
	.servo_pin = SERVO_C,
	.min_pulse_width = CONFIG_SERVO_C_MIN_PULSEWIDTH,
	.max_pulse_width = CONFIG_SERVO_C_MAX_PULSEWIDTH,
	.max_degree = CONFIG_SERVO_C_MAX_DEGREE,
	.mcpwm_num = MCPWM_UNIT_0,
	.timer_num = MCPWM_TIMER_1,
	.gen = MCPWM_OPR_A,
};

servo_config servo_d = {
	.servo_pin = SERVO_D,
	.min_pulse_width = CONFIG_SERVO_D_MIN_PULSEWIDTH,
	.max_pulse_width = CONFIG_SERVO_D_MAX_PULSEWIDTH,
	.max_degree = CONFIG_SERVO_D_MAX_DEGREE,
	.mcpwm_num = MCPWM_UNIT_0,
	.timer_num = MCPWM_TIMER_1,
	.gen = MCPWM_OPR_B,
};

servo_config servo_e = {
	.servo_pin = SERVO_E,
	.min_pulse_width = 1000,
	.max_pulse_width = 2000,
	.max_degree = 180,
	.mcpwm_num = MCPWM_UNIT_0,
	.timer_num = MCPWM_TIMER_1,
	.gen = MCPWM_OPR_A,
};

void mcpwm_example_servo_control(int State)
{

	if (State == 1 /*&& LastRotation != 18*/)
	// if(adc_value>200)
	
    {
		printf("Straightening...");
		set_angle_servo(&servo_a, 150);
		set_angle_servo(&servo_b, 150);
		set_angle_servo(&servo_c, 150);
		set_angle_servo(&servo_d, 150);
		//set_angle_servo(&servo_e, 180);
		// LastRotation = 1;
	}
	else if (State == 0 /*&& LastRotation != 0*/)
	// else if (adc_value<90)
	
    {
		printf("Bending...");
		set_angle_servo(&servo_a, 0);
		set_angle_servo(&servo_b, 0);
		set_angle_servo(&servo_c, 0);
		set_angle_servo(&servo_d, 0);
		//set_angle_servo(&servo_e, 0);
		// LastRotation = 0;
	}
}

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
	

	printf("%d\n", adc_value);
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

	//enabling servo motors i.e initialization of gpio pins 
	enable_servo();

	
	printf("%d\n", adc_value);

	
}

void loop()
{
	vTaskDelay(10);
}
