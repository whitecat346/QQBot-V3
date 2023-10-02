#pragma once

#define DEFAULT_INT 96230

#include <string>

namespace encrypt
{
	// Encrypt
	std::string encode(std::string rstr);
	std::string decode(std::string rstr);

	std::string to_hex(const char in);

	namespace random_make
	{
		std::string FunctionA(const char in);
		std::string FunctionB(const char in);
		std::string FunctionC(const char in);
		std::string FunctionD(const char in);

		int INT_Y();
	}
}
