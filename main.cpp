// Program Information /////////////////////////////////////////////////////////
/**
 * @file main.cpp
 *
 * @brief Main function for the OS Simulator for CS 446
 * 
 * @details This file includes the main which creates a object of the 
 *			processHandler class. Then the function starts a timer to keep
 *			track of time and proceeds to run the desired process(s).
 *	
 * @author Matthew Cook
 *
 * @version 1.00 (15 September 16)
 * @version 1.01 (6 October 16)
 * @version 1.02 (15 December 16)
 */

// HEADER FILES ////////////////////////////////////////////////////////////////

#include "processHandler.h"

// GLOBAL CONSTANTS ////////////////////////////////////////////////////////////

// None
using namespace std;

int main(int argc, char* argv[])
{
	processHandler test1(argv[1]);
	test1.timer1.start();
	test1.buildProcessList();
	test1.calculateBurstTime();
	while( test1.getNumOfProcesses() > 0 )
	{
		test1.runQuantum(test1.scheduleProcesses());
	}
	test1.timer1.stop();
	test1.timer1.getElapsedTime(test1.currentTime);
	return 0;
}

