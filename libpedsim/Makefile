CXX = g++
CXXFLAGS = -g -O0 -fno-inline -std=c++0x

libpedsim.so: ped_obstacle.cpp ped_vector.cpp ped_waypoint.cpp ped_agent.cpp ped_scene.cpp ped_tree.cpp
	$(CXX) $(CXXFLAGS) -fPIC -c ped_vector.cpp -o ped_vector.o
	$(CXX) $(CXXFLAGS) -fPIC -c ped_outputwriter.cpp -o ped_outputwriter.o
	$(CXX) $(CXXFLAGS) -fPIC -c ped_scene.cpp -o ped_scene.o
	$(CXX) $(CXXFLAGS) -fPIC -c ped_tree.cpp -o ped_tree.o
	$(CXX) $(CXXFLAGS) -fPIC -c ped_obstacle.cpp -o ped_obstacle.o
	$(CXX) $(CXXFLAGS) -fPIC -c ped_waypoint.cpp -o ped_waypoint.o
	$(CXX) $(CXXFLAGS) -fPIC -c ped_agent.cpp -o ped_agent.o
	$(CXX) $(CXXFLAGS) -shared -Wl,-soname,libpedsim.so -o libpedsim.so ped_obstacle.o ped_vector.o ped_waypoint.o ped_agent.o ped_scene.o ped_tree.o ped_outputwriter.o

test_gtest: libpedsim.so
	$(CXX) $(CXXFLAGS) -I./ -I/usr/include/gtest -pthread tests/test_main.cpp tests/unit/*.cpp tests/acceptance/*.cpp /usr/lib/libgtest.a -o test_all -L. -lpedsim

test_mem: libpedsim.so examples
	LD_LIBRARY_PATH=. valgrind --leak-check=full --error-exitcode=1 ./example01

test: test_gtest test_mem
	LD_LIBRARY_PATH=. ./test_all

examples: libpedsim.so examples/example*.cpp
	g++ examples/example01.cpp -o example01 -I. -lpedsim -L. -g -std=c++0x
	g++ examples/example02.cpp -o example02 -I. -lpedsim -L. -g -std=c++0x
	g++ examples/example03.cpp -o example03 -I. -lpedsim -L. -g -std=c++0x
	g++ examples/example04.cpp -o example04 -I. -lpedsim -L. -g -std=c++0x
	g++ examples/example05.cpp -o example05 -I. -lpedsim -L. -g -std=c++0x

doc: documentation/doxygen.conf
	doxygen documentation/doxygen.conf
	cp ./documentation/*.png ./documentation/latex
	cp ./documentation/*.png ./documentation/html
	cp ../ecosystem/2dvis/documentation/*.png documentation/html
	cp ../ecosystem/2dvis/documentation/*.png documentation/latex
	cp ../ecosystem/3dvis/documentation/*.png documentation/html
	cp ../ecosystem/3dvis/documentation/*.png documentation/latex
	cp ../ecosystem/demoapp/documentation/*.png documentation/html
	cp ../ecosystem/demoapp/documentation/*.png documentation/latex
#	cp ./documentation/distributed/images/* documentation/html
#	cp ./documentation/distributed/images/* documentation/latex


clean:
	rm *.o *.so test_all example*
