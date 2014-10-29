## CS 179F Fall 2014: Senior Design
LIBS = -std=c++0x -Werror -pthread
CC = g++

##Global Header Files
INCLUDE = 

##Object Files and Executables
MAIN_OUT = a.out

##Requirments for each command
MAIN_REQS = newmain.o

##Targets to compile for each command
MAIN_TARGETS = newmain.cc

all:newmain

##Main
newmain: $(MAIN_REQS)
	$(CC) $(MAIN_TARGETS) $(LIBS) -o $(MAIN_OUT)
newmain.o: newmain.cc
	$(CC) $(LIBS) newmain.cc

clean:
	rm -f *~ *.o *.out
