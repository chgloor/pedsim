CXX = g++
CXXFLAGS = -g -O0 -fno-inline -std=c++11

SOURCES = $(shell echo *.cpp)
HEADERS = $(shell echo *.h)
OBJECTS=$(SOURCES:.cpp=.o)

libpedsim.so: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -shared -Wl,-soname,libpedsim.so -o libpedsim.so $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -fPIC -c $<

test_gtest: libpedsim.so
	$(CXX) $(CXXFLAGS) -I./ -I/usr/include/gtest -pthread tests/test_main.cpp tests/unit/*.cpp tests/acceptance/*.cpp /usr/lib/libgtest.a -o test_all -L. -lpedsim

test_mem: libpedsim.so examples
	LD_LIBRARY_PATH=. valgrind --leak-check=full --error-exitcode=1 ./example01

test: test_gtest test_mem
	LD_LIBRARY_PATH=. ./test_all

examples: libpedsim.so examples/example*.cpp
	g++ examples/example01.cpp -o example01 -I. -lpedsim -L. -g -std=c++11
	g++ examples/example02.cpp -o example02 -I. -lpedsim -L. -g -std=c++11
	g++ examples/example03.cpp -o example03 -I. -lpedsim -L. -g -std=c++11
	g++ examples/example04.cpp -o example04 -I. -lpedsim -L. -g -std=c++11

doc: documentation/doxygen.conf
	doxygen documentation/doxygen.conf
	cp ./documentation/title.png ./documentation/latex
	cp ../ecosystem/2dvis/documentation/*.png documentation/html
	cp ../ecosystem/2dvis/documentation/*.png documentation/latex
	cp ../ecosystem/3dvis/documentation/*.png documentation/html
	cp ../ecosystem/3dvis/documentation/*.png documentation/latex
	cp ../ecosystem/demoapp/documentation/*.png documentation/html
	cp ../ecosystem/demoapp/documentation/*.png documentation/latex
#	cp ./documentation/distributed/images/* documentation/html
#	cp ./documentation/distributed/images/* documentation/latex


clean:
	rm $(OBJECTS) *.so test_all example*
