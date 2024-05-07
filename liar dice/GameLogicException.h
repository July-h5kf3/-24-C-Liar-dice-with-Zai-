#pragma once
#ifndef LIARSDICE_INCLUDE_EXCEPTIONS_GAMELOGICEXCEPTION_HPP
#define LIARSDICE_INCLUDE_EXCEPTIONS_GAMELOGICEXCEPTION_HPP

#include "CustomException.h"

class GameLogicException : public CustomException 
{
public:
	explicit GameLogicException(const std::string& message) : CustomException("Game Logic Error: " + message) {}
};

#endif //LIARSDICE_INCLUDE_EXCEPTIONS_GAMELOGICEXCEPTION_HPP