/**
 * This class is used to store and retrieve the distance between various locations 
 * A route is assumed to be bidirectional. i.e., a route from CityA to CityB is 
 * same as a route from CityB to CityA. Furthermore, there can be no more than 
 * one route between two locations. Deleting a route is not supported at this point.
 * The storage limit for this version is 10 routes.
 * In the case more than multiple routes between the same two locations were entered,
 * we store only the latest one. The command format is given by the example interaction below:

 Welcome to SimpleRouteStore!
 Enter command:addroute Clementi BuonaVista 12
 Route from Clementi to BuonaVista with distance 12km added
 Enter command:getdistance Clementi BuonaVista
 Distance from Clementi to BuonaVista is 12
 Enter command:getdistance clementi buonavista
 Distance from clementi to buonavista is 12
 Enter command:getdistance Clementi JurongWest
 No route exists from Clementi to JurongWest!
 Enter command:addroute Clementi JurongWest 24
 Route from Clementi to JurongWest with distance 24km added
 Enter command:getdistance Clementi JurongWest
 Distance from Clementi to JurongWest is 24
 Enter command:exit

 * @author Dave Jun
 * @author Loke Yan Hao (Convert to C++)
 * @author Onn Wei Cheng (Replaced exception handling code)
 */

/*
 * ==============NOTE TO STUDENTS======================================
 * This class is not written in pure Object-Oriented fashion. That is 
 * because we haven't covered OO theory yet. Yes, it is possible to 
 * write non-OO code using an OO language.
 * ====================================================================
 */

// This is to safeguard the class to prevent redefined
#ifndef CITYCONNECT_H_
#define CITYCONNECT_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <iterator>
#include <vector>

using namespace std;

class CityConnect{
public:
	// These are the possible command types
	enum COMMAND_TYPE {
		ADD_ROUTE, GET_DISTANCE, EXIT, INVALID
	};	

private:
	/*
	 * ==============NOTE TO STUDENTS======================================
	 * These messages shown to the user are defined in one place for convenient
	 * editing and proof reading. Such messages are considered part of the UI
	 * and may be subjected to review by UI experts or technical writers. Note
	 * that Some of the strings below include '%1$s' etc to mark the locations
	 * at which java String.format(...) method can insert values.
	 * ====================================================================
	 */
	static const string MESSAGE_DISTANCE;
	static const string MESSAGE_NO_ROUTE;
	static const string MESSAGE_ADDED;
	static const string MESSAGE_INVALID_FORMAT;
	static const string MESSAGE_NO_SPACE;
	static const string WELCOME_MESSAGE;
	static const string MESSAGE_PROGRAM_TERMINATION;

	//These are used for errors
	static const string ERROR_UNRECOGNISED_COMMAND_TYPE;
	static const string ERROR_NULL_ROUTE_ENDPT;

	//This used to indicate wrong user input
	static const int INVALID_NUMBER_FORMAT = -1;

	// This is used to indicate there is no suitable slot to store route
	static const int SLOT_UNAVAILABLE = -1;

	// This is used to indicate the route was not found in the database
	static const int NOT_FOUND = -2;

	//These are the correct number of parameters for each command
	static const int PARAM_SIZE_ADD_ROUTE = 3;
	static const int PARAM_SIZE_GET_DISTANCE = 2;

	//These are the locations at which various parameters will appear in a command
	static const int PARAM_POSITION_START_LOCATION = 0;
	static const int PARAM_POSITION_END_LOCATION = 1;
	static const int PARAM_POSITION_DISTANCE = 2;

	//This array will be used to store the routes
	static string route[10][3]; 

	/*
	 * These are the locations at which various components of the route will
	 * be stored in the routes[][] array.
	 */
	static const int STORAGE_POSITION_START_LOCATION = 0;
	static const int STORAGE_POSITION_END_LOCATION = 1;
	static const int STORAGE_POSITION_DISTANCE = 2;

	static char buffer[255];

	static void showToUser(string text);

	static COMMAND_TYPE determineCommandType(string commandTypeString);

	static string getDistance(string userCommand);
	static int getPositionOfExistingRoute(string newStartLocation, string newEndLocation);

	static string addRoute(string userCommand);
	static void addRouteAtPosition(string newStartLocation, string newEndLocation, string distance, int entryPosition);
	static int location(string newStartLocation, string newEndLocation);
	static bool sameRoute(string startLocation1, string endLocation1, string startLocation2, string endLocation2);

	static bool isPositiveNonZeroInt(string s);
	static string removeFirstWord(string userCommand);
	static string getFirstWord(string userCommand);
	static vector<string> splitParameters(string commandParametersString);

public:
	static string executeCommand(string userCommand);

	/*
	 * ==============NOTE TO STUDENTS====================================== 
	 * Ignore the methods below. They are designed so that the C++ code 
	 * is similar with the Java code.
	 * ====================================================================
	 */
	static void main();
	static string trim_right(const string& s, const string& delimiters = " \f\n\r\t\v" );
	static string trim_left(const string& s, const string& delimiters = " \f\n\r\t\v" );
	static string trim(const string& s, const string& delimiters = " \f\n\r\t\v" );
	static bool equalsIgnoreCase(const string& str1, const string& str2);
	static int parseInt(string str);
	static string replace(string a ,string b , string c);
	template <typename T, size_t N> inline static size_t sizeOfArray( const T(&)[ N ] );
};

#endif