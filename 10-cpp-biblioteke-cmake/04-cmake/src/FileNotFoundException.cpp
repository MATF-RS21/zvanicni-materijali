#include "FileNotFoundException.h"

FileNotFoundException::FileNotFoundException(const char* message)
	: std::exception()
    , message_(message)
{}
	
const char* FileNotFoundException::what() const noexcept
{
    return message_.c_str();
}
