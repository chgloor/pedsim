PEDSIM Demo Application {#demoapp}
=======================

## Introduction and purpose of the Demo Application

Originally, PEDSIM was a monolithic software package that was capable
to read simple scenario definitions from a file and run the crowd
simulation. This was PEDSIM version 1.x. For version 2.x, PEDSIM has
been separated into a library and the Demo Application. These two
pieces of software do more or less the same as PEDSIM Version 1.x, but
with less import/export and scenario analysis features.

The main focus of development is on the PEDSIM library, since it is
assumed that interested users are quickly able to develop their own
software using the library. The Demo Application is still being
maintained, but no longer extended. Its purpose is now to show how
`libpedsim` can be used in a flexible way. It uses OOP inheritance to
achive a tighter integration. These offers possibilities beyond what
is presented in the code examples.

At the same time the Demo App is used as a _manual_ integration test
case. The library contains unit and user acceptance tests, based on
the Google test framework. These tests are run automatically and are
supposed to cover all possible aspects of failure. However, I believe
that in the end a human has to look at the output of the system and
judge if everything still looks sane. This is what the Demo
Application is used for internally.

The scenario input features mentioned above are still a good starting
point for your own small experiments. It is possible to define a
scenario by writing a simple XML file, and use the user interface to
quickly play with the various forces of the underlying model.

## More Documentation

- @ref demoapp_gui
- @ref demoapp_scenario

## Compilation

Qt is needed to compile and run the demo application!  See the
installation documentation on [Linux](@ref linux) and [Windows](@ref windows)
for more information regarding compillation of the source
code.

Please note that (at least for the time being) the DemoApp does not
link `libpedsim` dynamically using the .dll on Windows or the .so
library on Linux respectively. This is due to bug related to
incompatible compiler versions or settings in Qt and msvc15, which is
often used to compile the library on Windows.

The source of `libpedsim` is directly included in the DemoApp Qt
project file. This means that there is no need to compile the library
separately at the moment. Compiling the DemoApp will also compile and
statically link the library into the code. No need to link the
library, or specify its location.

This method of including `libpedsim` can also be used by your own
project. Make sure you do not violate the terms of the GPL doing this,
e.g. by including the library source into your commercial
projects. (Linking the library is OK under the terms of the
LGPL.)

![PEDSIM Demo App](screenshot.png)

@latexonly
\includegraphics[width=\textwidth]{screenshot.png}
@endlatexonly
