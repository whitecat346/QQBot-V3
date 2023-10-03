#pragma once

namespace str
{
	inline std::string getFunName(std::string in);
	inline std::string jrs_to_string(std::string in);
	inline std::string fileServerGetFunctionName(std::string in);
	inline std::string fileServerGetInfo(std::string in);
	inline std::string fileServerAllInfo(std::string in);

	// Bot Function
	namespace BotFunction
	{
		std::string CqCode_String(std::string& in);
		std::string GetCqCode(std::string& in);

		inline std::string EchoMessageGet(std::string in);
	}
}
