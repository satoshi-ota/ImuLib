#include <math.h>

#include <MPU6050.h>

MPU6050::MPU6050(int address)
{
    kI2CBus = 0;
    kI2CAddress = address;
    error = 0;
}

MPU6050::~MPU6050()
{
    closeMPU6050();
}

bool MPU6050::openMPU6050()
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

void MPU6050::closeMPU6050()
{
    if(kI2CFileDescriptor > 0)
    {
        close(kI2CFileDescriptor);
        kI2CFileDescriptor = -1;
    }
}

int MPU6050::readByte(int readRegister)
{
    int toReturn = i2c_smbus_read_byte_data(kI2CFileDescriptor, readRegister);
    if(toReturn < 0)
    {
        printf("MPU6050 Read Byte Error: %d", errno);
        error = errno;
        toReturn = -1;
    }
    return toReturn;
}

int MPU6050::writeByte(int writeRegister, int writeValue)
{
    int toReturn = i2c_smbus_write_byte_data(kI2CFileDescriptor, writeRegister, writeValue);
    if(toReturn < 0)
    {
        printf("MPU6050 Write Byte Error: %d", errno);
        error = errno;
        toReturn = -1;
    }
    return toReturn;
}
