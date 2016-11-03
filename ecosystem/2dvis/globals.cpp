//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "globals.h"
#include <QString>

// ALL THE GLOBAL DEFINITIONS


bool g_option_writefile = false;
QString g_option_writefile_directory = "/tmp/";

bool g_option_network = false;
int g_option_network_port = 2222;

bool g_option_file = false;
QString g_option_file_name = "pedsim_out.txt";

bool g_option_charts = false;
bool g_option_metrics = false;
