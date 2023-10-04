#include "server.h"

void WebSocketServer::OnMessage(const WebSocketChannelPtr& channe, const std::string& msg)
{
	std::cout << "Get new message: " << msg << std::endl;
}

void WebSocketServer::OnOpen(const WebSocketChannelPtr& channel, const HttpRequestPtr& req)
{
	std::cout << "Server is open now! Path:  " << req->Path() << std::endl;
}

void WebSocketServer::OnClose(const WebSocketChannelPtr& channel)
{
}
