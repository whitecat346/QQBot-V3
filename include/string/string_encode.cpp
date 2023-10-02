#include <random>
#include "string_encode.h"

#include "../hv/hstring.h"

#define DEFAULT_INT 96230

static unsigned int Y = encrypt::random_make::INT_Y();
static unsigned int N = 9 - Y;

// Encrypt
std::string encrypt::encode(std::string rstr)
{

}

std::string encrypt::decode(std::string rstr)
{
	return std::string();
}


// Random Make
std::string encrypt::random_make::FunctionA(const char in)
{
	const unsigned int char_int = (int)in;
	return std::to_string(( ( ( char_int * Y ) * Y ) / 2 ) * (N * N));
}

std::string encrypt::random_make::FunctionB(const char in)
{
	const unsigned int char_int = (int)in;
	return std::to_string(( ( ( char_int + Y ) * ( N * N ) ) / 4 ) * Y);
}

std::string encrypt::random_make::FunctionC(const char in)
{
	const unsigned int char_int = (int)in;
	return std::to_string(( ( ( ( char_int * N ) * ( char_int * N ) ) / 4 ) * Y ) + N);
}

std::string encrypt::random_make::FunctionD(const char in)
{
	const unsigned int char_int = (int)in;
	return std::to_string(( ( ( ( char_int + N ) * ( char_int + N ) ) / 2 ) * Y ) - ( Y * Y ));
}

int encrypt::random_make::INT_Y()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 9);

	return dist(gen);
}

