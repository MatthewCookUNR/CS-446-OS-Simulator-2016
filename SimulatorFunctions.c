// Program Information /////////////////////////////////////////////////////////
/**
 * @file SimulatorFunctions.c
 *
 * @brief Integer to Hexadecimal Implementation for Assignment 3
 * 
 * @details This file includes the function implementation for the integer
 *			to hexadecimal conversion.
 *
 * @author Cayler Miley & Matthew Cook
 *
 * @version 1.01 (14 September 16)
 * @version 1.02 (8 November 16)
 */

// HEADER FILES ////////////////////////////////////////////////////////////////

#include "SimulatorFunctions.h"

// GLOBAL CONSTANTS ////////////////////////////////////////////////////////////

 //None

/**
*@Name: Integer to Hexadecimal conversion Function
*
*@Purpose: To convert a unsigned integer value to a hexadecimal one
*
*@Param in: unsigned integer value to be converted to hexadecimal
*@Param out: character array to store the hexadecimal conversion
*@Param out: integer to keep track of how many digits the hexadecimal
*			 form of value is
*
*@Brief: takes in a unsigned integer value and converts it into
*		 hexadecimal form. The hexadecimal value is stored in the
*		 form of a character array. Threshold determines how many
*		 digits the hexadecimal number is after converted.
*
*@ErrorsHandled: Throws an exception if the threshold is a invalid
*				 number
*/
void intToHex( unsigned int value, char * hexNum, int &threshold)
{
	try
	{
		int temp;
		threshold = 1;
		while(value != 0)
		{
		  	temp = value % 16;
		  	if( temp < 10)
			{
		    	temp = temp + 48;
			}
		  	else
			{
		     	temp = temp + 55;
			}
		  	hexNum[threshold++]= temp;
		  	value = value / 16;
		}
		if( threshold  < 1 || threshold > 7 )
		{
			throw logic_error("Threshold for integer to hexadecimal is invalid");
		}
	}
	catch( exception &e )
	{
		cout << endl << e.what() << endl;
	}
}
