# aut0rient (Auto Orient-) Work In Progress.
Auto rotate your monitor using ADXL335+ADS1115 and linux.

# required library 
ads1115 library for linux <https://github.com/giobauermeister/ads1115-linux-rpi>
Don't be worry, It can be compiled on x86 and x86_64 without any modification to the library.

# Compile and Run
Before you gonna compile. You need to do some several things because this wont works right out of the box.

1. check your display that want to auto rotate by issue following command
```
xrandr
```
and see all of the name of port, E.G. VGA-1-1 HDMI-0 and so on.
2. go get the "i2ctools" and issue following command
```
i2cdetect -l
```
It will list all i2c port on your PC. so you need to select one that match with your display (which intergraded the sensor and jam into the same i2c line of EEPROM, my case is internal eeprom in my laptop monitor)

3. the information from the step 1 is the output port and the info from the setp 2 is i2c bus. YOu need these information to make the code works for you. By changing the i2c bus by locating the "openI2CBus" and change to /dev/i2c-x (mine is "/dev/i2c-1") and locate system("xrandr you need to replace the --output with your display

4.besure that the z axis of sensor (look from the top of sensor) is toward you (the position of you is infront of the display) and the +y axis of sensor upward the monitor. NOTE : go find the datasheet and look at the picture on page 12 <https://www.analog.com/media/en/technical-documentation/data-sheets/ADXL335.pdf>

5.after step 4 you need the pinout of your connector of your monitor. just google " VGA i2c pinout " or " HDMI i2c pinout " and so on.

6. then issue following commands
```
git clone https://github.com/TiNredmc/aut0reint.git
git clone https://github.com/giobauermeister/ads1115-linux-rpi.git
cd ads1115-linux-rpi
cp ads1115_rpi.* ../aut0rient
cd ../aut0rient 
gcc main.c ads1115_rpi.c -o aut0rient
chmod +x aut0rient //optional
./aut0rient //if thing works go put someware to make it auto-start.
```
