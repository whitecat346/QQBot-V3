#pragma once

namespace cqmsg
{
	std::string BotGroupMessageSend(unsigned int group_id = NULL, std::string msg = "", bool auto_escape = false, std::string echo = "!none!");
	std::string BotPrivateMessageSend(unsigned int user_id = NULL, unsigned int group_id = NULL, std::string message = "", bool auto_escape = false, std::string echo = "!none!");
	std::string BotGroupDeleteMessage(int message_id = NULL);
	std::string BotGroupSetGroupBan(unsigned int group_id = NULL, unsigned int user_id = NULL, unsigned int duration = 0);
	std::string BotGroupSetGroupWholeBan(unsigned int group_id = NULL, bool enable = true);
	std::string BotGroupSetEssenceMsg(int message_id = NULL);
	std::string BotGroupDeleteEssenceMsg(int message_id = NULL);
	std::string BotGroupSetGroupKick(unsigned int group_id = NULL, unsigned int user_id = NULL, bool reject_add_request = false);
	std::string BotSetGroupAddRequest(std::string flag, std::string sub_type, bool approve = true, std::string reson = "!none!");
}
