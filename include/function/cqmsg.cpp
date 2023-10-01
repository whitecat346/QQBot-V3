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
std::string cqmsg::BotGroupMessageSend(int group_id = NULL, std::string msg, std::string echo = "!none!")
{
	std::string temp = "{\"action\":\"send_group_msg\",\"params\":{\"group_id\":\"";
	if ( group_id != NULL )
		temp.append(std::to_string(group_id) + "\",\"msg\":\"");
	else throw( "Group ID can't empty!" );

	if ( msg.size() != 0 )
		temp.append(msg + "\"}");
	else throw( "Message is empty!" );

	
}
