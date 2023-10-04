#pragma comment(lib, "hv.lib")

#include <iostream>
#include <string>
#include "include/server/server.h"
#include "include/hv/WebSocketServer.h"

hv::WebSocketService wsService;

int main(int argc, char ** argv)
{
	wsService.onopen = WebSocketServer::OnOpen;
	wsService.onmessage = WebSocketServer::OnMessage;
	wsService.onclose = WebSocketServer::OnClose;

	hv::WebSocketServer server(&wsService);
	server.setPort(25565);
	server.setThreadNum(4);
	server.run();

	while ( true );

	return 0;
}
