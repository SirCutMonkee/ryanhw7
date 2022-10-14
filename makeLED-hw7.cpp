/** Simple On-board LED flashing program - written in C++ by Derek Molloy edited by Joshua Ryan
*    simple functional struture for the Exploring BeagleBone book
*
*    This program uses USR LED 3 and can be executed in 5 ways:
*         makeLED-hw7 on
*         makeLED-hw7 off
*         makeLED-hw7 flash  (flash at 100ms intervals - on 50ms/off 50ms)
*         makeLED-hw7 status (get the trigger status)
*	  makeLED-hw7 blink x (blink the LED x number of times with a 1s pause between blinks)
*
* * Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.           
* Edited by Joshua Ryan for WNEU CPE-525 HW7 */

#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
using namespace std;

#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"

void writeLED(string filename, string value){
   fstream fs;
   string path(LED3_PATH);
   fs.open((path + filename).c_str(), fstream::out);
   fs << value;
   fs.close();
}

void removeTrigger(){
  writeLED("/trigger", "none");
}

int main(int argc, char* argv[]){
   if(argc<=1){
	cout << "Usage is makeLED-hw7 and one of: " << endl;
        cout << "   on, off, flash, status, or blink and an integer value" << endl;
	cout << " e.g. makeLED-hw7 flash" << endl;
        return 2;
   }
   string cmd(argv[1]);
   cout << "Starting the makeLED-hw7 program" << endl;
   cout << "The current LED Path is: " << LED3_PATH << endl;

   // select whether command is on, off, flash or status
   if(cmd=="on"){
        cout << "Turning the LED on" << endl;
	removeTrigger();
        writeLED("/brightness", "1");
   }
   else if (cmd=="off"){
        cout << "Turning the LED off" << endl;
	removeTrigger();
        writeLED("/brightness", "0");
   }
   else if (cmd=="flash"){
        cout << "Flashing the LED" << endl;
        writeLED("/trigger", "timer");
        writeLED("/delay_on", "50");
        writeLED("/delay_off", "50");
   }
   else if (cmd=="status"){
	// display the current trigger details
        std::fstream fs;
	fs.open( LED3_PATH "/trigger", std::fstream::in);
	string line;
	while(getline(fs,line)) cout << line << endl;
	fs.close();
   }
   else if(cmd=="blink"){
      	int x = atoi(argv[2]);
      	cout << "Blinking the LED " << argv[2] << " times" << endl;
	removeTrigger();
      	for (int i = 0; i < x; i++){
		writeLED("/brightness", "1");
		sleep(1);
		writeLED("/brightness", "0");
		sleep(1);
	}
   }
   else{
	cout << "Invalid command!" << endl;
   }
   cout << "Finished the makeLED Program" << endl;
   return 0;
}
