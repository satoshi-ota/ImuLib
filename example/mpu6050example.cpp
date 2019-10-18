#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <MPU6050.h>

int main()
{
    MPU6050 *mpu6050 = new MPU6050();
    int err = mpu6050->openMPU6050();

    if(err < 0)
    {
        printf("Error: %d", mpu6050->error);
    }
    else
    {
        printf("MPU6050 Device Address: 0x%02X\n", mpu6050->kI2CAddress);
        //for debugging
        int devAddress = mpu6050->readByte(MPU6050_WHO_AM_I);
        printf("I am 0x%02X\n", devAddress);

        printf("Now publishing...\n");
        mpu6050->readAccel();
        sleep(1);

        while(mpu6050->error >= 0)
        {
            printf("Now publishing...\n");
            mpu6050->readAccel();
            sleep(1);
        }
    }
    mpu6050->closeMPU6050();
}
