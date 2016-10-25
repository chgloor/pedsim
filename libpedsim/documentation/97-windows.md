Using PEDSIM on Windows
=======================

This document explains how to use _Microsoft Visual Studio Community 2015_ and _Qt 5.7_ to compile PEDSIM and the examples.

https://www.visualstudio.com/vs/community/

https://www.qt.io/download/

libpedsim
---------

Basically, in Visual Studio, create a new project of type _Win32 Console Application_, and click "Dynamic .dll" in the wizard. Uncheck the "Precompiled Header" and "Security" boxes. This will open a new project containing a few empty documents. Add all .cpp Files to the "Source Files" filter, and all .h files to the "Header Files" filter. Then remove the files that Windows generated for you, they are not used.

If you click "Build", Visual Studio will generate a libpedsim.lib and a libpedsim.dll file.

Such a project file is located in the "msvc15" folder. If you have installed Visual Studio, double click libpedsim.sln. Then, once the IDE has opened, use "Build" from the menu.


Examples (and your own programs):
---------------------------------

Again, create a new _Win32 Console Application_ project. This time, do not check he "Dynamic .dll" box (still uncheck the others). I think the default is "Console Application" here; leave that as it is. Again, remove the auto-generated files, and add e.g. the file example03.cpp.

Now here comes the tricky part. You have to specify the include and library directories. Go to "Project options", "VC++ directories". Add the path to the libpedsim source files to the "Include directories". This is where the ped_*.cpp/.h files are. Then, do the same with "Library directories", where you add the path to the libpedsim.lib file generated while compiling libpedsim.

A bit further down should be a tab called "Linker", and "Dependencies". There you have to add "libpedsim.lib" to the list of libraries to include.

Now you should be able to build the example. Again, one sample project file is in the examples folder. Theoretically, it should be possible to open that using Visual Studio, and just click on "Build" to compile example03.

Once you have generated the example03.exe file, you need to copy the libpedsim.dll file into that folder (next to the .exe). This is because libpedsim.dll is not installed in one of the system-wide folders.


2-dimensional visualizer 2dvis
------------------------------

2dvis is built on Qt. If you want to use all the features (especially charts), you need Qt 5.7 or above. It should be possible to compile it using an oder version. However, you will not see the metrics charts in 2dvis then.

Download the latest version of Qt, and install it. I think you only need the msvc15 files, about 3.0 Gb. I assume Visual Studio has been installed in the steps above. It is possible to use e.g. cygwin, but that is beyond the scope of that short introduction.

Once Qt is installed, simply double click the 2dvis.pro file. This will open Qt Creator with the project loaded, where you can build 2dvis. Before you can start the application, you need to copy various Qt libraries into the same directory. Easiest is to just double click the 2dvis.exe file, and see what happens. These qt5*d.dll libraries are somewhere in your Qt installation folder, located (probably) under C:\Qt\...\bin. Once the required ones are there, start 2dvis using the command line:


Run 2dvis from the command line:
~~~~ .sh
2dvis.exe -n 2222
~~~~

This starts a 2dvis that is listening on network port 2222 for incoming data (used by the UDPOutputWriter class of libpedsim in the examples).
