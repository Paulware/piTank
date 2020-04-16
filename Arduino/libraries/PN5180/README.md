# PN5180-Library

Arduino Uno / Arduino ESP-32 library for PN5180-NFC Module from NXP Semiconductors

![PN5180-NFC module](./doc/PN5180-NFC.png)
![PN5180 Schematics](./doc/FritzingLayout.jpg)

Release Notes:

Version 1.3 - 21.05.2019
	
	* Initialized Reset pin with HIGH
	* Made readBuffer static
	* Typo fixes
	* Data type corrections for length parameters
	
Version 1.2 - 28.01.2019

	* Cleared Option bit in PN5180ISO15693::readSingleBlock and ::writeSingleBlock

Version 1.1 - 26.10.2018
	
	* Cleanup, bug fixing, refactoring
	* Automatic check for Arduino vs. ESP-32 platform via compiler switches
	* Added open pull requests
	* Working on documentation
	
Version 1.0.x - 21.09.2018

	* Initial versions
	
