// Program Information /////////////////////////////////////////////////////////
/**
 * @file processHandler.cpp
 *
 * @brief Implementation for the class that handles the functionality of creating 
 *		  and running a process
 * 
 * @details Implements the class created to take in the data configuration 
 *			and use it's information to simulate the OS managing a process 
 *			running on the computer	
 *
 * @author Matthew Cook
 *
 * @version 1.00 (15 September 16)
 * @version 1.01 (6 October 16)
 * @version 1.02 (8 November 16)
 * @version 1.03 (15 December 16)
 */

// HEADER FILES ////////////////////////////////////////////////////////////////

#include "processHandler.h"

// GLOBAL CONSTANTS ////////////////////////////////////////////////////////////

 // None

// Function definitions ////////////////////////////////////////////////////////

void * IOrunner( void * delay1 );

using namespace std;

/**
*@Name: Parameterized Constructor
*
*@Purpose: Construct data structure with values from config. file inputted
*
*@Param in: Name of config file (fileName)
*		out: N/A
*
*@Brief: calls function inputVarInfo to complete task
*					 using the inputted file name
*
*@ErrorsHandled: N/A
*/
processHandler::processHandler(const char* fileName)
{
	numOfProcesses = 0;
	pushProcess();
	nextProcess = 0;
	memoryUsed = 0;
	printersUsed = 0;
	hardDrivesUsed = 0;
	inputVarInfo( fileName );
}

/**
*@Name: Deconstructer
*
*@Purpose: Deconstructs data structure
*
*@Param: N/A
*
*@Brief: closes files opened by the class
*		 if still open. Deletes list of processes
*
*@ErrorsHandled: N/A
*/ 
processHandler::~processHandler()
{
	if( outputFile.is_open() )
    {
        outputFile.close();
    }
	if( metaFile.is_open() )
	{
		metaFile.close();
	}
	processList.clear();
}

/**
*@Name: Input Var Info
*
*@Purpose: Open the configuration file and go through each line until all the
*		   desired values are inputted to the correct private data members of
*		   the class
*
*@Param in: Name of config file (fileName)
*		out: N/A
*
*@Brief: Increments a integer to keep track of current line being used in
*		 the inputted file. It calls getline until the end of the file is 
*		 reached. Uses supporting function varSelector to use
*		 the information on the line correctly
*
*@ErrorsHandled: Checks to make sure the configuration file opens correctly
*/
void processHandler::inputVarInfo(const char* fileName)
{
	try
	{
		string lineInput;
		int lineNum = 1;
		ifstream configFile;
		configFile.open (fileName);
		if( !configFile.is_open() )
		{
			throw logic_error("Inputted config file does not exist or did not open properly");
		}
		while( lineNum <= 18)
		{
			getline(configFile, lineInput);
			varSelector( lineInput, lineNum);
			lineNum++;
		}
		configFile.close();
	}
	catch(exception &e)
	{
		cout << endl << e.what() << endl;
	}
}

