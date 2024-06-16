
#pragma once
#include "Server.h"
#include "IRequestHandler.h"
#include "BaseException.hpp"
#include <string>
#include <mutex>
#include <condition_variable>
#include <WinSock2.h>
#include <unordered_map>
#include "RequestHandleFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "LoginRequestHandler.h"
#include "ICryptoAlgorithem.h"

class Communicator :public Server
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
	void send(string msg, SOCKET client_sock);
	void recive(SOCKET client_sock, string& msg);
	std::string addLengthToMsg(std::string msg);

	string checkIfLoginReturnUserName(string msg);

	// cryptography
	ICryptoAlgorythem* m_crypto;

	// member variubles
	std::unordered_map<SOCKET, IRequestHandler*> m_clients;
	SOCKET m_serverSocket;

	// lockers
	std::mutex m_mtx;
	std::condition_variable m_condition;

};

