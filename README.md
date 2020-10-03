This is my documentation for the assignment I did as a part of acceptance exam to an internship.

## design specification
### Hardware
- Use PICSimLab v0.8
-Board: PIC Genios with  pic16f877a <br/>
-Use peripherals from the
board
- Heating Element ➔ Heater
- Cooling Element ➔ Fan
- External E2PROM ➔ I2C E2PROM
- Map other elements as
you wish
Let's first devote the specification required for this project 
### Specifications – Temperature Setting
- The “Up” or “Down” buttons are used to change the required water
- temperature (set temperature)
- The first “Up” or “Down” button press, enters the temperature setting mode
- After entering temperature setting mode, a single “Up” button press increase the set temperature by 5 degrees
- After entering temperature setting mode, a single “Down” button press decrease the set temperature by 5 degrees
- The minimum possible set temperature is 35 degrees
- The maximum possible set temperature is 75 degrees
- The “External E2PROM” should save the set temperature once set
- If the electric water heater is turned OFF then ON, the stored set temperature should be retrieved from the “External E2PROM”
- The initial set temperature is 60 degrees

### Specifications – ON/OFF Behavior
- If power is connected to the heater, the electric water heater is in OFF state
- If the “ON/OFF” button is released and the electric water heater is in OFF state, the electric water heater goes to ON state
- If the “ON/OFF” button is released and the electric water heater is in ON state, the electric water heater goes to OFF state
- In the OFF state, all display should be turned OFF
### Specifications – Temperature Sensing
- The temperature sensor measures the water temperature
- The water temperature should increase, if the “Heating Element” is ON
- The water temperature should decrease, if the “Cooling Element” is ON
- Temperature should be sensed once every 100 ms
- The decision to turn ON or OFF either the “Heating Element” or the “Cooling Element” based on the average of the last 10 temperature readings
### Specifications – Heating/Cooling Elements
- The “Heating Element” should be turned ON, if the current water temperature is less than the set temperature by 5 degrees
- The “Cooling Element” should be turned OFF, if the current water temperature is less than the set temperature by 5 degrees
- The “Heating Element” should be turned OFF, if the current water temperature is greater than the set temperature by 5 degrees
- The “Cooling Element” should be turned ON, if the current water temperature is greater than the set temperature by 5 degrees
### Specifications – Seven Segments
- 2 seven segment by default show the current water temperature or the set temperature
- By default, the 2 seven segment display are show the current water temperature
- If the electric water heater is in the temperature setting mode, the 2 seven segment displays should blink every 1 second and show the set temperature
- In the temperature setting mode, every change in the set temperature should be reflected on the 2 seven segment displays
- The 2 seven segment display should exit the temperature setting mode, if the “UP” and “Down” buttons are not pressed for 5 seconds
### Specifications – Heating Element Led
- If the “Heating Element” is ON, the “Heating Element Led” should blink every 1 second
If the “Cooling Element” is ON, the “Heating Element Led” should be ON
## hello PIC  mcu

The first challenge I faced in this project was that I must use the pic pic16f877a with its limited resources and deal with new development environment. So I began searching for the suitable compiler and downloaded the datasheet and started writing some hello world code to get used to this new microcontroller and know the register responsible of handling the ports and other peripheral 
Then I moved to deal with timer and interrupts which will be necessary when I design the system I discovered that unlike AVR, PIC mcu doesn't have interrupt vector table and you have to check which peripheral caused the interrupt manually.




## Deciding the design pattern 
As noticed from the specification, the system contain tasks that happen periodically and another tasks that interact with the user
so I  did some research to find out the best method to build the project with. I came upon different RTOSs but find that it is difficult to port my mcu to work with them due its limited RAM and Flash size, so I tried another route and grabbed the book written by Michael j Pont pattern for time triggered system and looked at the source code of the system he design at the first I thought that his book about designing RTOS but later I found out that his system lack many capabilities that normal RTOS provide like protecting shared data and the communication with system tasks. 
I discarded these two idea I decided to design the system with crude approach that would later arise many many bugs.
### Board specification
As the source code must be applied to [PICSimLab](https://sourceforge.net/projects/picsim/) PIC Geniue board, I downloaded the board diagram and some example from [their respo](https://lcgamboa.github.io/) .I started to dig into  the board and deal with different devices on it to know which port controlling which device. I found that there is DIP switch connecting PORT pins to the devices and you should turn them on to control the target device.
 Here is a summary of the most important modules on the board and their correspond pins.

7seg ---> PORTD  toggled by RA3 RA4. <br/>
heater ---> RC5  toggled by RSIS DIP switch <br/> 
cooler ---> RC2  toggled by VENT DIP switch <br/>
temperature sensor --->  RA2 which is ADC channel 2<br/>
eeprom ---> I2C pins

Note that the two seven segments digit are connected to the same port which mean that they will show the same number instead of different ones. <br/>
the solution to this issue is straightforward 
```
turn on one 7seg while turning off the other 
send the wanted number to PORTD 
repeat the process by the next system tick but with exchanging the 7seg
```
## Layout the system 
I divided the system into multiple modules each deal with specific part of the system. the main idea was to use timer to interrupt every 10 ms which will behave as system tick where the tasks would be implemented in order. there is super loop to poll the statue of on/off toggle switch. <br/>
As I noticed later this approach is fragile as it depend heavily on the assumbtion that all the task would be done before the next system tick to come, if not the whole system latency would be affected. 
## The importance of backup ##
The biggest lesson I learned from this project that I should back up periodically. I was writing code for half a day when I accidentaly closed the terminal - I used vim as my code editor - and when I tried to open the code again vim asked if I wanted to restore the swap files. not knowing what to do I ended discarding the code I was written all the day. fortunately I was writing my notes in sheet of paper, so I didn't had to begin from scratch
## Bug hunting
The first bug to appear was that the led that indicate heater is on doesn't blink expected. I had to examine the code that configure the pin and the tasks that monitor it.

The next bug occurred when I misunderstood the job specification of the heater and the cooler so I studied it and write their code again.

The bug that got me crazy and took me a lot of time to discover and solve this bug occur unexpectedly when I try to change the wanted temperature so instead of waiting 5 seconds then return to the normal mode, the system turn off completely as if I pressed the on/off toggle. 
After hours of careful investigating I solved the problem by removing the code- that export the wanted temperature to eeprom after setting it- from the interrupt routine and instead call it from the main function. I don't really know what caused this problem maybe that reading or writing from eeprom take much time that lengthen interrupt latency long.

## Compiling and findal notes
You can compile this code with xc8 compiler from microchip. Please note that this code was tested only on simulation platform not on real target.
