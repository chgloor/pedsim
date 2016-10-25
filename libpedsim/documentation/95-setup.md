Using PEDSIM on Linux
=====================

These are some notes regardng setting up a linux development system for pedsim. If you have written software before, you might have everything needed in place already.

Basically you need a C++ compiler to compile libpedsim (the core library of PEDSIM). Graphical bits of the ecosystem folder require Qt5 - see here <a href="https://www.qt.io/developers/">https://www.qt.io/developers/</a>.

This is for Linux, I don't know much about Windows, since I do not use it. Theoretically, it is possible to compile PEDSIM on any decent C++ compiler. Reportedly NetBeans 7.4 is able to compile it nicely under Windows 8.1. Make sure your compiler supports C++11.

## C++ Compiler

I personally use gcc version 5.4.0 on a Linux Mint system. gcc 4.8 probably works just fine. 

## Preparing a system for software development

You should be root for these steps:
~~~~ .sh
sudo -s
~~~~

First install the C++ compiler:
~~~~ .sh
aptitude install gcc g++ 
~~~~

For the graphical bits install Qt5:
~~~~ .sh
aptitude install qt5-default qt5-qmake qt5-style-plugins
~~~~

PEDSIM uses Google's framework for writing C++ tests, gtest. Not strictly necessary unless you play with the source of libpedsim and want to make sure you've not broken anything. 
~~~~ .sh
aptitude install libgtest-dev cmake
cd /usr/src/gtest/
cmake .
make
mv libgtest* /usr/lib/
~~~~

To run the test, run this in the libpedsim source folder:
~~~~ .sh
make clean ; make
export LD_LIBRARY_PATH=.
make test
~~~~

If you want to update the PEDSIM documentation, you need Doxygen and, if you want pdf output, LaTeX:
~~~~ .sh
aptitude install doxygen
aptitude install texlive-full
~~~~


This export is needed since the library is not installed in a system wide known directory.

Good luck!
