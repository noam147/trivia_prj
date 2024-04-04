#pragma once
#include "BaseException.hpp"
class ServerOpenSocketError : protected BaseException {
public:
	ServerOpenSocketError(const std::string& funcName) : BaseException("Error: " + funcName + ":Server cannot open listening socket") {};
};