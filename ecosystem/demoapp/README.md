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

![PEDSIM Demo App](screenshot.png)

@latexonly
\includegraphics[width=\textwidth]{screenshot.png}
@endlatexonly
