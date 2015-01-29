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

#include "CityConnect.h"

// These are the static variables that cannot be initialize in header file
const string CityConnect::MESSAGE_DISTANCE = "Distance from %s to %s is %s";
const string CityConnect::MESSAGE_NO_ROUTE = "No route exists from %s to %s!";
const string CityConnect::MESSAGE_ADDED = "Route from %s to %s with distance %skm added";
const string CityConnect::MESSAGE_INVALID_FORMAT = "invalid command format :%s";
const string CityConnect::WELCOME_MESSAGE = "Welcome to SimpleRouteStore!";
const string CityConnect::MESSAGE_NO_SPACE = "No more space to store locations";
const string CityConnect::MESSAGE_PROGRAM_TERMINATION = "Press any key to terminate the program . . .";

const string CityConnect::ERROR_UNRECOGNISED_COMMAND_TYPE = "ERROR: Unrecognised command type";
const string CityConnect::ERROR_NULL_ROUTE_ENDPT = "ERROR: Route end points cannot be NULL";


string CityConnect::route[10][3];
char CityConnect::buffer[255];

/*
* ==============NOTE TO STUDENTS======================================
* Notice how this method solves the whole problem at a very high level. We
* can understand the high-level logic of the program by reading this method
* alone.
* ====================================================================
*/
void CityConnect::main() {
	showToUser(WELCOME_MESSAGE);
		
	while (true) {
		cout << "Enter command:";
		string command;
		getline (cin, command);
		string userCommand = command;
		string feedback = executeCommand(userCommand);
		showToUser(feedback);	
	}
}

/*
* ==============NOTE TO STUDENTS====================================== 
* If the reader wants a deeper understanding of the solution, he/she can go to
* the next level of abstraction by reading methods (given below)
* that is referenced by the method above.
* ====================================================================
*/

void CityConnect::showToUser(string text) {
	cout << text << endl;
}

string CityConnect::executeCommand(string userCommand) {
	if(trim(userCommand) == "") {
		sprintf_s(buffer, MESSAGE_INVALID_FORMAT.c_str(), "");
		return buffer;
	}

	string commandTypeString = getFirstWord(userCommand);
		
	COMMAND_TYPE commandType = determineCommandType(commandTypeString);

	switch (commandType) {
	case ADD_ROUTE: 
		return addRoute(userCommand);
	case GET_DISTANCE: 
		return getDistance(userCommand);
	case INVALID:
		{
			sprintf_s(buffer, MESSAGE_INVALID_FORMAT.c_str(), userCommand.c_str());
			return buffer;
		}
	case EXIT:
		exit(0);
	default:
		//Generates an error message and termiantes the program
		showToUser(ERROR_UNRECOGNISED_COMMAND_TYPE);
		showToUser(MESSAGE_PROGRAM_TERMINATION);

		getchar();
		exit(EXIT_FAILURE);
	}

	/* 
	 * ==============NOTE TO STUDENTS==================================
	 * If the rest of the program is correct, this error will never be
	 * thrown. That is why we use an Error instead of an Exception. 
	 * ================================================================
	 */
}

/* ==============NOTE TO STUDENTS======================================
 * After reading the above code, the reader should have a reasonable
 * understanding of how the program works. If the reader wants to go 
 * EVEN more deep into the solution, he/she can read the methods given 
 * below that solves various sub-problems at lower levels of abstraction. 
 * ====================================================================
 */
	
/**
 * This operation determines which of the supported command types the user
 * wants to perform
 * 
 * @param commandTypeString
 *            is the first word of the user command
 */
CityConnect::COMMAND_TYPE CityConnect::determineCommandType(string commandTypeString) {

	    // In C++, we do not need to check if the string is null if it is not declare as a pointer

	if(equalsIgnoreCase(commandTypeString, "addroute")) {
		return COMMAND_TYPE::ADD_ROUTE;
	} else if (equalsIgnoreCase(commandTypeString, "getdistance")) {
		return COMMAND_TYPE::GET_DISTANCE;
	} else if (equalsIgnoreCase(commandTypeString, "exit")) {
		return COMMAND_TYPE::EXIT;
	} else {
		return COMMAND_TYPE::INVALID;
	}
}

