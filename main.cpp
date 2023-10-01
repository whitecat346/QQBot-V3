#pragma comment(lib, "hv.lib")

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "include/hv/json.hpp"
#include "include/hv/WebSocketClient.h"
#include "include/function/function.h"

typedef void( *fun ) ( std::string& msg );

hv::WebSocketClient wsclient;
hv::WebSocketClient wsfileServer;
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
	for ( int i = 0; i < jtemp.at("Bot").at("function").size(); i++ )
	{
		funIndex.insert(std::pair<std::string, int>(jtemp.at("Bot").at("function").at(i),
			i));
		funED.insert(std::pair<std::string, bool>(jtemp.at("Bot").at("endis").at(i),
			jtemp.at("Bot").at("endis").at(i)));
	}
	// File Server function index load
	for ( int i = 0; i < jtemp.at("FileServer").at("function").size(); i++ )
	{
		fileIndex.insert(std::pair<std::string, int>(jtemp.at("FileServer").at("function").at(i), i));
	}
}

void closeFunction(int closeCode = 0)
{
	wsclient.close();
	wsfileServer.close();
	exit(closeCode);
}

int main(int argc, char** argv)
{
	// WebSocket Client Set
	reconn_setting_t reconn;
	reconn_setting_init(&reconn);
	reconn.min_delay = 1000;
	reconn.max_delay = 10000;
	reconn.delay_policy = 2;

	wsclient.onmessage = qqBot::OnMessage;
	wsclient.onopen = qqBot::OnOpen;
	wsclient.onclose = [ ] ()
		{
			std::cout << "OnClose!";
			exit(0);
		};

	wsfileServer.onmessage = fileServer::OnMessage;
	wsfileServer.onopen = fileServer::OnOpen;
	wsfileServer.onclose = [ ] ()
		{
			std::cout << "File Server OnClose!";
			exit(0);
		};

	// Port Input
	if ( argc == 0 )
	{
		unsigned int iport = 0;
		std::string sPort;
		std::cout << "Not Found Command. ";

		for ( int i = 0; i < 2; i++ )
		{
			if ( i == 0 ) std::cout << "Please Input GO-CqHTTP Port: ";
			else if ( i == 1 ) std::cout << "Please Input File Server Port: ";

			std::cin >> sPort;
			for ( int i = 0; i < sPort.size(); i++ )
				if ( !isdigit(sPort.at(i)) ) throw( "Port Have No Digit Char" );

			std::istringstream sti(sPort);
			sti >> iport;

			if ( iport >= 1 && iport <= 65535 )
			{
				if ( i == 0 )
				{
					std::cout << "Connect On Bot...";
					wsclient.open(( "ws://127.0.0.1:" + std::to_string(iport) ).c_str());
					sPort.clear();
					iport = 0;
					std::cout << "Done!" << std::endl;
				}
				else if ( i == 1 )
				{
					std::cout << "Connect On File Server...";
					wsfileServer.open(( "ws://127.0.0.1:" + std::to_string(iport) ).c_str());
					std::cout << "Done!" << std::endl;
				}
			}
			}
			else throw( "Out Of Memory!" );
		}
	}

	// Start
	openSet();

	// No Exit
	while ( true );

	return 0;
}
