#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
#include <sstream>
#include <fstream>
using std::string;
using std::stringstream;
using std::ofstream;
using std::vector;
using std::cout;
using std::endl;


namespace utils{


// @brief convert parameters to string with space
template < typename T, typename ... Types>
string to_string(const T& firstArg, const Types&... args)
{
	stringstream buf;
	buf << firstArg;
	if constexpr (sizeof ...(args) > 0) return buf.str() + " " + to_string(args...);
	else return buf.str();
}

// @brief convert parameters to string without space 
template < typename T, typename ... Types>
string to_string2(const T& firstArg, const Types&... args)
{
	stringstream buf;
	buf << firstArg;
	if constexpr (sizeof ...(args) > 0) return buf.str() + to_string2(args...);
	else return buf.str();
}

// @brief print message to ui.textBrowser
template<typename... Types> void print(const Types&... args) {
	cout << to_string(args...)<<endl;
}

// @brief log message to file
template<typename... Types> void printToFile(string fileName, const Types&... args) {
	static string fileNameOpened= fileName;
	static ofstream logfile(fileName, std::ios::app);
	if (fileNameOpened != fileName) {
		logfile.close();
		if (fileName != "") {
			logfile.open(fileName, std::ios::app);
			fileNameOpened = fileName;
		}
	}
	logfile << to_string2(args...);
	logfile.flush();
}


}

#endif
