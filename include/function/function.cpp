#include "function.h"
#include <string>

#include "../hv/WebSocketClient.h"
#include "../string/function.h"

// File Server

// WebSocket Message
void fileServer::OnMessage(const std::string& msg)
{
	
}

void fileServer::OnOpen()
{
	
}

void fileServer::fscave(std::string& msg)
{
	
}

// QQ Bot

// WebSocket Message
typedef void( *fun ) ( std::string& msg );

extern fun findex [];
extern fun fs [];
extern hv::WebSocketClient wsclient;
extern hv::WebSocketClient wsfileServer;
extern std::map<std::string, int> funIndex;
extern std::map<std::string, bool> funED;
extern std::map<std::string, int> fileIndex;
extern void closeFunction(int closeCode = 0);

void qqBot::OnOpen()
{
	
}


void qqBot::OnMessage(const std::string& msg)
{
	nlohmann::json omMsg = nlohmann::json::parse(msg);
	if ( omMsg.find("post_type") != omMsg.end() )
	{
		if ( omMsg.at("message").at(0) == '#' )
		{
			int group_id = omMsg.at("group_id");
			std::string msgInfo = omMsg.at("message");
			std::map<std::string, int>::iterator it = funIndex.find(str::getFunName(msgInfo));
			if ( it != funIndex.end() )
			{
				if ( funED.at(str::getFunName(msgInfo)) == true )
				{
					std::string sendTemp = msg;
					findex [funIndex [str::getFunName(msgInfo)]](sendTemp);
					if ( str::getFunName(sendTemp) == "send" )
					{
						it = fileIndex.find(str::fileServerGetFunctionName(sendTemp));
						if ( it != fileIndex.end() )
						{
							sendTemp = str::fileServerGetInfo(sendTemp);
							fs [fileIndex [str::fileServerGetFunctionName(sendTemp)]](sendTemp);
							wsfileServer.send(sendTemp);
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

// Function
void qqBot::fecho(std::string& msg)
{

}

void qqBot::fcave(std::string& msg)
{
	
}
