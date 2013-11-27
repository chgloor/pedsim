

-----------------------------------------------------
Qt is needed to compile and run the demo application! 
Get Qt from qt.nokia.com
-----------------------------------------------------


Linux:

Compile the library first (libpedsim)

Command Line:

qmake
make




Windows (e.g. Visual Studio Express 2010):

Compile the library first (libpedsim)

copy libpedsim.lib (probably in the Release or Debug folder in libpedsim) into the libpedsim folder, and rename it to pedsim.lib

Command Line:

qmake
nmake

copy libpedsim.dll (probably in the Release or Debug folder in libpedsim) into the demoapp folder.

Command Line:

pedsim.exe
