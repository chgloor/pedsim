FAQ {#faq}
===

PEDSIM Frequently Asked Questions

## General

> Is there a PEDSIM application that allows me to design, run and
> analyze my own scenario?

No. At this point, PEDSIM is a library, plus some helper
applications. This means you basically have to write your own
application. You need a C++ compiler and some computer science
knowledge.

Some helper applications are included, however. They allow you to try
simple scenarios without programming anything. You can e.g. define a
scenario in XML for the Demo Application (included), and simulate it
there. It is also possible to extend one of the C++ examples, which is
very straightforward, and visualize/analyze it using the 2-dimensional
visualizer 2dvis (included).

> Is PEDSIM suited for evacuation simulations?

PedSim is an open source implementation typically used to add
pedestrian dynamics to you own product. Is is therefore not _per se_
suited for such evacuation simulations, because it lacks a convenient
user interface. The provided sample user interface is more seen as a
demonstration of the possibilities. The target user group is not
planners, but system developers. However, the model of PedSim is
perfectly able to simulate such an evacuation scenario.

> I see that PEDSIM can be downloaded as an open-source software or
> also under a commercial license from yourself, right? Is there any
> difference in the capabilities and features of these two, or in
> their functionality?

No, at the moment there is no difference. The availability of a
commercial license is just mentioned in case somebody can not use the
GPL for whatever reason. Please contact me if you are interested in this.

## Model

> Is the model able to calculate an individual escape route for each of
> the persons within a subway station? (This includes the flow of people
> from/to the trains and the subway station)

Yes. However, at this point, the routing algorithm layer is not
available for download yet. This means that the nearest escape exit
(final point) has to be set manually per person or group of persons.
Once the routing is available, this is done automatically.

> Is the model applicable in case of fire and/or toxic gas attack?
> (Because of the different characteristics of the different
> substances.)

> Is the model able to consider dispersal of pollutants?

No. However, libpedsim is extensible, you can implement this by
yourself. Just define a model for the pollutants and add the reaction
of the agents to you pedsim application. Characteristics of gases have
not been implemented. You can easily extend the model for your own
project.

> How long does the calculation take?

This depends on the number of persons simulated and the complexity of
the scenario. In "realistic" examples, the speed of the simulation is
more than 100 times faster than real-time.

> Is the model able to consider the architecture of a subway station
> e.g. platforms, corridors, stairways, etc.?

Yes, modeling architecture is possible. There are two categories of
items in the model scenario: obstacles and paths. Obstacles can be
invisible. This allows great flexibility for modeling any kind of
architectural item.

> Is PEDSIM 3-dimensional?

While the model calculates almost everything in 3D internally, the
ground is 2D only at the moment (so no level crossings).

> Is the model able to consider inaccessible ways or places (e.g.  in
> case of a construction site)?

Yes. You can use invisible obstacles for this.

> If an agent moves in front of a convex building and the next
> waypoint is behind this building, the agent gets caught.

Yes, this is normal behavior. The agents try to proceed to the next
waypoint directly. There is, at the moment, no routing algorithm
included. Agents do not find their way around obstacles by themselves.
The easiest solution to avoid this would be to add an additional
waypoint on one side of the obstacle. Alternatively, you can add an
'invisible' wall to the obstacle to make it concave. Invisible since
you add it to the model, but do not display it somewhere.

> If too many agents move through a very narrow path which is edged
> with obstacles, the force becomes so high that some of the agents are
> pushed trough the obstacles.

Since version 2.4.1, this should no longer happen. You can play with
the obstacle forces as well. Usually, if this problem arises, it means
that something is already wrong with the scenario. If pressure is that
high, people would die in reality.

> Is it possible to consider further influencing factors?

Yes. As stated above, since the core library can be extended easily,
you can add your own factors.

## Installation, Compilation

> Can I get a binary version of PEDSIM?

Yes and no. Every now and then I compile PEDSIM on various operating
systems to check if everything is still fine everywhere. Theoretically
I can send out these binary files. Please contact me. However, these
binaries are usually a bit older than the repo release. And you still
need a C++ compiler to do anything useful with PEDSIM. You can't
really test your own scenarios using the pre-compiled binaries yet.

> Do you have a Mac version? iPhone? Android? 

I don't know. I do not own a Mac. I think is is possible to compile
the core library (libpedsim) on any modern operating system, as long
as a decent C++ compiler is available. Support is available for Linux
and Windows.

All the graphical parts use the Qt framework, which is compatible with
Mac, iOS and Android devices. See
[here](http://doc.qt.io/qt-5/supported-platforms.html). So
theoretically, PEDSIM runs almost everywhere. But I can't test it.