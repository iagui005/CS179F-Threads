## CS 179F Fall 2014: Senior Design
LIBS = -std=c++0x -Werror -pthread
CC = g++

##Global Header Files
INCLUDE = 

##Object Files and Executables
MAIN_OUT = a.out

##Requirments for each command
MAIN_REQS = main.o thread.o

##Targets to compile for each command
MAIN_TARGETS = main.cc thread.h

all:main

##Main
main: $(MAIN_REQS)
	$(CC) $(MAIN_TARGETS) $(LIBS) -o $(MAIN_OUT)
main.o: main.cc
	$(CC) $(LIBS) main.cc
thread.o: thread.h
	$(CC) $(LIBS) thread.h

clean:
	rm -f *~ *.o *.out
