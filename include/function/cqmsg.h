#pragma once

namespace cqmsg
{
	std::string BotGroupMessageSend(int group_id = NULL, std::string msg, std::string echo = "!none!");
	std::string BotGroupDeleteMessage(int message_id = NULL, std::string echo = "!none!");
}
