# pantempi

pantempi is a temperature and humidity sensor board based on the panStamp
wireless sensor nodes.


## git submodule configuration

This repository uses external repostiories using git submodules:

    $ git submodules init
    $ git submodules update


## Hardware Assembly

Each panStamp needs an antenna. A simple wire stub should do. The default
frequency is 868 MHz, but they can also operate on 915 MHz if you chose so
later on.

                 |  868 MHz | 915 MHz  |
  --------------:|---------:|---------:|
  1/4 Wavelength |  82.2 mm |  77.9 mm |
  1/2 Wavelength | 164.3 mm | 155.9 mm |

In experiments it seems like that these do not have to be very exact on short
distance, so any wirelength around 8 cm should do.

(Source: http://code.google.com/p/panstamp/wiki/antennalengths)


## Software Requirements

### Arduino IDE

While the Arduino-Makefile used in this project allows to compile the firmware
from the command line without use of the Arduino IDE, the toolchain and Arduino
core libraries are still required. The Makefile detects an existing
installation Arduino IDE installation and uses its resources. Your mileage may
vary.

http://arduino.cc/en/Main/Software


### Arduino panstamp library

This is required for the pantempi firmware. Import library with the help of the
Arduino IDE or simply place the panstamp folder in this ZIP file into the
.../arduino/libraries/ directory (detailed installation instructions can be
found at http://arduino.cc/en/Guide/Libraries).

DO NOT USE THE LIBRARY FROM THE SUBVERSION OR tools/panstamp/arduino/.
Apparently EEPROM handling is broken in this version at the moment and
therefore new nodes with this firmware cannot be configured remotely. Use the
release from the panStamp website.

http://www.panstamp.com/downloads/panstamp_library.zip?attredirects=0&d=1


### Arduino Timer1 library

This is required for the modem firmware. See instructins above.

http://playground.arduino.cc/code/timer1


### panStamp Python applications

The host software components are already available in tools/panstamp/python
after initializing the git submodules as described above. While the upstream
release should work, the local branch contains portability fixes for
pyswapdmtgui. Additionally it fixes pyswapdmt which offers a command line
interface to sniff and monitor SWAP traffic and configure nodes.

The python applications have their own requirements, depending on which tool
you want to use you will need python >= 2.6, wxPython >=2.8, and pyserial.

(http://www.panstamp.com/downloads/panStamp_apps.zip?attredirects=0&d=1)


## Building & Flashing

...


## Deployment

...

