PEDSIM Demo Application {#demoapp}
=======================

Download and Start

The PedSim Demo App can be downloaded as binary (currently for Linux and Windows), or as source code. More information regarding how to compile the source code is provided below. Once you have the executable, you must make sure it finds the PedSim library, and the Qt libraries. When you use Windows, the easiest way to do this is to just place all those .dlls into the same directory as the executable. The binary package comes already like this. If you use linux, you might have to specify the LD_LIBRARY_PATH environment variable:

    export LD_LIBRARY_PATH=.

In this example, it is assumed that the library libpedsim.so is also in the same folder as the executable.
After that, it should be possible to start the executable from the command line or the explorer.

More Documentation

- @ref demoapp_gui
- @ref demoapp_scenario


Qt is needed to compile and run the demo application!  
Get Qt from [www.qt.io](https://www.qt.io/)


## Linux

Compile the library first (libpedsim).

Then use the command line to compile the demo app:

    qmake
    make


You might need to add the path to libpedsim before you can run this:
   
    export LD_LIBRARY_PATH=../libpedsim/


## Windows (e.g. Visual Studio Express 2010)

Compile the library first (libpedsim).

copy libpedsim.lib (probably in the Release or Debug folder in libpedsim) into the libpedsim folder, and rename it to pedsim.lib

Command line:

    qmake
    nmake

Copy libpedsim.dll (probably in the Release or Debug folder in libpedsim) into the demoapp folder.

Command Line:

    pedsim.exe


![2dvis is a 2-dimensional visualizer for PEDSIM](20120204-screenshot-v2-2.png)

@latexonly
\includegraphics[width=\textwidth]{20120204-screenshot-v2-2.png}
@endlatexonly
