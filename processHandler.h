// Program Information /////////////////////////////////////////////////////////
/**
 * @file processHandler.h
 *
 * @brief Class that handles the functionality of creating and running a process
 * 
 * @details This file includes the class created to take in the data 
 *			configuration and use it's information to simulate the OS managing
 *			a process running on the computer		
 *
 * @author Matthew Cook
 *
 * @version 1.00 (15 September 16)
 * @version 1.01 (6 October 16)
 * @version 1.02 (8 November 16)
 * @version 1.03 (15 December 16)
 */

// HEADER FILES ////////////////////////////////////////////////////////////////

#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <ios>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "SimpleTimer.h"
#include "process.h"
#include "SimulatorFunctions.h"

// GLOBAL CONSTANTS ////////////////////////////////////////////////////////////

// None

using namespace std;

class processHandler
{
	public:
		processHandler(const char* fileName);
		~processHandler();
		void configSplitter( const string &input, string &preData, string &data );
		void metaSplitter( const string& input, string &dataCode, string &cycleNum, char &code);
		void varSelector( string lineInput, int lineNum );
		void inputVarInfo(const char* fileName);
		void buildProcessList();
		int scheduleProcesses();
		void runQuantum( int processNum );
		void pushProcess( );
		void AllocateMemory();
		void showProcesses();
		void calculateBurstTime();
		void memoryCache( int processNum, int jobNum);
		SimpleTimer timer1;
		char currentTime[10];
		void addPrinterInUse();
		void addHDInUse();
		void removePrinterInUse();
		void removeHDInUse();
		int getPrintersUsed();
		int getHDUsed();
		int getNumOfPrinters();
		int getNumOfHDs();
		int getNumOfProcesses();
		void removeProcess(int num);


		ofstream outputFile;
		ifstream metaFile;
	private:
		vector<PCB> processList;
		int versionNum;
		int processorSpeed;
		int monitorSpeed;
		int hardSpeed;
		int printerSpeed;
		int keyboardSpeed;
		int memorySpeed;
		int systemMemory;
		unsigned int memoryUsed;
		int printersUsed;
		int hardDrivesUsed;
		int numOfPrinters;
		int numOfHDs;
		int memBlockSize;
		int numOfProcesses;
		int quantumNum;
		int nextProcess;
		string schedulingAlg;
		string logToWhere;
		string logFilePath;
		string metaFileName;
};