/**
*@Name: Var Selector
*
*@Purpose: To use the current line number to decide what line is
*		   being looked at and it should be treated. 
*
*@Param in: String containing a line from the config file (lineInput)
*			Integer containing current line number looked at in config file (lineNum)
*		out: N/A
*
*@Brief: First it chooses a case based on line number. It does
*		 nothing in the case of the first and last lines since they
*		 do not contain config. data. Otherwise, it sets the private
*		 data member to the correct value that cooresponds with
*		 with the current line number. Relies on supporting function
*		 "configSplitter" to seperate parts of the line so it can isolate
*		 the data as it's own string and use atoi to convert it to a integer
*		 
*
*@ErrorsHandled: Throws an exception if there are spelling errors in config file,
*				  giving the line number to denote it.
*/
void processHandler::varSelector( string lineInput, int lineNum )
{
	string preData;
	string actualData;
	try
	{
		switch( lineNum )
		{
			case 1:
					if( lineInput.compare("Start Simulator Configuration File") != 0 )
					{
						throw logic_error("Spelling/Formatting error in config file on line ");
					}
					break;
			case 2:
					configSplitter(lineInput, preData, actualData);
					if( preData.compare("Version/Phase: ") != 0 )
					{
						throw logic_error("Spelling/Formatting error in config file on line ");
					}
					else
					{
						versionNum = atoi(actualData.c_str());
					}
					break;
			case 3:
					configSplitter(lineInput, preData, actualData);
					if( preData.compare("File Path: ") != 0 )
					{
						throw logic_error("Spelling/Formatting error in config file on line ");
					}
					else
					{
						metaFileName = actualData;
					}
					break;
			case 4:
					configSplitter(lineInput, preData, actualData);
					if( preData.compare("Processor Quantum Number: ") != 0 )
					{
						throw logic_error("Spelling/Formatting error in config file on line ");
					}
					else
					{
						quantumNum = atoi(actualData.c_str());
					}
					break;
			case 5:
					configSplitter(lineInput, preData, actualData);
					if( preData.compare("CPU Scheduling Code: ") != 0 )
					{
						throw logic_error("Spelling/Formatting error in config file on line ");
					}
					else
					{
						schedulingAlg = actualData;
					}
					break;
			case 6:
					configSplitter(lineInput, preData, actualData);
					if( preData.compare("Processor cycle time (msec): ") != 0 )
					{
						throw logic_error("Spelling/Formatting error in config file on line ");
					}
					else
					{
						processorSpeed = atoi(actualData.c_str());
					}
					break;
			case 7:
					configSplitter(lineInput, preData, actualData);
					if( preData.compare("Monitor display time (msec): ") != 0 )
					{
						throw logic_error("Spelling/Formatting error in config file on line ");
					}
					else
					{
						monitorSpeed = atoi(actualData.c_str());
					}
					break;
			case 8:
					configSplitter(lineInput, preData, actualData);
					if( preData.compare("Hard drive cycle time (msec): ") != 0 )
					{
						throw logic_error("Spelling/Formatting error in config file on line ");
					}
					else
					{
						hardSpeed = atoi(actualData.c_str());
					}
					break;
			case 9:
					configSplitter(lineInput, preData, actualData);
					if( preData.compare("Printer cycle time (msec): ") != 0 )
					{
						throw logic_error("Spelling/Formatting error in config file on line ");
					}
					else
					{
						printerSpeed = atoi(actualData.c_str());
					}
					break;
			case 10:
					configSplitter(lineInput, preData, actualData);
					if( preData.compare("Keyboard cycle time (msec): ") != 0 )
					{
						throw logic_error("Spelling/Formatting error in config file on line ");
					}
					else
					{
						keyboardSpeed = atoi(actualData.c_str());
					}
					break;
			case 11:
					configSplitter(lineInput, preData, actualData);
					if( preData.compare("Memory cycle time (msec): ") != 0 )
					{
						throw logic_error("Spelling/Formatting error in config file on line ");
					}
					else
					{
						memorySpeed = atoi(actualData.c_str());
					}
					break;
			case 12:
					configSplitter(lineInput, preData, actualData);
					if( preData.compare("System memory (kbytes): ") != 0 )
					{
						throw logic_error("Spelling/Formatting error in config file on line ");
					}
					else
					{
						systemMemory = atoi(actualData.c_str());
					}
					break;
			case 13:
					configSplitter(lineInput, preData, actualData);
					if( preData.compare("Memory block size (kbytes): ") != 0 )
					{
						throw logic_error("Spelling/Formatting error in config file on line ");
					}
					else
					{
						memBlockSize = atoi(actualData.c_str());
					}
					break;
			case 14:
					configSplitter(lineInput, preData, actualData);
					if( preData.compare("Printer quantity: ") != 0 )
					{
						throw logic_error("Spelling/Formatting error in config file on line ");
					}
					else
					{
						numOfPrinters = atoi(actualData.c_str());
					}
					break;
			case 15:
					configSplitter(lineInput, preData, actualData);
					if( preData.compare("Hard drive quantity: ") != 0 )
					{
						throw logic_error("Spelling/Formatting error in config file on line ");
					}
					else
					{
						numOfHDs = atoi(actualData.c_str());
					}
					break;
			case 16:
					configSplitter(lineInput, preData, actualData);
					if( preData.compare("Log: ") != 0 )
					{
						throw logic_error("Spelling/Formatting error in config file on line ");
					}
					else
					{
						logToWhere = actualData;
					}
					break;
			case 17:
					configSplitter(lineInput, preData, actualData);
					if( preData.compare("Log File Path: ") != 0 )
					{
						throw logic_error("Spelling/Formatting error in config file on line ");
					}
					else
					{
						logFilePath = actualData;
					}
					break;
			case 18:
					if( lineInput.compare("End Simulator Configuration File") != 0 )
					{
						throw logic_error("Spelling/Formatting error in config file on line ");
					}
					break;
			default:
					throw logic_error("Line does not exist --> ");
					break;
		}
	}
	catch(exception &e)
	{
		cout << endl << e.what() << lineNum << endl;
	}
}

