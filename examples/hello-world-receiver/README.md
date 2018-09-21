# Smart Response PE

## Hello-World-Receiver
This directory contains a sample application that is intended to be run directly on a Smart Response PE Receiver (03-00099-21).

**Features:**
* Sends data over the serial port (the CP2102 is wired up to USART1 Alt. 2)

This is intended to be built using the Small Device C Compiler ([SDCC](http://sdcc.sourceforge.net/)).

To build it, execute the `make all` command.

### Programming the CC2430
Programming the CC2430 requires a capable programming device.

To use TI's tools (i.e. [FLASH-PROGRAMMER](http://www.ti.com/tool/FLASH-PROGRAMMER)), you will need a CC-Debugger, or SmartRT04EB, or similar.

To go the DIY approach, you can use an Arduino running the [CC_Flash.ino](https://github.com/serisman/CC.Flash/blob/master/CC_Flash/CC_Flash.ino) sketch along with the [CC.Flash.exe](https://github.com/serisman/CC.Flash/blob/master/CC.Flash.exe) Windows .NET application.
This is based on the excellent work started by x893: http://akb77.com/g/rf/program-cc-debugger-cc2511-with-arduino/
