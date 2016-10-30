2-Dimensional Visualizer 2dvis {#2dvis}
==============================


The 2-dimensional visualizer is a separate application that can be
used to visualize the output of a PEDSIM simulation run. It listens on
a network socket for update information (agent positions, but also
dynamic scene definitions.), which are rendered in real-time. This is
perfectly suited to observe stand-allone simulations or optimizations
which take a long time to run. Also nice for demonstrations, where the
visualizer is installed on the machine connected to the beamer, and
the simulation runs on a separate host. Ah and yes, it is able to
output png files for each frame, which can be combined into a video
easily!

_2dvis_ is built on _Qt_. If you want to use all the features (especially
charts), you need _Qt 5.7_ or above. It should be possible to compile it
using an oder version. However, you will not see the metrics charts in
_2dvis_ then. See documenation for compiling on [Linux](@ref linux) and
[Windows](@ref windows).


## Usage

Usually, `2dvis` is started in network mode, where it listens to
incoming data packets on the specified UDP port.

~~~~ .sh
 ./2dvis -n 2222
~~~~

Instead of a network stream it is also possible to process a XML file
containing the messages. It can be specified using

~~~~ .sh
./2dvis -f filename.xml
~~~~


## Video generation

In order to generate a video sequence out of a PEDSIM run, use these
steps:

~~~~ .sh
./2dvis -f ../../libpedsim/examples/pedsim_out.txt -o output
mencoder mf://output/*.png -mf w=1280:h=720:fps=25:type=png -ovc lavc -lavcopts vcodec=mpeg4:mbd=2:trell:vbitrate=6000 -oac copy -o example01.avi
~~~~

Find more about _mencoder_, which is part of the _mplayer_ suite,
[here](http://www.mplayerhq.hu/).

For example videos, see PEDSIM's [YouTube
channel](https://www.youtube.com/watch?v=CxfTYi6CgNs).

## Supported XML tags

See [here](@ref xml) for a list of supported XML tags. 