Using PEDSIM on Windows {#windows}
=======================

This document explains how to use [_Microsoft Visual Studio Community 2015_][msvc] and [Qt _5.7_][qt] to compile PEDSIM and the examples.

[msvc]:   https://www.visualstudio.com/vs/community/ "Visual Studio Community"

[qt]:     https://www.qt.io/download/ "Qt Download Page"


libpedsim
---------

Basically, in _Visual Studio_, create a new project of type _Win32
Console Application_, and click "DLL" in the wizard. Uncheck the
"Precompiled Header" and "Security Development Lifecycle (SDL) checks"
boxes. This will open a new project containing a few empty
documents. Add all `.cpp` Files to the "Source Files" filter, and all
`.h` files to the "Header Files" filter. Then remove the files that
Windows generated for you, they are not used.

If you click "Build", Visual Studio will generate a `libpedsim.lib` and a `libpedsim.dll` file.

Such a solution file is located in the "msvc15" folder. If you have
installed Visual Studio, double click `libpedsim.sln`. Then, once the
IDE has opened, use "Build Solution F7" from the menu. This will
generate a folder called "x64" (on a 64bit system), with a subfolder
called "Debug". In there are the compiled library files. Copy
`libpedsim.dll` and `libpedsim.lib` into the `/pedsim/libpedsim/` folder
(where the `.cpp` and `.h` files are).


Examples (and your own programs):
---------------------------------

Again, create a new _Win32 Console Application_ project. This time, do
not check he "DLL" box (still uncheck the others). I think the default
is "Console Application" here; leave that as it is. Again, remove the
auto-generated files, and add e.g. the file `example03.cpp`.

Now here comes the tricky part. You have to specify the include and
library directories. Go to "Project Properties Alt+F7". You probably
have to select the item below the top item in the menu at the
left. The first is the "solution", the second is the "project" which
is what we need. Once opened, there is a window with "Configuration
Properties".  Go to "VC++ Directories". Add the path to the libpedsim
source files to the "Include Directories". This is where the
`ped_*.cpp`/`.h` files are.  Then, do the same with "Library Directories",
where you add the path to the libpedsim.lib file generated while
compiling libpedsim.

A bit further down should be a tab called "Linker", and "Input". There
you have to add `libpedsim.lib` to the list of libraries to include
("Additional Dependencies).

Now you should be able to build the example. Again, one sample project
file is in the examples folder.  Theoretically, it should be possible
to open that using _Visual Studio_, and just click on "Build Solution
F7" to compile `example03.exe`.

Once you have generated the `example03.exe` file, you need to copy the
`libpedsim.dll` file into that folder (next to the `.exe`). This is
because `libpedsim.dll` is not installed in one of the system-wide
folders.


2-dimensional visualizer 2dvis
------------------------------

2dvis is built on _Qt_. If you want to use all the features (especially
charts), you need _Qt 5.7_ or above. It should be possible to compile it
using an older version. However, you will not see the metrics charts in
2dvis then.

Download the latest version of Qt, and install it. I think you only
need the msvc15 files, about 3.0 GB. I assume _Visual Studio_ has been
installed in the steps above. It is possible to use e.g. _Cygwin_, but
that is beyond the scope of that short introduction.

Once _Qt_ is installed, simply double click the `2dvis.pro` file. This
will open _Qt Creator_ with the project loaded, where you can build
`2dvis.exe`. Before you can start the application, you need to copy various
`Qt` libraries into the same directory. Easiest is to just double click
the `2dvis.exe` file, and see what happens. These `qt5*d.dll` libraries
are somewhere in your _Qt_ installation folder, located (probably) under
`C:\Qt\...\bin`. Once the required ones are there, start 2dvis using the
command line:


Run 2dvis from the command line:
~~~~ .sh
2dvis.exe -n 2222
~~~~

This starts a 2dvis that is listening on network port 2222 for
incoming data (used by the Ped::UDPOutputWriter class of _libpedsim_
in the examples).
