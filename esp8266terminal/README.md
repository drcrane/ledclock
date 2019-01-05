# Terminal Application

This terminal application contains support for setting the
WiFi SSID and PSK along with the ability to query an arbitrary
internet time server for the current time over serial at 9600.
It was modified for use with the LEDCLOCK project.

## To build this thing....

export PATH=/path_to/esp-open-sdk/xtensa-lx106-elf/bin:$PATH

make ESPPORT=/dev/ttyUSB0 flash

