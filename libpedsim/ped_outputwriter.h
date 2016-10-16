//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) 2003 - 2014 by Christian Gloor
//

#ifndef _ped_outputwriter_h_
#define _ped_outputwriter_h_ 1

#ifdef WIN32
#define LIBEXPORT __declspec(dllexport)
#else
#define LIBEXPORT
#endif

#include <iostream>
#include <fstream>

#include "ped_includes.h"

namespace Ped {

    /// Abstract Base Class that defines a Toutputwriter interface/default implementation.
    /// \author  chgloor
    /// \date    2014-12-18
    class LIBEXPORT OutputWriter {
    public:
        virtual ~OutputWriter() {};

        // pure virtual functions providing the framework.

	// general
	virtual void writeTimeStep(long int timestep) = 0;
	virtual void setScenarioName(string name) = 0;
	virtual void drawLine(Tvector &s, Tvector &e, int duration = 1, double red = 1.0, double green = 1.0, double blue = 1.0) = 0;

        // szene
        virtual void defineScene(Tscene &s) = 0;
        virtual void addObstacle(Tobstacle &o) = 0;
        virtual void addAgent(Tagent &a) = 0;
        virtual void addWaypoint(Twaypoint &w) = 0;

        // agent
        virtual void drawAgent(Tagent &a) = 0;
	// obstacle
        virtual void drawObstacle(Tobstacle &o) = 0;
	// waypoint
        virtual void drawWaypoint(Twaypoint &w) = 0;

    protected:
    };


    /// Class that defines a simple CSV OutputWriter
    /// \author  chgloor
    /// \date    2014-12-19
    class LIBEXPORT CSV_OutputWriter : public OutputWriter {
    public:
        virtual ~CSV_OutputWriter() {};

	// general
	virtual void writeTimeStep(long int timestep) {};

        // szene
        virtual void defineScene(Tscene &s) {};
        virtual void addObstacle(Tobstacle &o) {};
        virtual void addAgent(Tagent &a) {};
        virtual void addWaypoint(Twaypoint &w) {};

        // agent
        virtual void drawAgent(Tagent &a) { cout << a.getid() << ", " << a.getPosition().x << ", " << a.getPosition().y << endl; };

    protected:
    };


    /// Class that defines a frame-by-frame proprietary XMLOutputWriter.
    /// For supported tags, see @ref xml_specs.
    /// \author  chgloor
    /// \date    2016-07-02
    class LIBEXPORT XMLOutputWriter : public OutputWriter {
    public:
        XMLOutputWriter();
        XMLOutputWriter(string scenarioname);
        virtual ~XMLOutputWriter();

	// general
	virtual void writeTimeStep(long int timestep);
	virtual void setScenarioName(string name);
	virtual void drawLine(Tvector &s, Tvector &e, int duration = 1, double red = 1.0, double green = 0.0, double blue = 0.0);

        // szene
        virtual void defineScene(Tscene &s) {};
        virtual void addObstacle(Tobstacle &o) {};
        virtual void addAgent(Tagent &a) {};
        virtual void addWaypoint(Twaypoint &w) {};

        // agent
        virtual void drawAgent(Tagent &a);

        // obstacle
        virtual void drawObstacle(Tobstacle &o);

        // waypoint
        virtual void drawWaypoint(Twaypoint &w);

    protected:
	virtual void write(string message) {};
    };

    /// Class that defines a frame-by-frame proprietary XMLOutputWriter.
    /// For supported tags, see @ref xml_specs.
    /// \author  chgloor
    /// \date    2016-08-09
    class LIBEXPORT FileOutputWriter : public XMLOutputWriter {
    public:
      FileOutputWriter();
      virtual ~FileOutputWriter();

    protected:
	virtual void write(string message);
	ofstream outfile_;
    };

    /// Class that defines a frame-by-frame proprietary XMLOutputWriter that sends output over the network.
    /// For supported tags, see @ref xml_specs.
    /// \author  chgloor
    /// \date    2016-10-09
    class LIBEXPORT UDPOutputWriter : public XMLOutputWriter {
    public:
      UDPOutputWriter();
      virtual ~UDPOutputWriter();

    protected:
	virtual void write(string message);
	int socket_;
    };


}

#endif
