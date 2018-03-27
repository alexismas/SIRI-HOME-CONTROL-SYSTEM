#include <stdio.h>
#include <wiringPiI2C.h>

int main(void)
{
    int val,back_val;
    const int devId = 0x12; // communication port
    int com = wiringPiI2CSetup(devId);// initialisalyse the communication

    if (com < 0) {
            printf("Error setup I2C device %d\n", devId);
            return 1;
    }

        
	printf("please enter a number(0-255):\n");
	scanf("%d",&val);

	wiringPiI2CWrite(com,val);// sending Value

	printf("I send : %d\n",val);

	back_val=wiringPiI2CRead(com); // Arduino answer

	printf("Arduino answer  = %d\n",back_val);
	


     return 0;
}
