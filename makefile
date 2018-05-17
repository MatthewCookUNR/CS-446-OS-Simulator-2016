#Compiler Flags
CXXFLAGS=-g -Wall -std=c++11

Sim03: main.cpp main.o processHandler.o process.o timer.o simFunctions.o job.o
	g++ main.o processHandler.o process.o timer.o simFunctions.o job.o -o Sim04 -pthread

main.o: main.cpp processHandler.h
	g++ -c -o main.o main.cpp -pthread

processHandler.o: processHandler.h processHandler.cpp
	g++ -c -o processHandler.o processHandler.cpp -pthread

process.o: process.h process.cpp
	g++ -c -o process.o process.cpp -pthread

timer.o: SimpleTimer.h SimpleTimer.cpp
	g++ -c -o timer.o SimpleTimer.cpp -pthread

job.o:
	g++ -c -o job.o job.cpp -pthread

simFunctions.o:
	g++ -c -o simFunctions.o SimulatorFunctions.c -pthread


clean:
	rm *.o Sim04
