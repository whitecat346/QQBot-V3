#include <string>
#include "cqmsg.h"

/*
  {
    "action": "终结点名称, 例如 'send_group_msg'",
    "params": {
        "参数名": "参数值",
        "参数名2": "参数值"
    },
    "echo": "'回声', 如果指定了 echo 字段, 那么响应包也会同时包含一个 echo 字段, 它们会有相同的值"
  }
 */
std::string cqmsg::BotGroupMessageSend(unsigned int group_id = NULL, std::string msg, bool auto_escape = false, std::string echo = "!none!")
{
	std::string temp = "{\"action\":\"send_group_msg\",\"params\":{\"group_id\":";
	if ( group_id != NULL )
		temp.append(std::to_string(group_id) + ",\"msg\":\"");
	else throw( "Group ID can't empty!" );

	if ( msg.size() != 0 )
		temp.append(msg + "\"}");
	else throw( "Message is empty!" );

	if ( echo != "!none!" )
		temp.append(",\"echo\":\"" + echo + "\"}");
	else temp.append("}");

	return temp;
}

std::string cqmsg::BotGroupDeleteMessage(int message_id = NULL)
{
	std::string temp = "{\"action\":\"delete_msg\",\"params\":{\"message_id\":";

	if ( message_id != NULL )
		temp.append(std::to_string(message_id) + "}}");
	else throw( "Message ID can't empty!" );

	return temp;
}

std::string cqmsg::BotGroupSetEssenceMsg(int message_id = NULL)
{
	std::string temp = "{\"action\":\"set_essence_msg\",\"params\":{\"message_id\":";
	if ( message_id != NULL )
		temp.append(std::to_string(message_id) + "}}");
	else throw( "Message ID can't empty!" );

	return temp;
}

std::string cqmsg::BotGroupSetGroupWholeBan(unsigned group_id = NULL, bool enable = true)
{
	std::string temp = "{\"action\":\"set_group_whole_ban\",\"params\":{\"group_id\":";

	if ( group_id != NULL )
		temp.append(std::to_string(group_id) + ",\"enable\":" + std::to_string(enable) + "}}");
	else throw( "Group ID can't empty!" );

	return temp;
}

std::string cqmsg::BotGroupDeleteEssenceMsg(int message_id = NULL)
{
	std::string temp = "{\"action\":\"delete_essence_msg\",\"params\":{\"message_id\":";

	if ( message_id != NULL )
		temp.append(std::to_string(message_id) + "}}");
	else throw( "Message ID can't empty!" );

	return temp;
}

std::string cqmsg::BotGroupSetGroupBan(unsigned int group_id = NULL, unsigned int user_id = NULL, unsigned int duration = 0)
{
	std::string temp = "{\"action\":\"set_group_ban\",\"params\":{\"group_id\":";

	if ( group_id != NULL )
		temp.append(std::to_string(group_id) + ",\"user_id\":");
	else throw( "Group ID can't empty!" );

	if ( user_id != NULL )
		temp.append(std::to_string(user_id) + ",\"duration\":");
	else throw( "User ID can't empty!" );

	user_id *= 60;

	temp.append(std::to_string(user_id) + "}}");

	return temp;
}

std::string cqmsg::BotPrivateMessageSend(unsigned int user_id = NULL, unsigned int group_id = NULL, std::string message, bool auto_escape = false, std::string echo = "!none!")
{
	std::string temp = "{\"action\":\"send_private_msg\",\"params\":{\"group_id\":";

	if ( group_id != NULL )
		temp.append(std::to_string(group_id) + ",\"user_id\":");
	else throw( "Group ID can't empty!" );

	if ( user_id != NULL )
		temp.append(std::to_string(user_id) + ",\"message\":\"");
	else throw( "User ID can't empty!" );

	temp.append(message + "\",\"auto_escape\":" + std::to_string(auto_escape) + "}");

	if ( echo != "!none!" )
		temp.append(",\"echo\":\"" + echo + "\"}");
	else temp.append("}");

	return temp;
}


std::string cqmsg::BotGroupSetGroupKick(unsigned int group_id = NULL, unsigned int user_id = NULL, bool reject_add_request = false)
{
	std::string temp = "{\"action\":\"set_group_kick\",\"params\":{\"group_id\":";

	if ( group_id != NULL )
		temp.append(std::to_string(group_id) + ",\"user_id\":");
	else throw( "Group ID can't empty!" );

	if ( user_id != NULL )
		temp.append(std::to_string(user_id) + ",\"reject_add_request\":" + std::to_string(reject_add_request) + "}}");
	else throw( "User ID can't empty!" );

	return temp;
}

std::string cqmsg::BotSetGroupAddRequest(std::string flag, std::string sub_type, bool approve = true, std::string reson = "!none!")
{
	std::string temp = "{\"action\":\"set_group_add_request\",\"params\":{\"flag\":\"" + flag + "\",\"sub_type\":\"" + sub_type + "\",\"approve\":" + std::to_string(approve);

	if ( approve == false )
		temp.append(",\"reson\":" + reson + "\"}}");

	return temp;
}
