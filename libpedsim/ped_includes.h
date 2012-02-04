
#ifndef _ped_pedsim_h_
#define _ped_pedsim_h_ 1

#ifdef WIN32
#define LIBEXPORT __declspec(dllexport)
#else
#define LIBEXPORT
#endif

#include "ped_agent.h"
#include "ped_obstacle.h"
#include "ped_waypoint.h"
#include "ped_scene.h"

namespace Ped {
	const double LIBEXPORT LIBPEDSIM_VERSION = 2.1;
}

#endif
