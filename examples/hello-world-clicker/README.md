# Smart Response PE

## Hello-World-Clicker
This directory contains a sample application that is intended to be run directly on a Smart Response PE Clicker (03-00174).

**Features:**
* Draws text and graphics on the 128x48 LCD
* Displays a millisecond counter (wired up to Timer 4)
* Displays a keymap indicating which keys are currently pressed
* Sends data over the serial port (wired up to USART1 Alt. 2)
  * TxD (P1_6) can be pulled off of JP2 (connect to USB-to-serial's RxD)

This is intended to be built using the Small Device C Compiler ([SDCC](http://sdcc.sourceforge.net/)).

To build it, execute the `make all` command.

![working!](https://github.com/serisman/Smart-Response-PE/raw/master/examples/hello-world-clicker/hello-world.jpg)

### Programming the CC2430
Programming the CC2430 requires a capable programming device.

To use TI's tools (i.e. [FLASH-PROGRAMMER](http://www.ti.com/tool/FLASH-PROGRAMMER)), you will need a CC-Debugger, or SmartRT04EB, or similar.

To go the DIY approach, you can use an Arduino running the [CC_Flash.ino](https://github.com/serisman/CC.Flash/blob/master/CC_Flash/CC_Flash.ino) sketch along with the [CC.Flash.exe](https://github.com/serisman/CC.Flash/blob/master/CC.Flash.exe) Windows .NET application.
This is based on the excellent work started by x893: http://akb77.com/g/rf/program-cc-debugger-cc2511-with-arduino/
