// Program Information /////////////////////////////////////////////////////////
/**
 * @file SimpleTimer.cpp
 *
 * @brief Implementation for the class that is designed as a easy-to-use timer
 * 
 * @details This file includes the implementation of the "SimpleTimer" class, 
 *			which has all the functionality to track time as well as delay a 
 *			program for a given number of milliseconds
 *	
 * @author Michael Leverington
 *
 * @version 1.00 (Fall Semester 2015)
 */

// HEADER FILES ////////////////////////////////////////////////////////////////

#include "SimpleTimer.h"

// GLOBAL CONSTANTS ////////////////////////////////////////////////////////////

// None


/**
 * @brief Default constructor
 *
 * @details Constructs Timer class
 *          
 * @param None
 *
 * @note set running flag to false
 */
SimpleTimer::SimpleTimer
       (
        // no parameters
       )
   {
    running = false;
   }

/**
 * @brief Default constructor
 *
 * @details Destructs Timer class
 *          
 * @param None
 *
 * @note No data to clear
 */
SimpleTimer::~SimpleTimer
       (
        // no parameters
       )
   {
    // no action here 
   }

/**
 * @brief Start control
 *
 * @details Takes initial time data
 *          
 * @param None
 *
 * @note None
 */
void SimpleTimer::start
       (
        // no parameters
       )
   {
    gettimeofday( &startData, NULL );

    running = true;

    dataGood = false;
   }

/**
 * @brief Stop control
 *
 * @details Takes final time data, calculates duration
 *          
 * @param None
 *
 * @note None
 */
void SimpleTimer::stop
       (
        // no parameters
       )
   {
    if( running )
       {
        gettimeofday( &endData, NULL );

        running = false;

        dataGood = true;
       }

    else
       {
        dataGood = false;
       }
   }

/**
 * @brief Get Elapsed Time
 *
 * @details Subtracts the starting time of the timer
 * 			from it's stopping time and converts that
 * 			value to milliseconds; This value is stored
 *			in the memory pointed to by "timeStr"
 *          
 * @param pointer to a char to store the time elapsed
 *
 * @note value stored in timeStr is "No Data" if data is bad
 */
void SimpleTimer::getElapsedTime
       (
        char *timeStr
       )
   {
    int low, high, index = 0;
    char temp;

    if( dataGood )
       {
        secTime = endData.tv_sec - startData.tv_sec;
        microSecTime = endData.tv_usec - startData.tv_usec;

        if( microSecTime < 0 )
           {
            microSecTime += 1000000;

            secTime -= 1;
           }

        while( microSecTime > 0 )
           {
            timeStr[ index ] = char( microSecTime % 10 + '0' );

            microSecTime /= 10;
    
            index++;
           }

        while( index < 6 )
           {
            timeStr[ index ] = '0';

            index++;
           }

        timeStr[ index ] = RADIX_POINT;

        index++;

        if( secTime == 0 )
           {
            timeStr[ index ] = '0';
    
            index++;
           }

        while( secTime > 0 )
           {
            timeStr[ index ] = char( secTime % 10 + '0' );

            secTime /= 10;

            index++;
           }

        timeStr[ index ] = NULL_CHAR;

        low = 0; high = index - 1;

        while( low < high )
           {
            temp = timeStr[ low ];
            timeStr[ low ] = timeStr[ high ];
            timeStr[ high ] = temp;

            low++; high--;
           }
       }

    else
       {
        strcpy( timeStr, "No Data" );
       }
   }

/**
 * @brief Get Current Time
 *
 * @details finds the current time and subtracts the starting
 *			time of the timer from it and converts that
 * 			value to milliseconds; This value is stored
 *			in the memory pointed to by "timeStr"
 *          
 * @param pointer to a char to store the current time found
 *
 * @note
 */
void SimpleTimer::getCurrentTime
       (
        char *timeStr
       )
   {
    int low, high, index = 0;
    char temp;

    gettimeofday( &midData, NULL );

        secTime = midData.tv_sec - startData.tv_sec;
        microSecTime = midData.tv_usec - startData.tv_usec;

        if( microSecTime < 0 )
           {
            microSecTime += 1000000;

            secTime -= 1;
           }

        while( microSecTime > 0 )
           {
            timeStr[ index ] = char( microSecTime % 10 + '0' );

            microSecTime /= 10;
    
            index++;
           }

        while( index < 6 )
           {
            timeStr[ index ] = '0';

            index++;
           }

        timeStr[ index ] = RADIX_POINT;

        index++;

        if( secTime == 0 )
           {
            timeStr[ index ] = '0';
    
            index++;
           }

        while( secTime > 0 )
           {
            timeStr[ index ] = char( secTime % 10 + '0' );

            secTime /= 10;

            index++;
           }

        timeStr[ index ] = NULL_CHAR;

        low = 0; high = index - 1;

        while( low < high )
           {
            temp = timeStr[ low ];
            timeStr[ low ] = timeStr[ high ];
            timeStr[ high ] = temp;

            low++; high--;
           }

   }


/**
 * @brief Get Current Time
 *
 * @details finds the current time and subtracts the starting
 *			time of the timer from it and converts that
 * 			value to milliseconds; This value is stored
 *			in the memory pointed to by "timeStr"
 *          
 * @param pointer to a char to store the current time found
 *
 * @note
 */
void SimpleTimer::delay( int time )
   {
    long int waitTime;
    long int secondWait;
    int index = 0;

    gettimeofday( &delayData, NULL );

    waitTime = ( delayData.tv_usec + ( time ) * 1000 );

    while( waitTime > 1000000 )
       {
        waitTime -= 1000000;
        index++;
       }

    secondWait = index + delayData.tv_sec;

    while( delayData.tv_sec < secondWait )
       {
        gettimeofday( &delayData, NULL );
       }

    while( delayData.tv_usec < waitTime )
       {
        gettimeofday( &delayData, NULL );
       }

   }
