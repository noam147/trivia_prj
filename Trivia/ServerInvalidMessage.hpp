#pragma once
#include "BaseException.hpp"
#include <WinSock2.h>

class ServerOpenSocketError : protected BaseException {
public:
	ServerOpenSocketError(const std::string& funcName, SOCKET sock) : BaseException("Error: " + funcName + ":Invalid message from socket: " + std::to_string(sock) + "\n") {};
};