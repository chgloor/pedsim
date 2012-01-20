#include "pedsim.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {

	cout << "PedSim Example using libpedsim version " << Ped::LIBPEDSIM_VERSION << endl;

	vector<Ped::Tagent*> myagents;
	Ped::Tscene *pedscene = new Ped::Tscene();

	Ped::Twaypoint w1(-100, 0, 24);
	Ped::Twaypoint w2(+100, 0, 12);

	pedscene->addObstacle(new Ped::Tobstacle(0, -50,  0, +50));
	
	for (int i = 0; i<100; i++) { 
	  Ped::Tagent *a = new Ped::Tagent();
	  
	  a->addWaypoint(w1);
	  a->addWaypoint(w2);
	  
	  a->setPosition(-50 + rand()/(RAND_MAX/80)-40, 0 + rand()/(RAND_MAX/20) -10, 0);
	  
	  pedscene->addAgent(a);
	  myagents.push_back(a);
	}
	
	while (true) {
		for (vector<Ped::Tagent*>::iterator iter = myagents.begin(); iter != myagents.end(); ++iter) {
			Ped::Tagent *a = (*iter);
			a->move(0.2);
			a->print();
		}
	}
}

