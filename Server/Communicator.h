
#pragma once
#include "Server.h"
#include "IRequestHandler.h"
#include <string>
#include <mutex>
#include <condition_variable>
#include <WinSock2.h>
#include <unordered_map>
#include "RequestHandleFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "LoginRequestHandler.h"
class Communicator:public Server
{
public:
	//constructor + destructor
	Communicator();
	~Communicator();

	// member methods
	void startHandleRequests();

private:
	// member methods
	void bindAndListen(); // opens a listening socket
	void handleClient(SOCKET sock); // handles client conversation
	void acceptNewClients(); // handles client waiting for connection

	string checkIfLoginReturnUserName(string msg);
	// member variubles
	std::unordered_map<SOCKET, IRequestHandler*> m_clients;
	SOCKET m_serverSocket;
	
	// lockers
	std::mutex m_mtx;
	std::condition_variable m_condition;

};