/**
*@Name: Config Splitter
*
*@Purpose: To split the string containing the line from the config file 
*		   into two parts, one being the string up until the data needed
*		   (": ") and the other being after this (Meta-Data speeds, where
*		   to log to, etc.)
*
*@Param in: String containing the current line from the config file being split (lineInput)
*			String passed by reference to be set to the data up until ": " (preData)
*			String passed by reference to be set to the data needed after (actualData)
*		out: N/A
*
*@Brief: Finds the last ":" in the config file and uses that
*		 number as a pivot point to create two seperate substrings
*
*@ErrorsHandled: Throws a error if there is no colon in the line
*/ 
void processHandler::configSplitter( const string &lineInput, string &preData, string &actualData )
{
	try
	{
		int pivot = lineInput.find_last_of(':');
		if(pivot != string::npos)
		{
			preData = lineInput.substr( 0, pivot+2 );
			actualData = lineInput.substr( pivot+2, (lineInput.length() - 1));
		}
		else
		{
			throw logic_error("Spelling/Formatting error in current line");
		}
	}
	catch(exception &e)
	{
		cout << endl << e.what() << endl;
	}
}

/**
*@Name: Build Process List
*
*@Purpose: To use inputted meta data to build a list of processes
*
*@Param in: N/A
*		out: N/A
*
*@Brief: Function goes through desired meta-data file and uses the location 
*		 of semi-colons in each line to seperate each meta-data item individually. 
*		 Seperated data is used to determine what process it is in and whether or not
*		 it denotes a new process. 
*
*@ErrorHandled:	Throws a exception if there is no semi-colon in a line and
*				that line is not the first, last or a line with just 
*				a "S" command to turn off the OS
*
*@ErrorHandled: Throws a exception if the meta-data file or output file does not
*				open correctly
*
*/ 
void processHandler::buildProcessList()
{
	outputFile.open(logFilePath.c_str());
	metaFile.open (metaFileName.c_str());
	try
	{
		if( !outputFile.is_open() )
		{
			throw logic_error("Desired output file did not open properly");
		}
		if( !metaFile.is_open() )
		{
			throw logic_error("Desired meta-data file does not exist or didn't open properly");
		}
		string lineInput;
		string dataItem;
		int currentProcess = 1;
		int pivot;
		int pivot2;
		int result;
		while(lineInput.compare("End Program Meta-Data Code.") != 0)
		{
			getline(metaFile, lineInput);
			pivot = lineInput.find_first_of(';');
			pivot2 = 0;
			if(pivot == string::npos)
			{
				if( lineInput[lineInput.length()-2] == '0')
				{
					pivot = lineInput.length()-1;
					dataItem = lineInput.substr(pivot-7, pivot);
					processList[currentProcess-1].createJob(dataItem, currentProcess );
				}
				else if (lineInput.compare("Start Program Meta-Data Code:") != 0 && lineInput.compare("End Program Meta-Data Code.") != 0 )
				{
					cout << lineInput << endl;
					throw logic_error("Invalid line in the inputted Meta-Data file");
				}
			}
			else
			{
				while( pivot != string::npos )
				{	
					if( currentProcess > numOfProcesses ) 
					{
						pushProcess();
					}
					dataItem = lineInput.substr(pivot2, (pivot-pivot2));
					currentProcess = processList[currentProcess-1].createJob(dataItem, currentProcess );
					pivot2 = pivot+2;
					pivot = lineInput.find_first_of(';', pivot+1);
				}
				if( lineInput[lineInput.length()-1] == '.')
				{
					pivot = lineInput.length()-1;
					dataItem = lineInput.substr(pivot-7, pivot);
					processList[currentProcess-1].createJob(dataItem, currentProcess);
				}
			}
		}
	}
	catch( exception &e )
	{
		cout << endl << e.what() << endl;
		metaFile.close();
		outputFile.close();	
	}
}

/**
*@Name: Calculate Burst Time
*
*@Purpose: To calculate the total burst time needed on the CPU for each
*		   process in the application
*
*@Param N/A
*
*@Brief: Loops through the list of processes and calculates the total burst time
*		 for each process by adding up the burst time for each individual job in
*		 list that needs CPU time (Memory or Process).
*
*@ErrorHandled:	N/A
*
*/ 
void processHandler::calculateBurstTime()
{
	int totalBurst;
	char tempType;
	int tempCycles = 0;
	string tempName;
	for( int i = 0; i < numOfProcesses; i++ )
	{
	 	totalBurst = 0;
		for( int j = 0; j < processList[i].getNumOfJobs(); j++ )
		{
			tempType = processList[i].getJob(j).getType();
			tempCycles = processList[i].getJob(j).getCyclesRemaining();
			tempName = processList[i].getJob(j).getJobName();
			switch(tempType)
			{
				case 'P':
							if( tempName.compare("(run)") == 0)
							{
								totalBurst = totalBurst + tempCycles*processorSpeed;
							}
								break;
				case 'M':
							if( tempName.compare("(cache)") == 0)
							{
								totalBurst = totalBurst + tempCycles*memorySpeed;
							}
								break;
							if( tempName.compare("(allocate)") == 0)
							{
								totalBurst = totalBurst + tempCycles*memorySpeed;
							}
								break;
			}
		}
		processList[i].setRemainingBurstTime(totalBurst);
	}
}

