#pragma once

#include "../hv/WebSocketServer.h"

namespace WebSocketServer
{
	void OnMessage(const WebSocketChannelPtr& channel , const std::string& msg);
	void OnOpen(const WebSocketChannelPtr& channel, const HttpRequestPtr& req);
	void OnClose(const WebSocketChannelPtr& channel);
}
