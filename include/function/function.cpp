#include "function.h"
#include <string>

#include "../hv/WebSocketClient.h"
#include "../string/function.h"

#include "cqmsg.h"

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
	if ( omMsg.find("echo") != omMsg.end() && omMsg.at("echo") == "onopen")
	{
		
	}
	else if ( omMsg.find("post_type") != omMsg.end() )
	{
		if (omMsg.at("post_type") == "message" && omMsg.at("message").at(0) == '#' )
		{
			int group_id = omMsg.at("group_id");
			std::string msgInfo = omMsg.at("message");
			std::map<std::string, int>::iterator it = funIndex.find(str::getFunName(msgInfo));
			if ( it != funIndex.end() )
			{
				if ( funED.at(str::getFunName(msgInfo)) == true )
				{
					std::string sendTemp = msg;
					findex [funIndex ["f" + str::getFunName(msgInfo)]](sendTemp);
					if ( str::getFunName(sendTemp) == "send" )
					{
						if ( it = fileIndex.find(str::fileServerGetFunctionName(sendTemp)); it != fileIndex.end() )
						{
							sendTemp = str::fileServerGetInfo(sendTemp);
							fs [fileIndex ["fs" + str::fileServerGetFunctionName(sendTemp)]](sendTemp);
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
	else if ( omMsg.find("status") != omMsg.end() )
	{
		if ( omMsg.find("data") != omMsg.end() )
		{
			std::cout << "OK!  Reply Message: "  << omMsg.at("data") << std::endl;
		}
		else
		{
			if ( omMsg.at("status") == "ok" && omMsg.at("retcode") == 0 )
				std::cout << "OK!" << std::endl;
			else if ( omMsg.at("status") == "async" && omMsg.at("retcode") == 1 )
				std::cout << "ASYNC!" << std::endl;
			else if ( omMsg.at("status") == "failed" && omMsg.at("retcode") != 0 && omMsg.at("retcode") != 1 )
				std::cout << "FATAL!  INFO: " << omMsg.at("msg") << " & " << omMsg.at("wording") << std::endl;
		}
	}
}

// Function
void qqBot::fecho(std::string& msg)
{
	nlohmann::json jmsg = nlohmann::json::parse(msg);
	msg = cqmsg::BotGroupMessageSend(jmsg.at("group_id"),
		str::BotFunction::EchoMessageGet(jmsg.at("message")));
}

void qqBot::fcave(std::string& msg)
{
	
}
