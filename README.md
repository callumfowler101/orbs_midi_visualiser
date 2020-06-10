Orbs v0.2
-----
Orbs is a midi visualiser desgined to be used with any usb or virutal midi instrument. Currently it can only be run in the openFrameworks environment, however a standalone version will be released soon.

**Update v0.2 [10/06/2020]:** Single channel mode added. This allows users with an instrument that can only output on one channel at a time to use the visualiser based on pitch. 

**Overview**

Orbs can visualise up to 8 midi channels, with the channels 9-11 being used for control. Each channel has it's own cell in a 4x2 grid, with it's own colour.  Currently channels 12-16 are not used for anything. 

**Installation**

- Create a new openFrameworks project with the required addons (see below).
- Close the IDE, and replace the src and bin folders with the ones found in this repository
- Update the project using the openFrameworks project generator


**Addons**

- [ofxMidi](https://github.com/danomatika/ofxMidi)
- [ofxDatGui](https://github.com/braitsch/ofxDatGui)

**How to Use**

You can use the software without any need for setup, as long as there is one midi device connected or avaliable on the computer. However further changes can be made through the use of the gui or midi commands.

Press 'd' to access GUI.

- GUI
	- Single Channel Mode: this toggle allows you to switch between single channel (pitch) or multi-channel (channel number) to influence the groups of orbs. 
	- Scatter: this toggle makes all of the orbs appear in random positions (not tied to their cell)
	- Random Cells: this toggle re-orders the cells 
	- Radomise: this button creates a new random order for the random cells
	- Drop down menu: allows you to select your midi device

- Midi Commands
	- Sending a midi message on channels 1-8 (1-12 in single channel mode) will generate an orb in the associated cell
	- Sending a midi message on channel 13 will trigger the randomise button
	- Sending a midi message on channel 14 will trigger the random cells toggle
	- Sending a midi message on channel 15 will trigger the scatter toggle
	
**Videos**

- [Tutorial]()
- [Demonstration](https://vimeo.com/426269798)