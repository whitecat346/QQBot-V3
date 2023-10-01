#pragma once

#include <string>

namespace fileServer
{
	// WebSocket Message
	void OnMessage(const std::string& msg);

	// Function
	void fscave(std::string& msg);
}

namespace qqBot
{
	// WebSocket Message
	void OnMessage(const std::string& msg);
	void OnOpen();

	// Function
	void fecho(std::string& msg);
	void fcave(std::string& msg);
}
