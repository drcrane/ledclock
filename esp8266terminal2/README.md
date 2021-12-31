Terminal Interface for ESP8266 (ESP-01S)
========================================

This is an enhanced version of esp8266terminal which compiles with the
`ESP8266_RTOS_SDK` from espressif.

Setup
-----

To compile the source, download the compiler toolchain:

    xtensa-lx106-elf-gcc8_4_0-esp-2020r3-linux-amd64.tar.gz

And the version of the `ESP8266_RTOS_SDK` you would like to use (for
developing this application version 3.4 was used):

    ESP8266_RTOS_SDK-v3.4.zip

Download URLs:

* [Github Repository RTOS SDK](https://github.com/espressif/ESP8266_RTOS_SDK)
* [xtensa GCC toolchain](https://dl.espressif.com/dl/xtensa-lx106-elf-gcc8_4_0-esp-2020r3-linux-amd64.tar.gz)
* [ESP8266\_RTOS\_SDK](https://github.com/espressif/ESP8266_RTOS_SDK/releases/download/v3.4/ESP8266_RTOS_SDK-v3.4.zip)

Make a workspace directory (for this document ~/esp8266 is assumed) and
extract the contents of the SDK and compiler toolchain:

    mkdir ~/esp8266
    cd ~/esp8266
    # download the files or alter the path as required
    tar -xf xtensa-lx106-elf-gcc8_4_0-esp-2020r3-linux-amd64.tar.gz
    unzip ESP8266_RTOS_SDK-v3.4.zip

Set the required environment variables (this assumes `ash` or `bash`):

    export PATH=~/esp8266/xtensa-lx106-elf/bin:$PATH
    export IDF_PATH=~/esp8266/ESP8266_RTOS_SDK

Now attempt to compile the code:

    cd ~/esp8266/ledclock/esp8266terminal2
    make

This will likely fail since python modules are required

