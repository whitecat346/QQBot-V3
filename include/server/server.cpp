#include "server.h"
#include "../hv/EventLoop.h"
#include "../hv/htime.h"

class MyContext {
public:
	MyContext() {
		printf("MyContext::MyContext()\n");
		timerID = INVALID_TIMER_ID;
	}
	~MyContext() {
		printf("MyContext::~MyContext()\n");
	}

	int handleMessage(const std::string& msg, enum ws_opcode opcode) {
		printf("onmessage(type=%s len=%d): %.*s\n", opcode == WS_OPCODE_TEXT ? "text" : "binary",
			(int)msg.size(), (int)msg.size(), msg.data());
		return msg.size();
	}

	hv::TimerID timerID;
};

void WebSocketServer::OnMessage(const WebSocketChannelPtr& channel, const std::string& msg)
{
	std::cout << "Get new message: " << msg << std::endl;

	auto ctx = channel->getContextPtr<MyContext>();
	ctx->handleMessage(msg, channel->opcode);
}

void WebSocketServer::OnOpen(const WebSocketChannelPtr& channel, const HttpRequestPtr& req)
{
	std::cout << "Server is open now! Path:  " << req->Path() << std::endl;

	printf("onopen: GET %s\n", req->Path().c_str());
	auto ctx = channel->newContextPtr<MyContext>();
	// send(time) every 1s
	ctx->timerID = hv::setInterval(1000, [ channel ] (hv::TimerID id) {
		if ( channel->isConnected() && channel->isWriteComplete() ) {
			char str [DATETIME_FMT_BUFLEN] = { 0 };
			datetime_t dt = datetime_now();
			datetime_fmt(&dt, str);
			channel->send(str);
		}
	});
}

void WebSocketServer::OnClose(const WebSocketChannelPtr& channel)
{
	std::cout << "Server is close now!" << std::endl;

	printf("onclose\n");
	auto ctx = channel->getContextPtr<MyContext>();
	if ( ctx->timerID != INVALID_TIMER_ID ) {
		hv::killTimer(ctx->timerID);
		ctx->timerID = INVALID_TIMER_ID;
	}
	// channel->deleteContextPtr();
}
