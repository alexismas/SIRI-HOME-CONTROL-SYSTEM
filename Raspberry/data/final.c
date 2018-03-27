#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

int fd;
char buf[100]; 

int main(int argc, const char* argv[] )
{
   int  val;
   char back_val;
    const int devId = 0x12; // communication port
    int com = wiringPiI2CSetup(devId);// initialisalyse the communication

    if (com < 0) {
            printf("Error setup I2C device %d\n", devId);
            return 1;
    }

    printf( "Algorythme I2C Run\n");

   
           // read a file 

    char value;

    sprintf(buf,"action.txt");

    fd = open(buf, O_RDONLY);

    read(fd, &value, 3);

    printf( "Value : %c \n",value); // %c pout iny %d pour entier

    close(fd);  
            
    // send the file
   

    val = atoi(&value);       // convert to int

    wiringPiI2CWrite(com,val);// sending Value

    printf("I send : %d\n",val);


    // receive Arduino data

    back_val = wiringPiI2CRead(com); // Arduino answer

    printf("Arduino answer  = %d\n",back_val);

    int temp;
    if((back_val>0)&&(back_val<100))
    {
        // Writing on a file

        temp = back_val;
        fd = open("tmp.txt", O_WRONLY); // ouvrire le fichier avec droit ecriture

        sprintf(buf, "%d", temp);  // ecrire dans le fichier buf

        printf("tmp = %d\n",temp);

        write(fd, buf, strlen(buf)); // ecrire dans le fichier ouvert

        close(fd); // fermer le fichier
    }
    else
    {
     
    }

    if(back_val == 200) // detection de mouvement
    {

        const char email[] = "alexis.massol@hotmail.fr";
        const char subject[] = "Raspberry Message";
        const char content[] = "Someone break into your house ?";
        char msg[100];
        sprintf(msg," echo \"%s\" | mail -s \"%s\" %s",content,subject,email); 
        printf("Email sent");
        system(msg);
    }
  



}
