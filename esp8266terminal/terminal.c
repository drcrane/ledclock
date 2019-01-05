/* Serial terminal example
 * UART RX is interrupt driven
 * Implements a simple GPIO terminal for setting and clearing GPIOs
 *
 * This sample code is in the public domain.
 */

#include "espressif/esp_common.h"
#include "espressif/user_interface.h"
#include "ssid_config.h"
#include "stdout_redirect.h"

#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <esp8266.h>
#include <esp/uart.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "ntp.h"
#include "argparser.h"

#define MAX_ARGC (10)

char wifi_ssid[50];
char wifi_passwd[50];

static void cmd_writelflash(uint32_t argc, char * argv[]) {

}

static void cmd_wifi(uint32_t argc, char *argv[]) {
	if (argc == 1) {
		if (strcmp(argv[0], "off") == 0) {
			printf("Stopping...\n");
			sdk_wifi_set_opmode(NULL_MODE);
		}
		if (strcmp(argv[0], "on") == 0) {
			printf("Connecting...\n");
			LOCK_TCPIP_CORE();
			struct sdk_station_config config;
			memset(&config, 0, sizeof(struct sdk_station_config));
			strcpy((char *)config.ssid, (char *)wifi_ssid);
			strcpy((char *)config.password, (char *)wifi_passwd);
			//config.threshold.rssi = -127;
			sdk_wifi_set_opmode(STATION_MODE);
			sdk_wifi_station_set_config(&config);
			sdk_wifi_station_connect();
			sdk_wifi_station_dhcpc_start();
			UNLOCK_TCPIP_CORE();
		}
		if (strcmp(argv[0], "write") == 0) {
			// Save to flash
			int res = 0;
			res += spiflash_erase_sector(0x7f000);
			res += spiflash_write(0x7f000, wifi_ssid, 50);
			res += spiflash_write(0x7f040, wifi_passwd, 50);
			printf("write (%s, %s) %d\r\n", wifi_ssid, wifi_passwd, res);
		}
		if (strcmp(argv[0], "read") == 0) {
			int res = 0;
			res += spiflash_read(0x7f000, wifi_ssid, 50);
			res += spiflash_read(0x7f040, wifi_passwd, 50);
			printf("read: (%s, %s) %d\r\n", wifi_ssid, wifi_passwd, res);
		}
		if (strcmp(argv[0], "show") == 0) {
			printf("wifi %s %s\r\n", wifi_ssid, wifi_passwd);
		}
	}
	if (argc == 3) {
		if (strcmp(argv[0], "set") == 0) {
			strcpy(wifi_ssid, argv[1]);
			strcpy(wifi_passwd, argv[2]);
			printf("set %s %s\n", wifi_ssid, wifi_passwd);
		}
	}
}

static void cmd_on(uint32_t argc, char *argv[])
{
    if (argc >= 2) {
        for(int i=1; i<argc; i++) {
            uint8_t gpio_num = atoi(argv[i]);
            gpio_enable(gpio_num, GPIO_OUTPUT);
            gpio_write(gpio_num, true);
            printf("On %d\n", gpio_num);
        }
    } else {
        printf("Error: missing gpio number.\n");
    }
}

static void cmd_off(uint32_t argc, char *argv[])
{
    if (argc >= 2) {
        for(int i=1; i<argc; i++) {
            uint8_t gpio_num = atoi(argv[i]);
            gpio_enable(gpio_num, GPIO_OUTPUT);
            gpio_write(gpio_num, false);
            printf("Off %d\n", gpio_num);
        }
    } else {
        printf("Error: missing gpio number.\n");
    }
}

static void cmd_help(uint32_t argc, char *argv[])
{
    printf("on <gpio number> [ <gpio number>]+     Set gpio to 1\n");
    printf("off <gpio number> [ <gpio number>]+    Set gpio to 0\n");
    printf("sleep                                  Take a nap\n");
    printf("\nExample:\n");
    printf("  on 0<enter> switches on gpio 0\n");
    printf("  on 0 2 4<enter> switches on gpios 0, 2 and 4\n");
    printf("Flash ID: %08x\n", sdk_spi_flash_get_id());
}

