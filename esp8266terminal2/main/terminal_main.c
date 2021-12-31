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
#include "lwip/sockets.h"
#include "lwip/api.h"

#include "argparser.h"

static const char * TAG = "terminal";

static TimerHandle_t system_monitor_timer;

static nvs_handle_t nvs_config_handle;

static EventGroupHandle_t wifi_event_group;
#define CONNECTED_BIT BIT0
#define CONNECTION_FAILED BIT1

static ip_addr_t sta_ip_addr;
static struct netconn * tcp_server_handle;

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
			ip_event_got_ip_t * ip_event = (ip_event_got_ip_t *)event_data;
			ESP_LOGI(TAG, "got ip: %s", ip4addr_ntoa(&ip_event->ip_info.ip));
			sta_ip_addr = ip_event->ip_info.ip;
			xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
		}
	}
}

#define WIFI_STA_CONNECTING 1
#define WIFI_STA_CONNECTED 2
#define WIFI_STA_ERROR 3

static int wifi_sta_join() {
	esp_err_t rc = ESP_OK;
	wifi_mode_t wifi_mode;
	// Is it already connected?
	int bits = xEventGroupGetBits(wifi_event_group);
	if (bits & CONNECTED_BIT) {
		return WIFI_STA_CONNECTED;
	}
	rc = esp_wifi_get_mode(&wifi_mode);
	if (rc == ESP_OK && !(wifi_mode & WIFI_MODE_STA)) {
		rc = esp_wifi_set_mode(wifi_mode | WIFI_MODE_STA);
	}
	{
		// Is there an ssid set?
		wifi_config_t wifi_config = { 0 };
		size_t len = sizeof(wifi_config.sta.ssid);
		rc = nvs_get_str(nvs_config_handle, "sta.ssid", (char *)wifi_config.sta.ssid, &len);
		if (rc != ESP_OK) {
			ESP_LOGI(TAG, "ssid read error");
			return WIFI_STA_ERROR;
		}
		len = sizeof(wifi_config.sta.password);
		rc = nvs_get_str(nvs_config_handle, "sta.pwd", (char *)wifi_config.sta.password, &len);
		if (rc != ESP_OK) {
			ESP_LOGI(TAG, "pwd read error");
			return WIFI_STA_ERROR;
		}
		rc = esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
		if (rc != ESP_OK) {
			ESP_LOGI(TAG, "set config error %d", rc);
			return WIFI_STA_ERROR;
		}
	}
	// begin new connect if wifi was in sta mode otherwise the
	// callback function will perform the connect call
	if (rc == ESP_OK && (wifi_mode & WIFI_MODE_STA)) {
		rc = esp_wifi_connect();
	}
	if (rc != ESP_OK) {
		ESP_LOGI(TAG, "error at end");
		return WIFI_STA_ERROR;
	}
	return WIFI_STA_CONNECTING;
}

static int wifi_softap_start() {
	//
	return 0;
}

struct netconn * tcp_client_handle;
//char rambuf[512];

static void tcp_server_callback(struct netconn * conn, enum netconn_evt evt, uint16_t length) {
	ESP_LOGI(TAG, "tcp_cb: %d %u", evt, length);
	if (evt == NETCONN_EVT_RCVPLUS) {
		struct netbuf * netbuf;
		void * ptr;
		uint16_t datalen;
		err_t err;
		if (conn == tcp_server_handle) {
			ESP_LOGI(TAG, "tcp_server_handle");
		}
		// Don't think can call in callback.
		//err = netconn_accept(conn, &tcp_client_handle);
		//ESP_LOGI(TAG, "netconn_accept err = %d", err);
		/*
		if (conn == tcp_server_handle && netconn_accept(conn, &tcp_client_handle) == ERR_OK) {
			ESP_LOGI(TAG, "got new connection");
		} else
		if (conn == tcp_client_handle && netconn_recv(conn, &netbuf) == ERR_OK) {
			ESP_LOGI(TAG, "recv_ok");
			do {
				netbuf_data(netbuf, (void *)&ptr, &datalen);
				ESP_LOGI(TAG, "%d", (int)datalen);
			} while (netbuf_next(netbuf) >= 0);
			netbuf_delete(netbuf);
		} else {
			ESP_LOGI(TAG, "got something %d %u", (int)evt, length);
		}
		*/
	}
}

static void system_monitor_callback(TimerHandle_t xTimer) {
	int rc = wifi_sta_join();
	{
		char buf[32];
		sprintf(buf, "wifi_sta_join() %d\r\n", rc);
		uart_write_bytes(UART_NUM_0, buf, strlen(buf));
	}
	if (rc == WIFI_STA_CONNECTED) {
		err_t err;
		if (tcp_server_handle == NULL) {
		// begin listening
		// esp_err_t tcpip_adapter_get_ip_info(tcpip_adapter_if_t tcpip_if, tcpip_adapter_ip_info_t *ip_info);
		//ip_addr_t ip_any = IP_ADDR_ANY;
		tcp_server_handle = netconn_new_with_callback(NETCONN_TCP, tcp_server_callback);
		ESP_LOGI(TAG, "%d", tcp_server_handle == NULL ? 0 : 1);
		netconn_set_flags(tcp_server_handle, NETCONN_FLAG_NON_BLOCKING);
		// Don't need to use htons here... for some reason.
		err = netconn_bind(tcp_server_handle, IP_ADDR_ANY, 5000);
		ESP_LOGI(TAG, "bind err %d", err);
		err = netconn_listen_with_backlog(tcp_server_handle, 2);
		ESP_LOGI(TAG, "listen err %d", err);
		tcp_client_handle = NULL;
		}
	}
	/*
	switch (rc) {
	case WIFI_RC_CONNECTING:
	case WIFI_RC_CONNECTED:
	case WIFI_RC_ERROR:
	default:
	}
	*/
}

