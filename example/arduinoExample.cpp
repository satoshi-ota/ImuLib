#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <ArduinoI2C.h>

int main()
{
    ARDUINO *arduino = new ARDUINO();
    int err = arduino->openARDUINO();

    if(err < 0)
    {
        printf("Error: %d", arduino->error);
    }
    else
    {
        printf("ARDUINO Device Address: 0x%02X\n", arduino->kI2CAddress);
        //for debugging
        //int devAddress = ARDUINO->readByte(ARDUINO_WHO_AM_I);
        //printf("I am 0x%02X\n", devAddress);

        while(arduino->error >= 0)
        {
            printf("Now publishing...\n");
            arduino->readArduino();
            sleep(1);
        }
    }
    arduino->closeARDUINO();
}
