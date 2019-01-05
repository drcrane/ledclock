LEDCLOCK
========

This repository contains the source files for my seven segment LED 
Clock which I made in 2017 for my nephew.

The Clock is powered by an MSP430G2553 and a 32.768 kHz watch 
crystal. The clock queried time over the serial port which should
be connected to an ESP8266 (ESP-01) running a modified terminal
programme that supports querying internet time servers.

Running ntpd on Alpine Linux
----------------------------

Turn on a time server in Alpine Linux / busybox (if compiled in)

    busybox ntpd -l -d -d -d -n

This is good for testing as you can see each request for the time.

Open-RTOS-SDK
-------------

The terminal application was modified (not very well) to support
this application. The REPOs:

repo:   https://github.com/SuperHouse/esp-open-rtos
commit: 46499c0f26c490f5a539f82eb950fa7879f65dc7

repo:   https://github.com/pfalcon/esp-open-sdk
commit: 5518fb6116c35a02ccb9a87260bb194a57cb429e

The build scripts and programmer are required from the above
repos.

The modified terminal application is available in:
`esp8266terminal` I recommend that you copy this into the
`esp-open-rtos/examples` directory to compile and deploy to
an ESP8266.

 - Benjamin Green 2018-02-03

