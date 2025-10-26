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

Additional Notes
----------------

`partitions.csv` is a copy of `partitions_singleapp.csv` from the SDK.

Communication using `picocom`
-----------------------------

`picocom` is a useful mini utility that allows serial communication,
it is like minicom but more modern. However, it does not seem to
compile properly on Alpine / musl when one wishes to use custom baud
rates. Custom rates are important for being able to view the early
output sent from an ESP8266 (ESP-01), the device used in my project.

The `setserial` application does work with musl and so to interact
with the device on `/dev/ttyUSB0` at 74880 bps:

    ./setserial /dev/ttyUSB0 74880
    doas ./picocom --noinit --noreset --omap crcrlf /dev/ttyUSB0

`picocom` will probably report that the baud rate is 9600, this can
be safely ignored, the `--noinit` switch will prevent changes to
the rate when the application starts. **IMPORTANT** this also
assumes that the other settings are normal, such as: 8-N-1. That is
to say: 8 data bits, no parity bit and 1 stop bit.

For more detail and to set other options, see the `stty` command.