/**
*@Name: Schedule Processes
*
*@Purpose: returns a integer representing the index of next process that should be
*		   scheduled to run based on the algorithm in the inputted config file
*
*@Param N/A
*
*@Brief: The function implements three different scheduling algorithms: SJF, RR, and STRF.
*		 SJF uses the burst time that is calculated in the main function while STRF updates
*		 the remaining burst time everytime a quantum finishes
*
*@ErrorHandled:	N/A
*
*/
int processHandler::scheduleProcesses()
{
	if(numOfProcesses == 0)
	{
		return -1;
		cout << "No More Processes" << endl;
	}

	int tempProcessNum;
	int tempBurst;
	if( schedulingAlg.compare("SJF") == 0)
	{
		tempBurst = processList[0].getRemainingBurstTime();
		tempProcessNum = 0;
		for( int i = 0; i < numOfProcesses; i++ )
		{
			if( processList[i].getRemainingBurstTime() < tempBurst )
			{
				tempBurst = processList[i].getRemainingBurstTime();
				tempProcessNum = i;
			}
		}
		return tempProcessNum;
	}
	else if ( schedulingAlg.compare("RR") == 0 )
	{
		if( nextProcess < numOfProcesses && nextProcess >= 0 )
		{
			tempProcessNum = nextProcess;
			nextProcess++;
			return tempProcessNum;			
		}
		else if ( nextProcess == numOfProcesses )
		{
			tempProcessNum = 0;
			nextProcess = 1;
			return tempProcessNum;
		}
	}
	else if( schedulingAlg.compare("STRF") == 0)
	{
		calculateBurstTime();
		tempBurst = processList[0].getRemainingBurstTime();
		tempProcessNum = 0;
		for( int i = 0; i < numOfProcesses; i++ )
		{
			if( processList[i].getRemainingBurstTime() < tempBurst )
			{
				tempBurst = processList[i].getRemainingBurstTime();
				tempProcessNum = i;
			}
		}
		return tempProcessNum;
	}
}

