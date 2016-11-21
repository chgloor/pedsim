3-Dimensional Visualizer {#threedvis}
========================


The 3-dimensional visualizer is a separate application that can be
used to visualize the output of a PEDSIM simulation run. It listens on
a network socket for update information (agent positions, but also
dynamic scene definitions.), which are rendered in real-time. This is
perfectly suited to observe stand-allone simulations or optimizations
which take a long time to run. Also nice for demonstrations, where the
visualizer is installed on the machine connected to the beamer, and
the simulation runs on a separate host. 

The difference between the two visualizers is that [2dvis](@ref
twodvis) is intended for displaying a technical view of the scenario,
while 3dvis show a "real" view. 3dvis does not render the scenario
realistically in any way - however, it only shows what would be
visible in real live - i.e. no waypoints or forces.

_3dvis_ is built on _Qt_. You need _Qt 5.7_ or above with Qt3D (might
be included, check when you install Qt).  See further documenation for
compiling on [Linux](@ref linux) and [Windows](@ref windows).


## Usage

`3dvis` is always started in network mode, where it listens to
incoming data packets on the specified UDP port. In contrast to 2dvis,
it can not render file based input.

~~~~ .sh
 ./3dvis
~~~~

## Video generation

There is no built in video generation mode for 3dvis. In order to
caputre a video from a 3dvis animation, use a 3rd party capture tool,
ideally one that supports your 3D graphics card natively.

## Supported XML tags

See [here](@ref xml) for a list of valid XML tags. However, 3dvis does
not render all tags. It only renders objects that have a physical
representation, e.g. agents or obstacles.

![3dvis is a 3-dimensional visualizer for PEDSIM](3dvis.png)

@latexonly
\includegraphics[width=\textwidth]{3dvis.png}
@endlatexonly
