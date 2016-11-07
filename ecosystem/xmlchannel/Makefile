LIBRARIES = -lexpat

NAME = xmlchannel

CC = g++
CFLAGS = -Wall 

OBJECTS = logger.o main.o

xmlchannel: ${OBJECTS}
	$(CC) $(CFLAGS)-o $(NAME) ${OBJECTS} $(LIBDIR) $(LIBRARIES)  

main.o : main.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c main.cpp

logger.o: logger.cpp logger.h
	$(CC) $(CFLAGS) $(INCLUDE) -c logger.cpp

clean:
	rm -rf *.o *~ core $(NAME) test
