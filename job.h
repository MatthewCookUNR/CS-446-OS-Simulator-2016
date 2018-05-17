// Program Information /////////////////////////////////////////////////////////
/**
 * @file job.h
 *
 * @brief Class that handles stores the properties of the a job
 * 
 * @details This file includes the class created to take in the contain the
 *			properties of a job
 *
 * @author Matthew Cook
 *
 * @version 1.00 (15 December 16)
 */

// HEADER FILES ////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>

// GLOBAL CONSTANTS ////////////////////////////////////////////////////////////

// None

using namespace std;

class Job
{
	public:
			Job(char jobCode, int cycleNum, string name);
			~Job();

			void cacheMemory();
			void setCyclesRemaining(int num);
			char getType();
			int getCyclesRemaining();
			string getJobName();
			
	private:
			char type;
			int cyclesRemaining;
			string jobName;
};
