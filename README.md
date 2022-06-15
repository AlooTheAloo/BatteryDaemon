# BatteryDaemon
Dynamically changes max charge for asus laptops on linux

### Make sure you have AsusCtl installed, or this won't work!

## What does this do?
This changes your battery dynamically to preserve battery health.
By default, from 7 AM to 6 PM your battery is limited to 80 (standard battery max for good battery health)
But during the night, you probably don't need your laptop to be fully charged (having it at 80 all the time is not optimal)
so it dials down your laptop's battery maximum to 50.

If you want to stop this daemon temporarily, the commands
```
battery-daemon-override
```
and
```
battery-daemon-stop-override
```
exist to stop/start the daemon temporarily.


## Installation
First, you need to clone the repo
```
git clone https://github.com/AlooTheAloo/BatteryDaemon
```
Then, go into the directory
```
cd BatteryDaemon
```
Finally, launch the install script (if you don't put sudo, everything will break!)
```
sudo ./installScript
```
#### Note : You will need to restart your system for the aliases to work!

### TLDR
```
git clone https://github.com/AlooTheAloo/BatteryDaemon
cd BatteryDaemon
sudo ./installScript
```

## I don't like the default values!
Worry not! If you want to change the values, simply go into the c file with nano or any other text editor
```
nano batteryDaemon.c
```
Then, modify the ending of the file to suit your needs. \
For example, if you want to change it to 30 percent from 11AM to 1PM and 100% for the rest of the time, you would write
```
if(hour < 11 || hour > 13){
  system("asusctl -c 30");
}
else{
  system("asusctl -c 100");
}
```
Finally, recompile the script.
```
gcc -Wall batteryDaemon.c -o battery-daemon
```

I might make way to modify it automatically but idk
