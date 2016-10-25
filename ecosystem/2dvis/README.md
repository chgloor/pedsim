2-dimensional visualizer 2dvis
==============================

## start

Usually, 2dvis is started in network mode, where it listens to incoming data packets on the specified UDP port.

	 ./2dvis -n 2222

Instead of a network stream it is also possible to process a XML file containing the messages. It can be specified using

	./2dvis -f filename.xml

In order to generate a video sequence out of a PEDSIM run, use these steps:

   	 ./2dvis -f ../../libpedsim/examples/pedsim_out.txt -o output
	 mencoder mf://output/*.png -mf w=1280:h=720:fps=25:type=png -ovc lavc -lavcopts vcodec=mpeg4:mbd=2:trell:vbitrate=6000 -oac copy -o example01.avi

