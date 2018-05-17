// Program Information /////////////////////////////////////////////////////////
/**
 * @file process.h
 *
 * @brief Class that handles stores the properties of the a process
 * 
 * @details This file includes the class created to take in the contain the
 *			properties of a process
 *
 * @author Matthew Cook
 *
 * @version 1.00 (6 October 16)
 * @version 1.01 (15 December 16)
 */

// HEADER FILES ////////////////////////////////////////////////////////////////

#include "job.h"
#include <string>
#include <exception>
#include <iostream>
#include <vector>
#include <stdlib.h>

// GLOBAL CONSTANTS ////////////////////////////////////////////////////////////

// None

using namespace std;

class PCB
{
	public:
			PCB( int num );
			~PCB();
			void setProcessNum(int num);
			void setState( string state);
			void setRemainingBurstTime( int time );
			void pushJob( Job newJob );
			void finishedJob( int jobNum );
			int createJob( const string& lineInput, int currentProcess);

			int getRemainingBurstTime();
			int getNumOfJobs();
			Job& getJob( int jobNum );
			vector<Job> getJobList();
			int getProcessNum();
			string getState();
	private:
			int remainingBurstTime;
			int processNum;
			vector<Job> jobList;
			int numOfJobs;
			string currentState;
};

