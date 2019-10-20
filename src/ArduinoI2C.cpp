#include <math.h>

#include <ArduinoI2C.h>

ARDUINO::ARDUINO(int address)
{
    kI2CBus = 0;
    kI2CAddress = address;
    error = 0;
}

ARDUINO::~ARDUINO()
{
    closeARDUINO();
}

bool ARDUINO::openARDUINO()
{
    char fileNameBuffer[32];
    sprintf(fileNameBuffer, "/dev/i2c-%d", kI2CBus);
    kI2CFileDescriptor = open(fileNameBuffer, O_RDWR);

    if(kI2CFileDescriptor < 0)
    {
        error = errno;
        return false;
    }

    if(ioctl(kI2CFileDescriptor, I2C_SLAVE, kI2CAddress) < 0)
    {
        error = errno;
        return false;
    }
    return true;
}

void ARDUINO::closeARDUINO()
{
    if(kI2CFileDescriptor > 0)
    {
        close(kI2CFileDescriptor);
        kI2CFileDescriptor = -1;
    }
}

int ARDUINO::readByte(int readRegister)
{
    int toReturn = i2c_smbus_read_byte_data(kI2CFileDescriptor, readRegister);
    if(toReturn < 0)
    {
        printf("ARDUINO Read Byte Error: %d", errno);
        error = errno;
        toReturn = -1;
    }
    return toReturn;
}

int ARDUINO::writeByte(int writeRegister, int writeValue)
{
    int toReturn = i2c_smbus_write_byte_data(kI2CFileDescriptor, writeRegister, writeValue);
    if(toReturn < 0)
    {
        printf("ARDUINO Write Byte Error: %d", errno);
        error = errno;
        toReturn = -1;
    }
    return toReturn;
}

void ARDUINO::readArduino()
{
    arduino_raw_  = readByte(ARDUINO_ADDRESS);

    //for debugging
    printf("Accel X: %d\n", arduino_raw_);
}
