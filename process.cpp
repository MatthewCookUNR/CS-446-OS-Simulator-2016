// Program Information /////////////////////////////////////////////////////////
/**
 * @file process.cpp
 *
 * @brief Implementation of the class that handles stores the properties of the 
 *		  a process 
 * 
 * @details This file implements the class created to take in the contain the
 *			properties of a process, specifically state and number
 *
 * @author Matthew Cook
 *
 * @version 1.00 (6 October 16)
 * @version 1.01 (15 December 16)
 */

// HEADER FILES ////////////////////////////////////////////////////////////////

#include "process.h"

// GLOBAL CONSTANTS ////////////////////////////////////////////////////////////

// None

//using namespace std;


/**
 * @Name Paramaterized Constructor
 *
 * @details N/A
 *          
 * @param in: integer that represents the number of the process
 *
 * @ErrorsHandled: N/A
 */
PCB::PCB(int num)
{
	remainingBurstTime = 0;
	numOfJobs = 0;
	processNum = num;
	currentState = "None";
}

/**
 * @Name Paramaterized Constructor
 *
 * @details clears the list of jobs
 *          
 * @param N/A
 *
 * @ErrorsHandled: N/A
 */
PCB::~PCB()
{
	jobList.clear();
}

/**
 * @Name Set process number
 *
 * @details sets the process number of the class to the inputted integer
 *          
 * @param in: integer representing process number
 *
 * @ErrorsHandled: N/A
 */
void PCB::setProcessNum(int num)
{
	processNum = num;
}

/**
 * @Name Set process state
 *
 * @details sets the state of the class to the inputted string
 *          
 * @param in: string representing process state
 *
 * @ErrorHandled: throws error if inputted state is not valid
 */
void PCB::setState(string state)
{
	try
	{
		if( (state == ("New")) || (state == ("Ready")) || (state == ("Running")) || (state == ("Waiting")) || (state == ("Terminated")))
		{
			currentState = state;
		}
		else
		{
			throw logic_error("Inputted State is invalid");
		}
	}
	catch( exception &e)
	{
		cout << e.what() << endl;
	}
}

/**
 * @Name Get process state
 *
 * @details returns the value of currentState
 *          
 * @param out: string representing current process state
 *
 * @ErrorHandled
 */
string PCB::getState()
{
	return currentState;
}

/**
 * @Name Push Job
 *
 * @details pushes new job onto the end of the job list
 *			and increments number of jobs
 *          
 * @param in: Job to be added to the list of Jobs
 *
 * @ErrorHandled N/A
 */
void PCB::pushJob( Job newJob )
{
	jobList.push_back( newJob );
	numOfJobs++;
}

/**
 * @Name Get Number Of Jobs
 *
 * @details returns the number of jobs in process
 *          
 * @param N/A
 *
 * @ErrorHandled N/A
 */
int PCB::getNumOfJobs()
{
	return numOfJobs;
}

/**
 * @Name Get Job
 *
 * @details returns the job at the given index in
 *			job list
 *          
 * @param in: integer of the index that the user tries to get
 *
 * @ErrorHandled Does not work if there are no jobs remaining or jobNum is
 *				 invalid
 */
Job& PCB::getJob( int jobNum )
{
	if( jobNum < numOfJobs && jobNum >= 0 )
	{
		return jobList[jobNum];
	}
}

/**
 * @Name Finished Job
 *
 * @details erases a Job from the list of jobs and decrements the number
 *			of Jobs
 *          
 * @param in: integer of the index that the user tries to erase from job list
 *
 * @ErrorHandled Does not work if there are no jobs remaining or jobNum is
 *				 invalid
 */
void PCB::finishedJob( int jobNum )
{
	if( jobNum < numOfJobs && jobNum >= 0 )
	{
		jobList.erase(jobList.begin()+jobNum);
		numOfJobs--;
	}
}

/**
 * @Name Create Job
 *
 * @details takes in a line of input from the meta data and seperates it into individual
 *			jobs. Thus, adding the job to the list of jobs. If the line has a A(end) command,
 *			the current process is incremented to represent the next jobs will be for the next
 *			process.
 *          
 * @param in: string containing a line from the meta data file
 *		  out: integer representing the current process new jobs will be for
 *
 * @ErrorHandled N/A
 */
int PCB::createJob( const string& lineInput, int currentProcess)
{
		char code = lineInput[0];
		string usedBy;
		string cycleNum;
		int pivot = lineInput.find_first_of('(');
		int pivot2 = lineInput.find_last_of(')');
		if(pivot != string::npos && pivot2 != string::npos && ((pivot2-pivot) < 12)) 
		{
			usedBy = lineInput.substr(pivot, pivot2);
			cycleNum = lineInput.substr(pivot2+1, lineInput.length() - 1);
		}
		if( code != 'S' && code != 'A' )
		{
			pushJob( Job(code, atoi(cycleNum.c_str()), usedBy ) );
		}
		if( code == 'A' && usedBy == "(end)" )
		{
			return (currentProcess + 1);
		}
		return currentProcess;
		
}

/**
 * @Name Set Remaining Burst Time
 *
 * @details sets remaining burst time to the given integer
 *          
 * @param in: integer representing the new remaining burst time
 *
 * @ErrorHandled N/A
 */
void PCB::setRemainingBurstTime( int time )
{
	remainingBurstTime = time;
}

/**
 * @Name Get Remaining Burst Time
 *
 * @details returns the remaining amount of burst time for the process
 *          
 * @param N/A
 *
 * @ErrorHandled N/A
 */
int PCB::getRemainingBurstTime( )
{
	return remainingBurstTime;
}

/**
 * @Name Get Job List
 *
 * @details returns the list of jobs
 *          
 * @param N/A
 *
 * @ErrorHandled N/A
 */
vector<Job> PCB::getJobList()
{
	return jobList;
}

/**
 * @Name Get Process Number
 *
 * @details returns the numerical indentifier of the process
 *          
 * @param N/A
 *
 * @ErrorHandled N/A
 */
int PCB::getProcessNum()
{
	return processNum;
}
