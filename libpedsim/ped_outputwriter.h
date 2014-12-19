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

#include "ped_includes.h"

namespace Ped {

    /// Abstract Base Class that defines a Toutputwriter interface/default implementation.
    /// \author  chgloor
    /// \date    2014-12-18
    class LIBEXPORT OutputWriter {
    public:
        virtual ~OutputWriter() {};

        // pure virtual functions providing the framework.

        // szene
        virtual void defineScene(Tscene &s) = 0;
        virtual void addObstacle(Tobstacle &o) = 0;
        virtual void addAgent(Tagent &a) = 0;

        // agent
        virtual void drawAgent(Tagent &a) = 0;

    protected:
    };


    /// Class that defines a simple CSV OutputWriter
    /// \author  chgloor
    /// \date    2014-12-19
    class LIBEXPORT CSV_OutputWriter : public OutputWriter {
    public:
        virtual ~CSV_OutputWriter() {};

        // szene
        virtual void defineScene(Tscene &s) {};
        virtual void addObstacle(Tobstacle &o) {};
        virtual void addAgent(Tagent &a) {};

        // agent
        virtual void drawAgent(Tagent &a) { cout << a.getid() << ", " << a.getx() << ", " << a.gety() << endl; };

    protected:
    };


}

#endif
