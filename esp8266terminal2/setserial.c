/*
 * Allows to set arbitrary speed for the serial device on Linux.
 * stty allows to set only predefined values: 9600, 19200, 38400, 57600, 115200, 230400, 460800.
 * the ESP8266 default requires a baud rate of: 74880
 * native speed of ESP8266 is: 74880
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <asm/termios.h>

// #include <sys/ioctl.h>
// extern int ioctl (int __fd, unsigned long int __request, ...) __THROW;
extern int ioctl(int __fd, unsigned long int __request, ...);

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("%s device speed\n\nSet speed for a serial device.\nFor instance:\n    %s /dev/ttyUSB0 74880\n", argv[0], argv[0]); 
        return -1;
    }

    int fd = open(argv[1], O_RDONLY);

    int speed = atoi(argv[2]);

    struct termios2 tio;
    ioctl(fd, TCGETS2, &tio);
    tio.c_cflag &= ~CBAUD;
    tio.c_cflag |= BOTHER;
    tio.c_ispeed = speed;
    tio.c_ospeed = speed;
    int r = ioctl(fd, TCSETS2, &tio);
    close(fd);

    if (r == 0) {
        printf("Changed successfully.\n");
    } else {
        perror("ioctl");
    }
}