/**
*@Name: Run Quantum
*
*@Purpose: Handles running the scheduled process for the given quantum length
*		   of cycles
*
*@Param: in: integer representing current process that is scheduled
*
*@Brief: The current process runs for the given number of quantums and delays
* 		 the program appropriately to simulate running jobs within a process. The function
*		 interrupts processing jobs if they have cycles remaining after the quantum is over.
*		 I/O operations are threaded and use mutex locks to ensure that they are not accessed
*		 while in use. Memory operations are not interruptable. The process is removed from the
*		 list of processes at the end of the function if it has no more jobs to complete.
*
*@ErrorsHandled: N/A
*/
void processHandler::runQuantum( int processNum )
{
	char startTime[10];
	timer1.getCurrentTime(startTime);
	char tempType;
	int tempCycles;
	int cycles = quantumNum;
	string tempName;
	int currentJob = 0;
	int numOfJobs = processList[processNum].getNumOfJobs();
	int jobTime[1];
	pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
	pthread_t tid;
	pthread_attr_t attr;
	timer1.getCurrentTime(currentTime);
	processList[processNum].setState("Ready");
	if( logToWhere.compare("Log to Monitor") == 0)
	{
		cout << startTime << " - OS: preparing process " << processList[processNum].getProcessNum() << endl;
		cout << currentTime << " - OS: starting process " << processList[processNum].getProcessNum() << endl;
	}
	else if(logToWhere.compare("Log to File") == 0)
	{
		outputFile << startTime << " - OS: preparing process " << processList[processNum].getProcessNum() << endl;
		outputFile << currentTime << " - OS: starting process " << processList[processNum].getProcessNum() << endl;
	}
	else if(logToWhere.compare("Log to Both") == 0)
	{
		cout << startTime << " - OS: preparing process " << processList[processNum].getProcessNum() << endl;
		cout << currentTime << " - OS: starting process " << processList[processNum].getProcessNum() << endl;
		outputFile << startTime << " - OS: preparing process " << processList[processNum].getProcessNum() << endl;
		outputFile << currentTime << " - OS: starting process " << processList[processNum].getProcessNum() << endl;
	}
	while( cycles > 0 && numOfJobs != 0)
	{
		tempType = processList[processNum].getJob(currentJob).getType();
		tempCycles = processList[processNum].getJob(currentJob).getCyclesRemaining();
		tempName = processList[processNum].getJob(currentJob).getJobName();
		switch( tempType )
		{
			case 'P':
						timer1.getCurrentTime(startTime);
						processList[processNum].setState("Running");
						if( logToWhere.compare("Log to Monitor") == 0)
						{
							cout << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start processing action" << endl;
						}
						else if(logToWhere.compare("Log to File") == 0)
						{
							outputFile << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start processing action" << endl;
	
						}
						else if(logToWhere.compare("Log to Both") == 0)
						{
							cout << startTime << " - Process " << processList[processNum].getProcessNum() << ": start processing action" << endl;
							outputFile << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start processing action" << endl;
						}
						while( cycles > 0 && tempCycles > 0 )
						{
							timer1.delay(processorSpeed);
							cycles--;
							tempCycles--;
						}
						timer1.getCurrentTime(currentTime);
						if( tempCycles == 0 )
						{
							if( logToWhere.compare("Log to Monitor") == 0)
							{
								cout << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end processing action" << endl;
							}
							else if(logToWhere.compare("Log to File") == 0)
							{
								outputFile << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end processing action" << endl;
	
							}
							else if(logToWhere.compare("Log to Both") == 0)
							{
								cout << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end processing action" << endl;
								outputFile << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end processing action" << endl;
							}
							processList[processNum].finishedJob(currentJob);
							numOfJobs--;
							break;
						}
						else
						{
							if( logToWhere.compare("Log to Monitor") == 0)
							{
								cout << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": interrupt processing action" << endl;
							}
							else if(logToWhere.compare("Log to File") == 0)
							{
								outputFile << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": interrupt processing action" << endl;
	
							}
							else if(logToWhere.compare("Log to Both") == 0)
							{
								cout << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": interrupt processing action" << endl;
								outputFile << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": interrupt processing action" << endl;
							}
							processList[processNum].getJob(currentJob).setCyclesRemaining(tempCycles);
							break;
						}
						break;
			case 'I':
						timer1.getCurrentTime(startTime);
						processList[processNum].setState("Waiting");
						if( tempName.compare("(hard drive)") == 0)
						{
							if( hardDrivesUsed < numOfHDs )
							{
								hardDrivesUsed++;
							}
							else if( hardDrivesUsed == numOfHDs )
							{
								while( hardDrivesUsed == numOfHDs )
								{
									//Nothing
								}
							}
							if( logToWhere.compare("Log to Monitor") == 0)
							{
								cout << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start hard drive input" << endl;
							}
							else if(logToWhere.compare("Log to File") == 0)
							{
								outputFile << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start hard drive input" << endl;
	
							}
							else if(logToWhere.compare("Log to Both") == 0)
							{
								cout << startTime << " - Process " << processList[processNum].getProcessNum() << ": start hard drive input" << endl;
								outputFile << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start hard drive input" << endl;
							}
							pthread_mutex_lock(&mutex1);
							jobTime[0] = tempCycles*hardSpeed;
							pthread_attr_init(&attr);
							pthread_create(&tid, &attr, IOrunner, jobTime);
							pthread_join(tid, NULL);
							processList[processNum].finishedJob(currentJob);
							numOfJobs--;
							hardDrivesUsed--;
							timer1.getCurrentTime(currentTime);
							pthread_mutex_unlock(&mutex1);
							if( logToWhere.compare("Log to Monitor") == 0)
							{
								cout << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end hard drive input" << endl;
							}
							else if(logToWhere.compare("Log to File") == 0)
							{
								outputFile << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end hard drive input" << endl;
	
							}
							else if(logToWhere.compare("Log to Both") == 0)
							{
								cout << currentTime << " - Process " << processList[processNum].getProcessNum() << ": end hard drive input" << endl;
								outputFile << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end hard drive input" << endl;
							}
						}
						if( tempName.compare("(keyboard)") == 0 )
						{
							if( logToWhere.compare("Log to Monitor") == 0)
							{
								cout << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start keyboard input" << endl;
							}
							else if(logToWhere.compare("Log to File") == 0)
							{
								outputFile << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start keyboard input" << endl;
	
							}
							else if(logToWhere.compare("Log to Both") == 0)
							{
								cout << startTime << " - Process " << processList[processNum].getProcessNum() << ": start keyboard input" << endl;
								outputFile << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start keyboard input" << endl;
							}
							pthread_mutex_lock(&mutex1);
							jobTime[0] = tempCycles*keyboardSpeed;
							pthread_attr_init(&attr);
							pthread_create(&tid, &attr, IOrunner, jobTime);
							pthread_join(tid, NULL);
							processList[processNum].finishedJob(currentJob);
							numOfJobs--;
							timer1.getCurrentTime(currentTime);
							pthread_mutex_unlock(&mutex1);
							if( logToWhere.compare("Log to Monitor") == 0)
							{
								cout << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end keyboard input" << endl;
							}
							else if(logToWhere.compare("Log to File") == 0)
							{
								outputFile << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end keyboard input" << endl;
	
							}
							else if(logToWhere.compare("Log to Both") == 0)
							{
								cout << currentTime << " - Process " << processList[processNum].getProcessNum() << ": end keyboard input" << endl;
								outputFile << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end keyboard input" << endl;
							}
						}
						processList[processNum].setState("Ready");
						break;
			case 'O':
						timer1.getCurrentTime(startTime);
						if( tempName.compare("(hard drive)") == 0 )
						{
							if( hardDrivesUsed < numOfHDs )
							{
								hardDrivesUsed++;
							}
							else if( hardDrivesUsed == numOfHDs )
							{
								while( hardDrivesUsed == numOfHDs )
								{
									//Nothing
								}
							}
							if( logToWhere.compare("Log to Monitor") == 0)
							{
								cout << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start hard drive output" << endl;
							}
							else if(logToWhere.compare("Log to File") == 0)
							{
								outputFile << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start hard drive output" << endl;
	
							}
							else if(logToWhere.compare("Log to Both") == 0)
							{
								cout << startTime << " - Process " << processList[processNum].getProcessNum() << ": start hard drive output" << endl;
								outputFile << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start hard drive output" << endl;
							}
							pthread_mutex_lock(&mutex1);
							jobTime[0] = tempCycles*hardSpeed;
							pthread_attr_init(&attr);
							pthread_create(&tid, &attr, IOrunner, jobTime);
							pthread_join(tid, NULL);
							processList[processNum].finishedJob(currentJob);
							numOfJobs--;
							timer1.getCurrentTime(currentTime);
							hardDrivesUsed--;
							pthread_mutex_unlock(&mutex1);
							if( logToWhere.compare("Log to Monitor") == 0)
							{
								cout << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end hard drive output" << endl;
							}
							else if(logToWhere.compare("Log to File") == 0)
							{
								outputFile << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end hard drive output" << endl;
	
							}
							else if(logToWhere.compare("Log to Both") == 0)
							{
								cout << currentTime << " - Process " << processList[processNum].getProcessNum() << ": end hard drive output" << endl;
								outputFile << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end hard drive output" << endl;
							}
						}
						if( tempName.compare("(printer)") == 0)
						{
							if( logToWhere.compare("Log to Monitor") == 0)
							{
								cout << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start printer output" << endl;
							}
							else if(logToWhere.compare("Log to File") == 0)
							{
								outputFile << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start printer output" << endl;
	
							}
							else if(logToWhere.compare("Log to Both") == 0)
							{
								cout << startTime << " - Process " << processList[processNum].getProcessNum() << ": start printer output" << endl;
								outputFile << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start printer output" << endl;
							}
							pthread_mutex_lock(&mutex1);
							jobTime[0] = tempCycles*printerSpeed;
							pthread_attr_init(&attr);
							pthread_create(&tid, &attr, IOrunner, jobTime);
							pthread_join(tid, NULL);
							processList[processNum].finishedJob(currentJob);
							numOfJobs--;
							timer1.getCurrentTime(currentTime);
							pthread_mutex_unlock(&mutex1);
							if( logToWhere.compare("Log to Monitor") == 0)
							{
								cout << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end printer output" << endl;
							}
							else if(logToWhere.compare("Log to File") == 0)
							{
								outputFile << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end printer output" << endl;
	
							}
							else if(logToWhere.compare("Log to Both") == 0)
							{
								cout << currentTime << " - Process " << processList[processNum].getProcessNum() << ": end printer output" << endl;
								outputFile << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end printer output" << endl;
							}
						}
						if( tempName.compare("(monitor)") == 0)
						{
							if( logToWhere.compare("Log to Monitor") == 0)
							{
								cout << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start monitor output" << endl;
							}
							else if(logToWhere.compare("Log to File") == 0)
							{
								outputFile << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start monitor output" << endl;
	
							}
							else if(logToWhere.compare("Log to Both") == 0)
							{
								cout << startTime << " - Process " << processList[processNum].getProcessNum() << ": start monitor output" << endl;
								outputFile << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start monitor output" << endl;
							}
							pthread_mutex_lock(&mutex1);
							jobTime[0] = tempCycles*monitorSpeed;
							pthread_attr_init(&attr);
							pthread_create(&tid, &attr, IOrunner, jobTime);
							pthread_join(tid, NULL);
							processList[processNum].finishedJob(currentJob);
							numOfJobs--;
							timer1.getCurrentTime(currentTime);
							pthread_mutex_unlock(&mutex1);
							if( logToWhere.compare("Log to Monitor") == 0)
							{
								cout << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end monitor output" << endl;
							}
							else if(logToWhere.compare("Log to File") == 0)
							{
								outputFile << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end monitor output" << endl;
	
							}
							else if(logToWhere.compare("Log to Both") == 0)
							{
								cout << currentTime << " - Process " << processList[processNum].getProcessNum() << ": end monitor output" << endl;
								outputFile << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end monitor output" << endl;
							}
						}
						processList[processNum].setState("Ready");
						break;
			case 'M':
						timer1.getCurrentTime(startTime);
						if( tempName.compare("(allocate)") == 0 )
						{
							if( logToWhere.compare("Log to Monitor") == 0)
							{
								cout << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": allocating memory" << endl;
							}
							else if(logToWhere.compare("Log to File") == 0)
							{
								outputFile << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": allocating memory" << endl;
	
							}
							else if(logToWhere.compare("Log to Both") == 0)
							{
								cout << startTime << " - Process " << processList[processNum].getProcessNum() << ": allocating memory" << endl;
								outputFile << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": allocating memory" << endl;
							}
							processList[processNum].setState("Running");
							char hexAddress[8];
							int threshold;
							timer1.delay(tempCycles*memorySpeed);
							AllocateMemory();
							intToHex((memoryUsed - memBlockSize), hexAddress, threshold);
							processList[processNum].finishedJob(currentJob);
							numOfJobs--;
							timer1.getCurrentTime(currentTime);
							if( logToWhere.compare("Log to Monitor") == 0)
							{
								cout << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": memory allocated at 0x";
								for(int i = 8; i > 0; i--)
								{
									if( i > (threshold - 1 ) )
									{
										cout << '0';
									}
									else
									{
										cout << hexAddress[i];
									}
								}
								cout << endl;
							}
							else if(logToWhere.compare("Log to File") == 0)
							{
								outputFile << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": memory allocated at 0x";
								for(int i = 8; i > 0; i--)
								{
									if( i > (threshold - 1 ) )
									{
										outputFile << '0';
									}
									else
									{
										outputFile << hexAddress[i];
									}
								}
								outputFile << endl;
	
							}
							else if(logToWhere.compare("Log to Both") == 0)
							{
								cout << currentTime << " - Process " << processList[processNum].getProcessNum() << ": memory allocated at 0x";
								outputFile << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": memory allocated at 0x";
								for(int i = 8; i > 0; i--)
								{
									if( i > (threshold - 1 ) )
									{
										cout << '0';
										outputFile << '0';
									}
									else
									{
										cout << hexAddress[i];
										outputFile << hexAddress[i];
									}
								}
								cout << endl;
								outputFile << endl;
							}
						}
						if( tempName.compare("(cache)") == 0 )
						{
							if( logToWhere.compare("Log to Monitor") == 0)
							{
								cout << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start memory caching" << endl;
							}
							else if(logToWhere.compare("Log to File") == 0)
							{
								outputFile << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start memory caching" << endl;
	
							}
							else if(logToWhere.compare("Log to Both") == 0)
							{
								cout << startTime << " - Process " << processList[processNum].getProcessNum() << ": start memory caching" << endl;
								outputFile << startTime << " - Process " << processList[processNum].getProcessNum() <<  ": start memory caching" << endl;
							}
							timer1.delay(tempCycles*memorySpeed);
							memoryCache(processNum, currentJob );
							processList[processNum].finishedJob(currentJob);
							numOfJobs--;
							timer1.getCurrentTime(currentTime);
							if( logToWhere.compare("Log to Monitor") == 0)
							{
								cout << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end memory caching" << endl;
							}
							else if(logToWhere.compare("Log to File") == 0)
							{
								outputFile << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end memory caching" << endl;
	
							}
							else if(logToWhere.compare("Log to Both") == 0)
							{
								cout << currentTime << " - Process " << processList[processNum].getProcessNum() << ": end memory caching" << endl;
								outputFile << currentTime << " - Process " << processList[processNum].getProcessNum() <<  ": end memory caching" << endl;
							}
						}

						break;
		}
	}
	timer1.getCurrentTime(startTime);
	if( numOfJobs == 0 )
	{
		if( logToWhere.compare("Log to Monitor") == 0)
		{
			cout << startTime << " - OS: removing process " << processList[processNum].getProcessNum() << endl;
		}
		else if(logToWhere.compare("Log to File") == 0)
		{
			outputFile << startTime << " - OS: removing process " << processList[processNum].getProcessNum() << endl;
		}
		else if(logToWhere.compare("Log to Both") == 0)
		{
			cout << startTime << " - OS: removing process " << processList[processNum].getProcessNum() << endl;
			outputFile << startTime << " - OS: removing process " << processList[processNum].getProcessNum() << endl;
		}
		removeProcess(processNum);
	}

}

