//////////////////////////////////////////////////
// Simple NTP client for ESP8266.
// Copyright 2015 Richard A Burton
// richardaburton@gmail.com
// See license.txt for license terms.
//////////////////////////////////////////////////

#ifndef __NTP_H__
#define __NTP_H__

#include <stdint.h>

#define NTP_TIMEOUT_MS 5000

typedef struct {
	uint8_t options;
	uint8_t stratum;
	uint8_t poll;
	uint8_t precision;
	uint32_t root_delay;
	uint32_t root_disp;
	uint32_t ref_id;
	uint8_t ref_time[8];
	uint8_t orig_time[8];
	uint8_t recv_time[8];
	uint8_t trans_time[8];
} ntp_t;

void ntp_get_time(char * hostname);

#endif

