#pragma once
#ifndef LIARSDICE_INCLUDE_EXCEPTIONS_FILEEXCEPTION_HPP
#define LIARSDICE_INCLUDE_EXCEPTIONS_FILEEXCEPTION_HPP

#include "CustomException.h"

class FileException : public CustomException 
{
public:
	explicit FileException(const std::string& message) : CustomException("File Error: " + message) {}
};
#endif //LIARSDICE_INCLUDE_EXCEPTIONS_FILEEXCEPTION_HPP