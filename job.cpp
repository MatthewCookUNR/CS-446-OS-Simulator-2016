// Program Information /////////////////////////////////////////////////////////
/**
 * @file job.cpp
 *
 * @brief Implementation of job classe that handles stores the properties of the
 *		  current process
 * 
 * @details This file implements the class created to take in the contain the
 *			properties of a job
 *
 * @author Matthew Cook
 *
 * @version 1.00 (15 December 16)
 */

// HEADER FILES ////////////////////////////////////////////////////////////////

#include "job.h"

// GLOBAL CONSTANTS ////////////////////////////////////////////////////////////

// None


/**
 * @Name Parameterized Constructor
 *
 * @details initializes data members of the Job with
 *			inputted vlaues
 * @param in: character that represents the code of the job
 *		  in: integer with the number of cycles the job should run for
 *	      in: string with the name of the job
 *
 * @ErrorsHandled: N/A
 */
Job::Job(char jobCode, int cycleNum, string name )
{
	type = jobCode;
	cyclesRemaining = cycleNum;
	jobName = name;
}

/**
 * @Name Deconstructor
 *
 * @details N/A
 *          
 * @param N/A
 *
 * @ErrorsHandled: N/A
 */
Job::~Job()
{

}

/**
 * @Name Cache Memory
 *
 * @details Simulates memory being cached by decreasing its
 *			the cycles the job has remaining by 2
 *          
 * @param N/A
 *
 * @ErrorsHandled: N/A
 */
void Job::cacheMemory()
{
	if( cyclesRemaining > 2 )
	{
		cyclesRemaining = cyclesRemaining - 2;
	}
}

/**
 * @Name Get Type
 *
 * @details returns the character representing job type
 *          
 * @param N/A
 *
 * @ErrorsHandled: N/A
 */
char Job::getType()
{
	return type;
}

/**
 * @Name Get Cycles Remaining
 *
 * @details returns the number of cycles remaining for the job
 *          
 * @param N/A
 *
 * @ErrorsHandled: N/A
 */
int Job::getCyclesRemaining()
{
	return cyclesRemaining;
}

/**
 * @Name Get Job Name
 *
 * @details returns the string with the name of the job
 *          
 * @param N/A
 *
 * @ErrorsHandled: N/A
 */
string Job::getJobName()
{
	return jobName;
}

/**
 * @Name Set Cycles Remaining
 *
 * @details sets the number of cycles remaining to the inputted
 *			integer
 *          
 * @param in: integer representing the number of cycles remaining
 *
 * @ErrorsHandled: N/A
 */
void Job::setCyclesRemaining(int num)
{
	if( num > 0 )
	{
		cyclesRemaining = num;
	}
	else
	{
		cout << "Invalid number of cycles remaining" << endl;
	}
}
