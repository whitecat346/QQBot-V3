#pragma comment(lib, "hv.lib")

#include <iostream>
#include <string>
#include <map>
#include "include/hv/json.hpp"
#include "include/hv/WebSocketClient.h"

typedef void( *fun ) ( std::string& msg );

hv::WebSocketClient wsclient;
std::map<int,fun>  funIndex;
std::map<int, bool> funED;

void openSet()
{
	
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
			if (omMsg.at("message").at(0) == '#')
			{
				
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
		bool bfin = false;
		for ( int i = 1; i < argc; i++ )
		{
			if ( argv [i] == "-cq" || argv [i] == "-fs" )
			{
				bfin = true;
				break;
			}
		}
		if (bfin == true)
		{
			std::string temp = argv [2];
			wsclient.open(("ws://127.0.0.1:" + temp).c_str());
		}
		else
		{
			std::cout << "Command Error!" << std::endl;
			exit(0);
		}
	}

	// Not Exit
	while ( true );

	return 0;
}
