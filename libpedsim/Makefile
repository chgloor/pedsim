CXX = gcc

libpedsim.so: ped_obstacle.cpp ped_vector.cpp ped_waypoint.o ped_agent.o ped_scene.o
	$(CXX) -fPIC -c ped_vector.cpp -o ped_vector.o
	$(CXX) -fPIC -c ped_scene.cpp -o ped_scene.o
	$(CXX) -fPIC -c ped_obstacle.cpp -o ped_obstacle.o
	$(CXX) -fPIC -c ped_waypoint.cpp -o ped_waypoint.o
	$(CXX) -fPIC -c ped_agent.cpp -o ped_agent.o
	$(CXX) -shared  -Wl,-soname,libpedsim.so -o libpedsim.so ped_obstacle.o ped_vector.o ped_waypoint.o ped_agent.o ped_scene.o

doc: doxygen.conf
	doxygen doxygen.conf

clean:
	rm *.o *.so