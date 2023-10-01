#pragma comment(lib, "hv.lib")

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "include/hv/json.hpp"
#include "include/hv/WebSocketClient.h"
#include "include/string/function.h"
#include "include/function/function.h"

typedef void( *fun ) ( std::string& msg );

hv::WebSocketClient wsclient;
std::map<std::string, int>  funIndex;
std::map<std::string, bool> funED;
std::map<std::string, int> fileIndex;

fun findex [] = { qqBot::fecho, qqBot::fcave };
fun fs [] = { fileServer::fscave };

void openSet()
{
	std::ifstream cfg("config.json");
	nlohmann::json jtemp = nlohmann::json::parse(cfg);
	cfg.close();

	// Bot function index load
	for (int i = 0; i < jtemp.at("Bot").at("function").size(); i++ )
	{
		funIndex.insert(std::pair<std::string, int>(jtemp.at("Bot").at("function").at(i),
			i));
		funED.insert(std::pair<std::string, bool>(jtemp.at("Bot").at("endis").at(i),
			jtemp.at("Bot").at("endis").at(i)));
	}
	// File Server function index load
	for (int i = 0; i < jtemp.at("FileServer").at("function").size(); i++ )
	{
		fileIndex.insert(std::pair<std::string, int>(jtemp.at("FileServer").at("function").at(i), i));
	}
}

void closeFunction(int closeCode = 0)
{
	wsclient.close();
	exit(closeCode);
}

void OnMessage(const std::string &msg)
{
		if(msg[0] == '$')
		{
			std::string temp;
			for ( int i = msg.find(' ') + 1; i < msg.length(); i++ )
				temp += msg [i];
			wsclient.send(temp);
		}
		else
		{
			nlohmann::json omMsg = nlohmann::json::parse(msg);
			if (omMsg.find("post_type") != omMsg.end())
			{
				if (omMsg.at("message").at(0) == '#')
				{
					int group_id = omMsg.at("group_id");
					std::string msgInfo = omMsg.at("message");
					std::map<std::string, int>::iterator it = funIndex.find(str::getFunName(msgInfo));
					if (it != funIndex.end() )
					{
						if (funED.at(str::getFunName(msgInfo)) == true)
						{
							std::string sendTemp = msg;
							findex [funIndex [str::getFunName(msgInfo)]](sendTemp);
							if (str::getFunName(sendTemp) == "send")
							{
								it = fileIndex.find(str::fileServerGetFunctionName(sendTemp));
								if (it != fileIndex.end() )
								{
									
								}
								else
								{
									std::cout << "FileServer Command Not Found!" << std::endl;
									closeFunction(0);
								}
							}
						}
						else
						{
							wsclient.send("{\"action\":\"send_group_msg\",\"params\":{\"group_id\":"
								+ std::to_string(group_id)
								+ ",\"message\":\"[ERROR] 功能未启用！"
								+ "\"}}");
						}
					}
					else
					{
						wsclient.send("{\"action\":\"send_group_msg\",\"params\":{\"group_id\":"
						+ std::to_string(group_id)
						+ ",\"message\":\"[ERROR] 功能未找到！"
						+ "\"}}");
					}
				}
			}
		}
}

void OnOpen()
{
	
}

int main(int argc, char** argv)
{
	// WebSocket Client Set
	reconn_setting_t reconn;
	reconn_setting_init(&reconn);
	reconn.min_delay = 1000;
	reconn.max_delay = 10000;
	reconn.delay_policy = 2;

	wsclient.onmessage = OnMessage;
	wsclient.onopen = OnOpen;
	wsclient.onclose = [ ] ()
		{
			std::cout << "OnClose!";
			exit(0);
		};

	// Port Input
	if (argc == 0 )
	{
		std::cout << "No Command!" << std::endl;
		exit(0);
	}
	else
	{
		int index [2] = {0,0};
		for ( int i = 1; i <= argc; i++ )
		{
			if ( argv [i] == "-cq" )
				index [0] = i;
			else if ( argv [i] == "-fs" )
				index [1] = i;
		}

		// go-cqhttp Connect
		if (index[0] != 0)
		{
			std::string temp = argv [index[0] + 1];
			std::cout << "Try to connect the go-cqhttp...  ";
			wsclient.open(("ws://127.0.0.1:" + temp).c_str());
			std::cout << "done!" << std::endl;
		}
		else
		{
			std::cout << "Command Error!" << std::endl;
			exit(0);
		}

		// File Server Connect
		if (index[1] != 0)
		{
			std::string temp = argv [index [1] + 1];
			std::cout << "Try to connect the file server...  ";
			wsclient.open(( "ws://127.0.0.1:" + temp ).c_str());
			std::cout << "done!" << std::endl;
		}
		else
		{
			std::cout << "Command Error!" << std::endl;
			exit(0);
		}
	}

	// Start
	openSet();

	// Not Exit
	while ( true );

	return 0;
}
