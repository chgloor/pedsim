PEDSIM Demo Application
=======================

Qt is needed to compile and run the demo application!  
Get Qt from [qt.digia.com](http://qt.digia.com/)


## Linux

Compile the library first (libpedsim).

Command line:
```bash
qmake
make
```

You might need to add the path to libpedsim before you can run this:
```bash
export LD_LIBRARY_PATH=../libpedsim/
```

## Windows (e.g. Visual Studio Express 2010)

Compile the library first (libpedsim).

copy libpedsim.lib (probably in the Release or Debug folder in libpedsim) into the libpedsim folder, and rename it to pedsim.lib

Command line:
```
qmake
nmake
```

Copy libpedsim.dll (probably in the Release or Debug folder in libpedsim) into the demoapp folder.

Command Line:
```
pedsim.exe
```