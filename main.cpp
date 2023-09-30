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
				std::string msgInfo = omMsg.at("message");
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
