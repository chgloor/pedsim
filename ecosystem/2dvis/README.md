2-Dimensional Visualizer {#twodvis}
========================


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

~~~~ .sh
Usage: ./2dvis [options]
2-dimensional PEDSIM visualizer.

Options:
  -h, --help                         Displays this help.
  -q, --quiet                        Do not show graphical output
  -n, --network <port>               Read input from network on port <port>
  -f, --file <file>                  Read input from <file>
  -c, --charts                       Display charts DockWidget
  -m, --metrics                      Display metrics DockWidget
  -o, --outputdirectory <directory>  Write frame-by-frame image output to <directory>
~~~~

Usually, `2dvis` is started in network mode, where it listens to
incoming data packets on the specified UDP port.

~~~~ .sh
 ./2dvis -n 2222
~~~~

## Metrics and charts display

2dvis has the ability to display user-defined metrics coming from the
simulation. It can display the latest metrics in numerical form, and
also chart the values as line graphs. These two dockable windows are
enabled by specifying `-m`/`--metrics` or `-c`/`--charts` respectively
on the command line. Note that the charts window needs _Qt_ version
5.7 or above. Otherwise the feature will not be compiled in. Numerical
metrics work for all _Qt_ versions.

These metrics are submitted from the simulation using
Ped::XMLOutputWriter::writeMetrics(std::unordered_map<std::string,
std::string> hash). For example like this:

~~~~ .cpp
ow->writeMetrics({{"name1", "value1"}, {"name2", "value2"}});
~~~~

Here is an example with metrics transmitted:

~~~~ .cpp
ow->writeMetrics({
  {"Average Timesteps", std::to_string(sum_age/agents.size())},
  {"Average Theta", std::to_string(sum_theta/agents.size())},
  {"Average Sensitivity L", std::to_string(sum_sensitivity_l/agents.size())},
  {"Average Sensitivity R", std::to_string(sum_sensitivity_r/agents.size())},
  {"Average Reach", std::to_string(sum_reach/agents.size())}
});
~~~~

![2dvis is a 2-dimensional visualizer for PEDSIM](2dvis_metrics.png)
@latexonly
\includegraphics[width=\textwidth]{2dvis_metrics.png}
@endlatexonly

## Video generation

Instead of a network stream it is also possible to process a XML file
containing the messages. This is meant for creating videos. At the
moment, 2dvis will try to play all events in full speed, resulting in
an overloaded graphics engine. Use it together with the `-o` output
option only. This mode can be specified using

~~~~ .sh
./2dvis -f filename.xml
~~~~

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

![2dvis is a 2-dimensional visualizer for PEDSIM](2dvis.png)
@latexonly
\includegraphics[width=\textwidth]{2dvis.png}
@endlatexonly