static void command_process(int argc, char *argv[]) {
	esp_err_t err;
	if (strcmp(argv[0], "wifi") == 0) {
		//if (argc >= 3 && strcmp(argv[1], "config") == 0) {
			//if (strcmp(argv[2], "dump") == 0) {
			//	wifi_config_t config = {0};
			//	err = esp_wifi_get_config(ESP_IF_WIFI_STA, &config);
			//	if (err != ESP_OK) {
			//		uart_write_bytes(UART_NUM_0, "ERR\r\n", 5);
			//		return;
			//	}
			//	uart_write_bytes(UART_NUM_0, (char *)config.sta.ssid, strlen((char *)config.sta.ssid));
			//	uart_write_bytes(UART_NUM_0, "\r\n", 2);
			//}
		//} else
		//if (strcmp(argv[1], "join") == 0) {
			//int timeout_ms = 10000;
			//wifi_mode_t wifi_mode = WIFI_MODE_NULL;
			//if (esp_wifi_get_mode(&wifi_mode) == ESP_OK && wifi_mode != WIFI_MODE_STA) {
			//	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
			//} else {
			//}
			//if (argc == 4) {
				//strncpy((char *)wifi_config.sta.ssid, argv[2], sizeof(wifi_config.sta.ssid));
				//strncpy((char *)wifi_config.sta.password, argv[3], sizeof(wifi_config.sta.password));
			//	ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
			//}
			//if (wifi_mode == WIFI_MODE_STA) {
			//	ESP_ERROR_CHECK(esp_wifi_connect());
			//} else {
			//}
			//int bits = xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT,
			//		pdFALSE, pdFALSE, timeout_ms / portTICK_PERIOD_MS);
			//if (bits & CONNECTED_BIT) {
			//	uart_write_bytes(UART_NUM_0, "CON\r\n", 5);
			//} else {
			//	uart_write_bytes(UART_NUM_0, "TOC\r\n", 5);
			//}
		//} else
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
		/*
		if (argc == 3) {
		if (strcmp(argv[1], "ssid") == 0) {
		}
		if (strcmp(argv[1], "pwd") == 0) {
		}
		}
		*/
		if (argc == 4) {
			if (strcmp(argv[1], "stacred") == 0) {
				err = nvs_set_str(nvs_config_handle, "sta.ssid", argv[2]);
				if (err == ESP_OK) {
					err = nvs_set_str(nvs_config_handle, "sta.pwd", argv[3]);
				}
				if (err == ESP_OK) {
					uart_write_bytes(UART_NUM_0, "OK_\r\n", 5);
				} else {
					uart_write_bytes(UART_NUM_0, "ERR\r\n", 5);
				}
			} else
			if (strcmp(argv[1], "apcred") == 0) {
			}
		}
	} else
	if (strcmp(argv[0], "get") == 0) {
		if (argc == 2) {
			if (strcmp(argv[1], "stacred") == 0) {
				size_t len = 29;
				char buf[32];
				err = nvs_get_str(nvs_config_handle, "sta.ssid", buf, &len);
				if (err == ESP_OK) {
					strcat(buf, "\r\n");
					len = strlen(buf);
					uart_write_bytes(UART_NUM_0, buf, len);
					len = 29;
					err = nvs_get_str(nvs_config_handle, "sta.pwd", buf, &len);
				}
				if (err == ESP_OK) {
					strcat(buf, "\r\n");
					len = strlen(buf);
					uart_write_bytes(UART_NUM_0, buf, len);
				} else {
					uart_write_bytes(UART_NUM_0, "ERR\r\n", 5);
				}
			}
		}
	} else
	if (strcmp(argv[0], "unset") == 0) {
		//xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
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
	err = nvs_open("config", NVS_READWRITE, &nvs_config_handle);
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
	// Allowing the wifi library to save state to fash causes an LoadStoreAlignment exception
	// TODO: Investigate the error further.
	ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_NULL));
	ESP_ERROR_CHECK(esp_wifi_start());

	tcp_server_handle = NULL;
}

void app_main() {
	initialise_nvs();
	initialise_wifi();
	xTaskCreate(command_task, "command_task", 1024, NULL, 10, NULL);
	system_monitor_timer = xTimerCreate("system_monitor", 10000 / portTICK_RATE_MS, pdTRUE, (void *)0, &system_monitor_callback);
	xTimerStart(system_monitor_timer, 0);
}

