#ifndef ARDUINO_H
#define ARDUINO_H

#include <math.h>
#include <cstddef>
extern "C" {
    #include <linux/i2c-dev.h>
    #include <i2c/smbus.h>
}
#include <sys/ioctl.h>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

class ARDUINO
{
public:
    ARDUINO(int address=0x08);
    ~ARDUINO();

    bool openARDUINO();
    void closeARDUINO();

    void readArduino();

    // Read the given register
    int readByte(int readRegister);
    // Write the the given value to the given register
    int writeByte(int writeRegister, int writeValue);

    unsigned char kI2CBus;         // I2C bus of the ARDUINO
    int kI2CFileDescriptor;        // File Descriptor to the ARDUINO
    int kI2CAddress;               // Address of ARDUINO; defaults to 0x68
    int error;

private:
    int8_t arduino_raw_;

};

#define ARDUINO_ADDRESS             0x08


#endif //ARDUINO_H
