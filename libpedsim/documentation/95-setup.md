Using PEDSIM on Linux {#linux}
=====================

These are some notes regardng setting up a Linux development system for PEDSIM. If you have written software before, you might have everything needed in place already.

Basically you need a C++ compiler to compile _libpedsim_ (the core library of PEDSIM). Graphical bits of the ecosystem folder require _Qt5_ - see here <a href="https://www.qt.io/developers/">https://www.qt.io/developers/</a>. Other compilers might work - make sure they support *C++11*.


## C++ Compiler

I personally use _gcc version 5.4.0_ on a _Linux Mint_ system. _gcc 4.8_ probably works just fine. 

## Preparing a system for software development

You should be root for these steps:
~~~~ .sh
sudo -s
~~~~

First install the C++ compiler:
~~~~ .sh
aptitude install gcc g++ 
~~~~

For the graphical bits install _Qt5_:
~~~~ .sh
aptitude install qt5-default qt5-qmake qt5-style-plugins
~~~~


If you want to update the PEDSIM documentation, you need _Doxygen_ and, if you want pdf output, _LaTeX_:
~~~~ .sh
aptitude install doxygen
aptitude install texlive-full
~~~~


Good luck!