/**
*@Name: Memory Cache
*
*@Purpose: simulates having memory cached during a process
*
*@Param: N/A
*
*@Brief: All processing jobs have their cycles reduced by 2 if
*		 its remaining cycles is greater than 2
*
*@ErrorsHandled: N/A
*/
void processHandler::memoryCache(int processNum, int jobNum )
{
	int tempCycles;
	char tempCode;
	for( int i = jobNum; i < processList[processNum].getNumOfJobs(); i++ )
	{	
		tempCode = processList[processNum].getJob(i).getType();
		tempCycles = processList[processNum].getJob(i).getCyclesRemaining();
		if( tempCycles > 2 && tempCode == 'P' )
		{
			processList[processNum].getJob(i).cacheMemory();
		}
	}
}

/**
*@Name: Remove Process
*
*@Purpose: erases the process at the given index in the
*		   process list
*
*@Param: N/A
*
*@Brief: N/A
*
*@ErrorsHandled: N/A
*/
void processHandler::removeProcess(int num)
{
	processList.erase(processList.begin() + num);
	numOfProcesses--;
}

/**
*@Name: Allocate Memory
*
*@Purpose: To allocate memory equal to one block size
*
*@Param: N/A
*
*@Brief: The function checks to see if there is room for another block
*		 of memory and, if so, increases the memory used by the system
*		 by one block; this effect simulates allocating memory. The
*		 function starts over and allocates from zero once memoryUsed
*		 would exceed system memory when another block is allocated
*
*@ErrorsHandled: Throws an exception if the memory currently used
*				 is greater than the system memory capacity
*/ 
void processHandler::AllocateMemory()
{
	try
	{
		if( (memoryUsed + memBlockSize) < systemMemory )
		{
			memoryUsed = memoryUsed + memBlockSize;
		}
		else if( memoryUsed > systemMemory )
		{
			throw logic_error("Memory used currently exceeds maximum system memory capacity, error");
		}
		else
		{
			memoryUsed = memBlockSize;
		}
	}
	catch( exception &e )
	{
		cout << endl << e.what() << endl;
	}
	
}

