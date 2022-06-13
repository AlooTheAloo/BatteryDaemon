#include <stdio.h>
#include <unistd.h>

int system(char *);

int main(){


    //Getting dir
    char cwd[4352]; //4096 (max file path) + 255 (max file name len) + 1 (Terminating character)
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("There was an error installing Batd :( Try running as sudo or give read access through chmod.");
        return -1;
    }
    //Systemctl stuff
    system("touch /lib/systemd/system/batd_startup.service");
    system("echo [Unit] > /lib/systemd/system/batd_startup.service");
    system("echo Description=Startup Daemon for batteryd >> /lib/systemd/system/batd_startup.service");
    system("echo [Service] >> /lib/systemd/system/batd_startup.service");
    char execStart[4700];
    sprintf(execStart, "echo ExecStart=%s/battery-daemon >> /lib/systemd/system/batd_startup.service", cwd);
    system(execStart);
    system("echo [Install] >> /lib/systemd/system/batd_startup.service");
    system("echo WantedBy=multi-user.target >> /lib/systemd/system/batd_startup.service");
    system("systemctl enable batd_startup.service --now");
    
    char username[1000];
    getlogin_r(username, 1000);
    //Aliases
    char path [4500];
    sprintf(path, "/home/%s/.bashrc", username);
    FILE* file;
    file = fopen(path, "aw");
    fprintf(file, "alias battery-daemon-override='touch %s/override.txt; echo Daemon overriden'\n", cwd);
    fprintf(file, "alias battery-daemon-stop-override='rm %s/override.txt; echo Daemon overriden'\n", cwd);
}