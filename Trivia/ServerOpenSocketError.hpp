#pragma once
#include "BaseException.hpp"
class ServerConnectionError : protected BaseException {
public:
	ServerConnectionError() : BaseException("Error: Server cannot open listening socket") {};
};