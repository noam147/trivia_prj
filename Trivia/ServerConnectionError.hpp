#pragma once
#include "BaseException.hpp"
class ServerConnectionError : protected BaseException {
public:
	ServerConnectionError(const std::string& funcName): BaseException("Error:  " + funcName + "Server connection with client cut off\n") {};
};