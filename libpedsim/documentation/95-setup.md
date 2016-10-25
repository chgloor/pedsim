Using PEDSIM on Linux
=====================

These are some notes regardng setting up a linux development system for pedsim. If you have written software before, you might have everything needed in place already.

Basically you need a C++ compiler to compile libpedsim (the core library of PEDSIM). Graphical bits of the ecosystem folder require Qt5 - see here <a href="https://www.qt.io/developers/">https://www.qt.io/developers/</a>. Other compilers might work - make sure they support C++11.


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

PEDSIM uses Google's test framework for writing C++ tests, _gtest_. Not strictly necessary unless you play with the source of libpedsim and want to make sure you've not broken anything. 
~~~~ .sh
aptitude install libgtest-dev cmake
cd /usr/src/gtest/
cmake .
make
mv libgtest* /usr/lib/
~~~~

To run the tests, run this in the libpedsim source folder:
~~~~ .sh
make clean ; make
export LD_LIBRARY_PATH=.
make test
~~~~
This export is needed since the library is not installed in a system wide known directory.


If you want to update the PEDSIM documentation, you need Doxygen and, if you want pdf output, LaTeX:
~~~~ .sh
aptitude install doxygen
aptitude install texlive-full
~~~~


Good luck!
