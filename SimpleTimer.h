// Program Information /////////////////////////////////////////////////////////
/**
 * @file SimpleTimer.h
 *
 * @brief Class that is designed as a easy-to-use timer
 * 
 * @details This file includes the "SimpleTimer" class, which has all the
 *			functionality to track time as well as delay a program for a
 *			given number of milliseconds
 *	
 * @author Michael Leverington
 *
 * @version 1.00 (Fall Semester 2015)
 */

// HEADER FILES ////////////////////////////////////////////////////////////////

#include <cstring>
#include <sys/time.h>

// GLOBAL CONSTANTS ////////////////////////////////////////////////////////////

// None

// Class definition  //////////////////////////////////////////////////////////

class SimpleTimer 
   {
    public:

       // constant
       static const char NULL_CHAR = '\0';
       static const char RADIX_POINT = '.';

       // Constructor
       SimpleTimer();

       // Destructor
       ~SimpleTimer();
    
       // accessors
       void start(); 
       void stop(); 
       void getElapsedTime( char *timeStr );
       void getCurrentTime( char *timeStr );
       void delay( int time );

    private:
       struct timeval startData, endData, midData, delayData;
       long int beginTime, endTime;
       long int secTime, microSecTime;
       bool running, dataGood;
   };