/**
 * This operation is used to find the distance between two locations
 * 
 * @param userCommand
 *            is the full string user has entered as the command
 * @return the distance
 */
string CityConnect::getDistance(string userCommand) {

	vector<string> parameters = splitParameters(removeFirstWord(userCommand));

	if(parameters.size() < PARAM_SIZE_GET_DISTANCE) {
		sprintf_s(buffer, MESSAGE_INVALID_FORMAT.c_str(), userCommand.c_str());
		return buffer;
	}
		
	string newStartLocation = parameters[PARAM_POSITION_START_LOCATION];
	string newEndLocation = parameters[PARAM_POSITION_END_LOCATION];

	int position = getPositionOfExistingRoute(newStartLocation, newEndLocation);

	if (position == NOT_FOUND) {
		sprintf_s(buffer, MESSAGE_NO_ROUTE.c_str(), newStartLocation.c_str(), newEndLocation.c_str());
		return buffer;
	} 
	else 
	{
		sprintf_s(buffer, MESSAGE_DISTANCE.c_str(), newStartLocation.c_str(), newEndLocation.c_str(), route[position][STORAGE_POSITION_DISTANCE].c_str());
		return buffer;
	}
}

/**
 * @return Returns the position of the route represented by 
 *    newStartLocation and newEndLocation. Returns NOT_FOUND if not found.
 */
int CityConnect::getPositionOfExistingRoute(string newStartLocation, string newEndLocation) {
	for (int i = 0; i < sizeOfArray(route); i++) {
			
		string existing_start_location = route[i][STORAGE_POSITION_START_LOCATION];
		string existing_end_location = route[i][STORAGE_POSITION_END_LOCATION];
			
		if (existing_start_location.empty()) { //beginning of empty slots
			return NOT_FOUND;
		} else if (sameRoute(existing_start_location, existing_end_location, 
				newStartLocation, newEndLocation)) {
			return i;
		} 
	}

	return NOT_FOUND;
}

/**
 * This operation adds a route to the storage. If the route already exists,
 * it will be overwritten.
 * 
 * @param userCommand
 *            (although we receive the full user command, we assume without
 *            checking the first word to be 'addroute')
 * @return status of the operation
 */
string CityConnect::addRoute(string userCommand) {

	vector<string> parameters = splitParameters(removeFirstWord(userCommand));

	if(parameters.size() < PARAM_SIZE_ADD_ROUTE){
		sprintf_s(buffer, MESSAGE_INVALID_FORMAT.c_str(), userCommand.c_str());
		return buffer;
	}
		
	string newStartLocation = parameters[PARAM_POSITION_START_LOCATION];
	string newEndLocation = parameters[PARAM_POSITION_END_LOCATION];
	string distance = parameters[PARAM_POSITION_DISTANCE];
		
	if(!isPositiveNonZeroInt(distance)){
		sprintf_s(buffer, MESSAGE_INVALID_FORMAT.c_str(), userCommand.c_str());
		return buffer;
	}

	int slotPosition = location(newStartLocation, newEndLocation);

	if (slotPosition == SLOT_UNAVAILABLE){
		return MESSAGE_NO_SPACE;
	}

	addRouteAtPosition(newStartLocation, newEndLocation, distance,
			slotPosition);

	sprintf_s(buffer, MESSAGE_ADDED.c_str(), newStartLocation.c_str(), newEndLocation.c_str(), distance.c_str());
	return buffer;
}

void CityConnect::addRouteAtPosition(string newStartLocation, string newEndLocation, string distance, int entryPosition) {
	route[entryPosition][STORAGE_POSITION_START_LOCATION] = newStartLocation;
	route[entryPosition][STORAGE_POSITION_END_LOCATION] = newEndLocation;
	route[entryPosition][STORAGE_POSITION_DISTANCE] = distance;
}

