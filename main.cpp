#pragma comment(lib, "hv.lib")

#include <iostream>
#include <string>
#include "include/hv/WebSocketServer.h"
#include "include/hv/EventLoop.h"
#include "include/hv/htime.h"
#include <cstdlib>

hv::WebSocketService wsService;

int main(int argc, char ** argv)
{
	wsService.onopen = [ ] (const WebSocketChannelPtr& channe, const HttpRequestPtr& req)
		{
			std::cout << "onopen: GET " << req->Path() << std::endl;
		};
	wsService.onmessage = [ ] (const WebSocketChannelPtr& channe, const std::string& msg)
		{
			std::cout << "onmessage: " << (int)msg.size() << msg.data() << std::endl;
		};
	wsService.onclose = [ ] (const WebSocketChannelPtr& channe)
		{
			std::cout << "onclose" << std::endl;
		};

	hv::WebSocketServer server(&wsService);
	server.setPort(25565);
	server.setThreadNum(4);
	server.run();

	return 0;
}