static void cmd_sleep(uint32_t argc, char *argv[])
{
    printf("Type away while I take a 2 second nap (ie. let you test the UART HW FIFO\n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
}

static void cmd_time(uint32_t argc, char *argv[]) {
	if (argc == 1) {
		if (strcmp(argv[0], "sync") == 0) {
			printf("Querying NTP\n");
			ntp_get_time("uk.pool.ntp.org");
		} else if (strcmp(argv[0], "show") == 0) {
			time_t curr_time = 0;
			time_t ct2;
			ct2 = time(&curr_time);
			printf("Current Unix Time: %lu %lu\r\n", (long unsigned int)curr_time, (long unsigned int)ct2);
		}
	}
	if (argc == 2) {
		if (strcmp(argv[0], "set") == 0) {
			time_t curr_time;
			curr_time = atoi(argv[1]);
		} else
		if (strcmp(argv[0], "sync") == 0) {
			ntp_get_time(argv[1]);
		} if (strcmp(argv[0], "syncip") == 0) {
			//
		}
	}
}

static void handle_command(char *cmd)
{
    char *argv[MAX_ARGC];
    int argc;
    //char *temp, *rover;
    memset((void*) argv, 0, sizeof(argv));
    //argv[0] = cmd;
    //rover = cmd;
    // Split string "<command> <argument 1> <argument 2>  ...  <argument N>"
    // into argv, argc style
    //while(argc < MAX_ARGC && (temp = strstr(rover, " "))) {
    //    rover = &(temp[1]);
    //    argv[argc++] = rover;
    //    *temp = 0;
    //}
    //
    argc = argparser_parse(argv, cmd);

    if (strlen(argv[0]) > 0) {
        if (strcmp(argv[0], "help") == 0) cmd_help(argc, argv);
        else if (strcmp(argv[0], "on") == 0) cmd_on(argc, argv);
        else if (strcmp(argv[0], "off") == 0) cmd_off(argc, argv);
	else if (strcmp(argv[0], "wifi") == 0) cmd_wifi(argc - 1, argv + 1);
        else if (strcmp(argv[0], "sleep") == 0) cmd_sleep(argc, argv);
	else if (strcmp(argv[0], "time") == 0) cmd_time(argc - 1, argv + 1);
        else printf("Unknown command %s, try 'help'\n", argv[0]);
    }
}

static void gpiomon()
{
    char ch;
    char cmd[81];
    int i = 0;
    printf("\n\n\nWelcome to gpiomon. Type 'help<enter>' for, well, help\n");
    printf("%% ");
    fflush(stdout); // stdout is line buffered
    while(1) {
        if (read(0, (void*)&ch, 1)) { // 0 is stdin
            printf("%c", ch);
            fflush(stdout);
            if (ch == '\n' || ch == '\r') {
                cmd[i] = 0;
                i = 0;
                printf("\n");
                handle_command((char*) cmd);
                printf("%% ");
                fflush(stdout);
            } else {
                if (i < sizeof(cmd)) cmd[i++] = ch;
            }
        } else {
            printf("You will never see this print as read(...) is blocking\n");
        }
    }
}

//typedef ssize_t _WriteFunction(struct _reent *r, int fd, const void *ptr, size_t len);

ssize_t _write_stdout_r(struct _reent *r, int fd, const void *ptr, size_t len );

ssize_t _write_stdout_r_custom(struct _reent *r, int fd, const void *ptr, size_t len ) {
	return len;
}

void set_write_stdout(_WriteFunction *f);

void user_init(void)
{
    uart_set_baud(0, 9600);
    // uart_set_baud(0, 115200);

    //set_write_stdout(_write_stdout_r_custom);

    printf("SDK version:%s\n", sdk_system_get_sdk_version());
    //struct sdk_station_config config = {
    //   .ssid = WIFI_SSID,
    //   .password = WIFI_PASS
    //};

    //sdk_wifi_set_opmode(STATION_MODE);
    //sdk_wifi_station_set_config(&config);

    xTaskCreate(&gpiomon, "gpiomon", 384, NULL, 2, NULL);
    //gpiomon();
}

