# Smart Response PE - Games

## HANGMAN!
This directory contains a port of the popular Hangman game and is intended to be run directly on a Smart Response PE Clicker (03-00174).

This is a port of an Arduboy version available here: https://github.com/serisman/arduboy-hangman

It is intended to be built using the Small Device C Compiler ([SDCC](http://sdcc.sourceforge.net/)).

To build it, execute the `make all` command.

![title!](https://github.com/serisman/Smart-Response-PE/raw/master/games/hangman/hangman-title.jpg)

![ingame!](https://github.com/serisman/Smart-Response-PE/raw/master/games/hangman/hangman-ingame.jpg)

### Programming the CC2430
Programming the CC2430 requires a capable programming device.

To use TI's tools (i.e. [FLASH-PROGRAMMER](http://www.ti.com/tool/FLASH-PROGRAMMER)), you will need a CC-Debugger, or SmartRT04EB, or similar.

To go the DIY approach, you can use an Arduino running the [CC_Flash.ino](https://github.com/serisman/CC.Flash/blob/master/CC_Flash/CC_Flash.ino) sketch along with the [CC.Flash.exe](https://github.com/serisman/CC.Flash/blob/master/CC.Flash.exe) Windows .NET application.
This is based on the excellent work started by x893: http://akb77.com/g/rf/program-cc-debugger-cc2511-with-arduino/
