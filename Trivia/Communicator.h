#pragma once

#include "ComunicateHelper.h"
#include "IRequestHandler.h"
#include <string>
#include <mutex>
#include <condition_variable>
#include <WinSock2.h>
#include <unordered_map>
#include "RequestHandleFactory.h"

class Communicator
{
public:
	//constructor + destructor
	Communicator();
	~Communicator();

	// member methods
	void startHandleRequests();

private:
	// member methods
	void bindAndListen();
	void handleClient(SOCKET sock);
	void acceptNewClient();

	// member variubles
	std::unordered_map<SOCKET, IRequestHandler> m_clients;
	//RequestHandleFactory& m_handleFactory;
	SOCKET m_serverSocket;
	
	// lockers
	std::mutex _mtxReceivedMessages;
	std::condition_variable _msgQueueCondition;

};

