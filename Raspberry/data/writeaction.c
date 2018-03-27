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
	/*

	// Prints argument 
	int gpio = atoi(argv[1]); // char to int to gpio
	printf( "Gpio : %d \n",gpio);

	int value = atoi(argv[2]); // char to int to Value (1 or 0)
	printf( "Value : %d \n",value); */

	// Writing on a file
	int temp = atoi(argv[1]);;
	fd = open("action.txt", O_WRONLY); // ouvrire le fichier avec droit ecriture

	sprintf(buf, "%d", temp);  // ecrire dans le fichier buf

	write(fd, buf, strlen(buf)); // ecrire dans le fichier ouvert

	close(fd); // fermer le fichier

	
	

}