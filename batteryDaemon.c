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
        FILE *file;
        if ((file) = fopen("/home/aloothealoo/projects/batteryDaemon/override.txt", "r")) 
        {

            sleep(60);
            //override file exists, we must skip this iteration the loop
            continue;
        }
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
