#include <string>
#include "str.h"

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

std::string str::fileServerAllInfo(std::string in)
{
	std::string out;
	for ( int i = in.find(' '); i < in.size(); i++ )
		out += in.at(i);
	return out;
}

std::string str::BotFunction::CqCode_String(std::string& in)
{
	/* data example
	 *	CQ CODE:
	 *	[CQ:at,qq=2710458198,name=Null]
	 *
	 *	JSON:
	 *	{
	 *		"type": "at",
	 *		"data": {
	 *			"qq": "2710458198",
	 *			"name": "Null“
	 *		}
	 *	}
	 */

	 // temp get type
	 // temp get data info (all are string)
	 // return temp

	std::string temp = "{\"type\":\"";
	for ( int i = 0; i < in.size(); i++ )
	{
		if ( in [i] == ':' )
		{
			while ( true )
			{
				i++;
				if ( in [i] == ',' ) break;
				temp += in [i];
			}
			temp.append("\",\"data\":{\"");

			while ( true )
			{
				i++;
				if ( in [i] == '=' )
				{
					temp.append("\":\"");
					while ( true )
					{
						i++;
						if ( in [i] == ',' )
						{
							i++;
							temp.append("\",\"");
							break;
						}
						else if ( in [i] == ']' )
						{
							temp.append("\"}}");
							return temp;
						}
						temp += in [i];
					}
				}
				temp += in [i];
			}
		}
	}
}

std::string str::BotFunction::GetCqCode(std::string& in)
{
	std::string temp;
	if ( in.find("[CQ:") )
	{
		for ( int i = in.find("[CQ:"); i < in.size(); i++ )
		{
			if ( in [i] == ']' )
			{
				temp.append("]");
				break;
			}
			temp += in [i];
		}
		return temp;
	}
	else return "false";
}

inline std::string str::BotFunction::EchoMessageGet(std::string in)
{
	std::string out;
	for ( int i = in.find(' '); i < in.length(); i++ )
		out += in.at(i);
	return out;
}
