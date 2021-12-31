/* Terminal Interface to ESP8266

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/uart.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "nvs.h"
#include "nvs_flash.h"

#include "argparser.h"

static TimerHandle_t system_monitor_timer;

static EventGroupHandle_t wifi_event_group;
#define CONNECTED_BIT BIT0
#define CONNECTION_FAILED BIT1

static void wifi_event_handler(void * arg, esp_event_base_t event_base, int32_t event_id, void * event_data) {
	if (event_base == WIFI_EVENT) {
		if (event_id == WIFI_EVENT_STA_START) {
			esp_wifi_connect();
		} else
		if (event_id == WIFI_EVENT_STA_DISCONNECTED) {
			// SET CONNECTION FAILED BIT...
			xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
		}
	} else
	if (event_base == IP_EVENT) {
		if (event_id == IP_EVENT_STA_GOT_IP) {
			xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
		}
	}
}

static esp_err_t wifi_join() {
	esp_err_t rc = ESP_OK;
	wifi_mode_t wifi_mode;
	// Is it already connected?
	int bits = xEventGroupGetBits(wifi_event_group);
	if (bits & CONNECTED_BIT) {
		return ESP_OK;
	}
	{
		// Is there an ssid set?
		wifi_config_t wifi_config = { 0 };
		rc = esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
		if (rc == ESP_OK && wifi_config.sta.ssid[0] == '\0') {
			return ESP_FAIL;
		}
	}
	// Allow the part to be in both AP and STA mode
	rc = esp_wifi_get_mode(&wifi_mode);
	if (rc == ESP_OK && !(wifi_mode & WIFI_MODE_STA)) {
		wifi_mode = wifi_mode | WIFI_MODE_STA;
		rc = esp_wifi_set_mode(wifi_mode);
	}
	return rc;
}

static void system_monitor_callback(TimerHandle_t xTimer) {
	if (wifi_join() == ESP_OK) {
		uart_write_bytes(UART_NUM_0, "ROK\r\n", 5);
	}
}

static void command_process(int argc, char *argv[]) {
	esp_err_t err;
	if (strcmp(argv[0], "wifi") == 0) {
		if (argc >= 3 && strcmp(argv[1], "config") == 0) {
			if (strcmp(argv[2], "dump") == 0) {
				wifi_config_t config = {};
				err = esp_wifi_get_config(ESP_IF_WIFI_STA, &config);
				if (err != ESP_OK) {
					uart_write_bytes(UART_NUM_0, "ERR\r\n", 5);
					return;
				}
				uart_write_bytes(UART_NUM_0, (char *)config.sta.ssid, strlen((char *)config.sta.ssid));
				uart_write_bytes(UART_NUM_0, "\r\n", 2);
			}
		} else
		if (strcmp(argv[1], "join") == 0) {
			wifi_config_t wifi_config = { 0 };
			int timeout_ms = 10000;
			wifi_mode_t wifi_mode = WIFI_MODE_NULL;
			if (esp_wifi_get_mode(&wifi_mode) == ESP_OK && wifi_mode != WIFI_MODE_STA) {
				ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
			}
			if (argc == 4) {
				strncpy((char *)wifi_config.sta.ssid, argv[2], sizeof(wifi_config.sta.ssid));
				strncpy((char *)wifi_config.sta.password, argv[3], sizeof(wifi_config.sta.password));
				ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
			}
			if (wifi_mode == WIFI_MODE_STA) {
				ESP_ERROR_CHECK(esp_wifi_connect());
			}
			int bits = xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT,
					pdFALSE, pdFALSE, timeout_ms / portTICK_PERIOD_MS);
			if (bits & CONNECTED_BIT) {
				uart_write_bytes(UART_NUM_0, "CON\r\n", 5);
			} else {
				uart_write_bytes(UART_NUM_0, "TOC\r\n", 5);
			}
		} else
		if (strcmp(argv[1], "status") == 0) {
			int bits = xEventGroupGetBits(wifi_event_group);
			if (bits & CONNECTED_BIT) {
				uart_write_bytes(UART_NUM_0, "CON\r\n", 5);
			} else {
				uart_write_bytes(UART_NUM_0, "DIS\r\n", 5);
			}
		} else
		if (argc == 4 && strcmp(argv[1], "on") == 0) {
			uart_write_bytes(UART_NUM_0, "wifion?\r\n", 9);
		} else {
			uart_write_bytes(UART_NUM_0, "eh?\r\n", 5);
		}
	} else
	if (strcmp(argv[0], "set") == 0) {
		xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
		//
	} else
	if (strcmp(argv[0], "get") == 0) {
		//
	} else
	if (strcmp(argv[0], "unset") == 0) {
		xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
	}
}

/**
 * This is an example which echos any data it receives on UART0 back to the sender,
 * with hardware flow control turned off. It does not use UART driver event queue.
 *
 * - Port: UART0
 * - Receive (Rx) buffer: on
 * - Transmit (Tx) buffer: off
 * - Flow control: off
 * - Event queue: off
 */

#define BUF_SIZE (1024)

static void command_task() {
	uint8_t * pos;
	uint8_t * data;
	char * arg[ARGPARSER_MAXARGS];
	int arg_count;
	// Configure parameters of an UART driver,
	// communication pins and install the driver
	uart_config_t uart_config = {
		.baud_rate = 74880,
		.data_bits = UART_DATA_8_BITS,
		.parity    = UART_PARITY_DISABLE,
		.stop_bits = UART_STOP_BITS_1,
		.flow_ctrl = UART_HW_FLOWCTRL_DISABLE
	};
	uart_param_config(UART_NUM_0, &uart_config);
	uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL, 0);

	// Configure a temporary buffer for the incoming data
	data = (uint8_t *) malloc(BUF_SIZE);
	pos = data;

	// Disable Buffering (used for printf)
	//setvbuf(stdin, NULL, _IONBF, 0);
	//setvbuf(stdout, NULL, _IONBF, 0);
	while (1) {
		// Read data from the UART
		int len = uart_read_bytes(UART_NUM_0, pos, BUF_SIZE, 20 / portTICK_RATE_MS);
		// Write data back to the UART
		uart_write_bytes(UART_NUM_0, (const char *)pos, len);

		if (len > 0) {
			pos = pos + len;
			len = argparser_check_for_eol((char *)data, (char *)pos);
			if (len) {
				arg_count = argparser_parse(arg, (char *)data);
				command_process(arg_count, arg);
				pos = data;
			}
		}
	}
}

static void initialise_nvs() {
	esp_err_t err = nvs_flash_init();
	if (err == ESP_ERR_NVS_NO_FREE_PAGES) {
		ESP_ERROR_CHECK(nvs_flash_erase());
		err = nvs_flash_init();
	}
	ESP_ERROR_CHECK(err);
}

static void initialise_wifi() {
	tcpip_adapter_init();
	wifi_event_group = xEventGroupCreate();
	//ESP_ERROR_CHECK(esp_event_loop_init(wifi_event_handler, NULL));

	ESP_ERROR_CHECK(esp_event_loop_create_default());
	ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
	ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL));

	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_NULL));
	ESP_ERROR_CHECK(esp_wifi_start());
}

void app_main() {
	initialise_nvs();
	initialise_wifi();
	xTaskCreate(command_task, "command_task", 1024, NULL, 10, NULL);
	system_monitor_timer = xTimerCreate("system_monitor", 10000 / portTICK_RATE_MS, pdTRUE, (void *)0, &system_monitor_callback);
	xTimerStart(system_monitor_timer, 0);
}

