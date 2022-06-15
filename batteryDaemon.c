#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main(void) {
    
   

    /* The Big Loop */
    while (1) {
        printf("Hello world!!");
        
        FILE *file;
        char cwd[4352]; //4096 (max file path) + 255 (max file name len) + 1 (Terminating character)
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            break;
        }
        char filepath[4500];
        sprintf(filepath, "%s/override.txt", cwd);
        if ((file) = fopen(filepath, "r")) 
        {
            printf("overriden!");
            //override file exists, we must skip this iteration the loop
            sleep(1);
            continue;
        }
        printf("was looking for %s", filepath);
        printf("not overriden!");
        //Get the time
        time_t rawtime;
        struct tm * timeinfo; 
        time ( &rawtime ); 
        timeinfo = localtime ( &rawtime );
        //String formatting
        char timeString[100] = "";
        sprintf(timeString, "%s",asctime (timeinfo));

        char *ptr = strtok(timeString, " ");

        //This is the way to get a specific place in the array because C is stupid
        int i = 0;
        while(i <= 2)
        {
            ptr = strtok(NULL, " ");
            i++;
        }
        char onlyTime[100];
        sprintf(onlyTime, "%s", ptr);
        char *token = strtok(onlyTime, ":");
        int hour = atoi(token); //String to int
        //Tests + Runs
        if(hour < 7 || hour > 18){
            system("asusctl -c 50");
        }
        else{
            system("asusctl -c 80");
        }
        sleep(60); /* wait 60 seconds */
    }
   exit(EXIT_SUCCESS);
}
