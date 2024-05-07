#pragma once
#ifndef LIARSDICE_INCLUDE_EXCEPTIONS_INPUTEXCEPTION_HPP
#define LIARSDICE_INCLUDE_EXCEPTIONS_INPUTEXCEPTION_HPP

#include "CustomException.h"

class InputException : public CustomException 
{
public:
	explicit InputException(const std::string& message) : CustomException("Input Error: " + message) {}
};

#endif //LIARSDICE_INCLUDE_EXCEPTIONS_INPUTEXCEPTION_HPP