/**
 * @return Returns a suitable slot for the route represented by 
 *   newStartLocation and newEndLocation. Returns SLOT_UNAVAILABLE if
 *   no suitable slot is found.
 */
int CityConnect::location(string newStartLocation, string newEndLocation) {
	for (int i = 0; i < sizeOfArray(route); i++) {

		string existingStartLocation = route[i][STORAGE_POSITION_START_LOCATION];
		string existingEndLocation = route[i][STORAGE_POSITION_END_LOCATION];
			
		if (existingStartLocation.empty()) { //empty slot 
			return i;
		} else if (sameRoute(existingStartLocation, existingEndLocation, 
			newStartLocation, newEndLocation)){
			return i;
		} 
	}

	return SLOT_UNAVAILABLE;
}

/**
 * This operation checks if two routes represents the same route.
 */
bool CityConnect::sameRoute(string startLocation1, 
	string endLocation1, string startLocation2, string endLocation2) {

	if((startLocation1.empty())||(endLocation1.empty())
				&&(startLocation2.empty())||(endLocation2.empty())) {			
			showToUser(ERROR_NULL_ROUTE_ENDPT);
			showToUser(MESSAGE_PROGRAM_TERMINATION);

			getchar();
			exit(EXIT_FAILURE);
	}
		
	return (equalsIgnoreCase(startLocation1, startLocation2) && equalsIgnoreCase(endLocation1, endLocation2))
			||(equalsIgnoreCase(startLocation1, endLocation2) && equalsIgnoreCase(endLocation1, startLocation2));
}

bool CityConnect::isPositiveNonZeroInt(string s){
		int i = parseInt(s);

		if(i == INVALID_NUMBER_FORMAT) {
			return false;
		} else { 
			//return true if i is greater than 0
			return (i > 0 ? true : false);
		}
}

string CityConnect::removeFirstWord(string userCommand){
	return trim(replace(userCommand, getFirstWord(userCommand), ""));
}

string CityConnect::getFirstWord(string userCommand){
	string commandTypeString = splitParameters(userCommand)[0];
	return commandTypeString;
}

// This method only split string based on delimiter space
vector<string> CityConnect::splitParameters(string commandParametersString){
	vector<string> tokens;
	istringstream iss(commandParametersString);
    copy(istream_iterator<string>(iss),
             istream_iterator<string>(),
             back_inserter<vector<string> >(tokens));

	return tokens;
}








// ==================================================================================================================================================================

/*
 * ==============NOTE TO STUDENTS====================================== 
 * Ignore the methods below. They are designed so that the C++ code 
 * is similar with the Java code.
 * ====================================================================
 */
int main() {
	CityConnect::main();
}

bool CityConnect::equalsIgnoreCase(const string& str1, const string& str2) {
    if (str1.size() != str2.size()) {
        return false;
    }
	
    for (string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2) {
        if (tolower(*c1) != tolower(*c2)) {
            return false;
        }
    }
    return true;
}

int CityConnect::parseInt(string str) {
	char c;
	int i=0;
    std::stringstream ss(str);
    ss >> i;
    if (ss.fail() || ss.get(c)) {
		return INVALID_NUMBER_FORMAT;
    } else {
		return i;
	}
}

string CityConnect::replace(string a ,string b , string c) {
    int pos ;
    do
    {
        pos = a.find(b);
        if (pos!=-1)  a.replace(pos, b.length(), c);
    }
    while (pos!=-1);
    return a;
}

inline string CityConnect::trim_right(const string& s, const string& delimiters) {
	return s.substr( 0, s.find_last_not_of( delimiters ) + 1 );
}

inline string CityConnect::trim_left(const string& s, const string& delimiters) {
	return s.substr( s.find_first_not_of( delimiters ) );
}

inline string CityConnect::trim(const string& s, const string& delimiters) {
	if(!s.empty())
		return trim_left( trim_right( s, delimiters ), delimiters );
	else
		return s;
}

template <typename T, size_t N> inline size_t 
	CityConnect::sizeOfArray(const T(&)[ N ]) {
  return N;
}
// ==================================================================================================================================================================
