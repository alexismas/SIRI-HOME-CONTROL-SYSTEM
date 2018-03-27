#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int fd;
char buf[100]; 

int main( int argc, const char* argv[] )
{
	

	// Prints argument 
	int gpio = atoi(argv[1]); // char to int to gpio
	printf( "Gpio : %d \n",gpio);

	int value = atoi(argv[2]); // char to int to Value (1 or 0)
	printf( "Value : %d \n",value);

	// Writing on a file

	// 0 to export the GPIO, set the direction to "OUTPUT" and switch off the LED
	// 1 to export the GPIO, set the direction to "OUTPUT" and switch on the LED
	// 3 to unexport the GPIO

	
	if(value <3)
	{
		// GPO :  echo gpio_number > /sys/class/gpio/export
		fd = open("/sys/class/gpio/export", O_WRONLY);

			sprintf(buf, "%d", gpio); 

			write(fd, buf, strlen(buf));

			close(fd);

		// direction : "echo "out"/"in" > /sys/class/gpio/gpioXX/direction
		sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio);

			fd = open(buf, O_WRONLY);

			// Set out direction
			write(fd, "out", 3); 
			

			close(fd);

		// Value : echo 0 > /sys/class/gpio/gpioXX/value
			sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);

			fd = open(buf, O_WRONLY);

		if(value ==0)
		{
			

		
			// Set GPIO low status 
			write(fd, "0", 1); 

			
		}

		if(value ==1)
		{
			

			

			// Set GPIO high status
			write(fd, "1", 1); 
			

			
		}

		close(fd);
		
	}
	else
	{
		if(value ==3)
		{
			// GPO :  echo gpio_number > /sys/class/gpio/export
		fd = open("/sys/class/gpio/unexport", O_WRONLY);

		sprintf(buf, "%d", gpio);

		write(fd, buf, strlen(buf));

		close(fd);
		}
		

	}
	

}