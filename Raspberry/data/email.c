
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main( int argc, const char* argv[] )
{       
        const char email[] = "alexis.massol@hotmail.fr";
        const char subject[] = "Raspberry Message";
        const char content[] = "Hi,How are you ?";
        char msg[100];
        sprintf(msg," echo \"%s\" | mail -s \"%s\" %s",content,subject,email); 
        printf("Email sent");
        system(msg);
}

