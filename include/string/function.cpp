#include <string>
#include "function.h"

inline std::string str::getFunName(std::string in)
{
	std::string out;
	for ( int i = 1; in.at(i) != ' '; i++ )
		out += in.at(i);
	return out;
}

inline std::string str::jrs_to_string(std::string in) { return in; }

inline std::string str::fileServerGetFunctionName(std::string in)
{
	std::string out;
	for ( int i = in.find(' ') + 1; in.at(i) != ' '; i++ )
		out += in.at(i);
	return out;
}

inline std::string str::fileServerGetInfo(std::string in)
{
	std::string out;
	for ( int i = in.rfind(' ') + 1; i < in.size(); i++ )
		out += in.at(i);
	return out;
}