/**
*@Name: Push Process
*
*@Purpose: adds a new process to the list of processes and increments
*		   the current number of processes 
*
*@Param: N/A
*
*@Brief: N/A
*
*@ErrorsHandled: N/A
*/
void processHandler::pushProcess( )
{
	numOfProcesses++;
	processList.push_back(PCB(numOfProcesses));
}

/**
*@Name: Show Processes
*
*@Purpose: prints out information for each process in the process list
*
*@Param: N/A
*
*@Brief: N/A
*
*@ErrorsHandled: N/A
*/
void processHandler::showProcesses()
{
	for(int i = 0; i < numOfProcesses; i++ )
	{
		cout << "Process " << (i+1) << endl;
		for( int j = 0; j < processList[i].getNumOfJobs(); j++ )
		{
			cout << "Job Number " << (j+1) << " is: " << processList[i].getJob(j).getType() << processList[i].getJob(j).getJobName() <<  processList[i].getJob(j).getCyclesRemaining() << endl;
		}
		cout << endl;
	}
}

/**
*@Name: Get Number of Processes
*
*@Purpose: returns the current number of processes
*
*@Param N/A
*
*@Brief: N/A
*
*@ErrorsHandled: N/A
*/
int processHandler::getNumOfProcesses()
{
	return numOfProcesses;
}

/**
*@Name: I/O Runner
*
*@Purpose: To delay the program for the time inputted 
*
*@Param in: array containing the number of milliseconds
*			to delay the program
*
*@Brief: This function allows the I/O thread to delay the program
*		 and then close itself
*
*@ErrorsHandled: N/A
*/ 
void * IOrunner( void * delay1 )
{
	SimpleTimer IOtimer;
	IOtimer.delay((*((int *) delay1)));
	pthread_exit(NULL);
}
