# MicroAdventure -- An Arduino-type project using flash memory to hold a Colossal Cave-like data structure.

This code uses about 9K of Flash memory on an Uno to store about 30 rooms of description and navigation. Many more rooms and additional complexity is possible:

    Sketch uses 8914 bytes (27%) of program storage space. Maximum is 32256 bytes.
    Global variables use 466 bytes (22%) of dynamic memory, leaving 1582 bytes for local variables. Maximum is 2048 bytes.

Based on :

* https://github.com/osgcc/colossal-cave-adventure and 
 https://github.com/osgcc/colossal-cave-adventure/blob/master/advdat.77-03-31
* https://forum.arduino.cc/t/storing-a-struct-array-in-progmem/512308
* https://www.pjrc.com/teensy/td_libs_FrequencyTimer2.html
* https://en.wikipedia.org/wiki/Hunt_the_Wumpus 

Dave Forrest 
