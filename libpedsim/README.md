libpedsim {#mainpage}
=========

## General Usage Notes

- Create a Tscene
- Create some Tobstacles
- Add the obstacles to the scene
- Create some Tagents
- Create some Twaypoints
- Add the waypoints to the agents
- Add the agents to the scene
- Call Tagent->move() for each timestep

See the Code Example further down, and have a look
at the full source code, available on the <a
href="/download/">download</a> page.

## Detailed Class Documentation

There is a complete documentation of the classes in the library. It is
automatically generated out of the source code. You can <a
href="annotated.html">access this documentation online here</a>.
This same documentation is delivered as PDF file with the library for
offline use.
 
## Code Example

This example shows the very basic usage of the library. No fancy
graphics, of course, only text output to the console.  This is
example01.cpp in the examples folder.  

<dl class="warning"><dt><b>Please note:</b></dt><dd> Additional steps
around the example code might be required in order to compile it. If
you are using _Windows_ and, for example, _MS Visual C++ 2010 Express_,
you can create a new console application using the wizard. Create a
file called `example01.cpp` and copy-paste the code into it. In the
project's _Properties_, under _Linker/Input_, add `libpedsim.lib` in
front of the _Additional Dependencies_ list. Click run.  </dd></dl>

On a typical linux system, if you are in the
_libpedsim_ folder, use this to compile, link and run:

~~~~ .sh
g++ examples/example01.cpp -o example -lpedsim -L. -I. -std=c++11
export LD_LIBRARY_PATH=.
./example
~~~~

It will create 100 agents, which are placed somewhat randomly
distributed around -50/0. They should walk between -100/0 and 100/0.
An obstacle (wall) is placed from 0/-50 to 0/50. The agents must walk
around that obstacle. That's it, as simple as that: the agents will
walk with that little code. 

If you want to display some graphics, write a file, or send data over
the network, you will get the agent's positions with <a
href="latest/classPed_1_1Tagent.html"
class="code">a-&gt;getPosition()</a>.  Of course, you can inherit your
own classes from Tagent, Tobctacle etc, if you want to have more
control.  See the <a href="/documentation/demoapp/index.html">Demo App
Source</a> for an example.

\include examples/example01.cpp

