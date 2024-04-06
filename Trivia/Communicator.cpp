#include "Communicator.h"
#include "CommunicationHelper.h"
#include "ServerConnectionError.hpp"
#include "ServerOpenSocketError.hpp"
#include "RequestHandleFactory.h"
#include <exception>
#include <iostream>
#include <string>

static const unsigned short PORT = 55555;
static const unsigned int IFACE = 0;
static const byte MESSAGE_LENGTH = 4;

using std::string;
using std::mutex;
using std::unique_lock;


Communicator::Communicator()
	:m_serverSocket(INVALID_SOCKET)
{
	m_serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_serverSocket == INVALID_SOCKET)
		throw ServerConnectionError(__FUNCTION__);
}

Communicator::~Communicator()
{
	try
	{
		::closesocket(m_serverSocket);
	}
	catch (...) {}
}


void Communicator::startHandleRequests()
{

	bindAndListen();
	
	std::thread tr(&Communicator::acceptNewClients, this);
	tr.detach();
	std::string cliStatment = "";
	do
	{
		std::cin >> cliStatment;
		if (cliStatment != "EXIT")
			std::cout << cliStatment << " is not a command" << std::endl;
	} while (cliStatment != "EXIT");
}

void Communicator::bindAndListen()
{

	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;
	// again stepping out to the global namespace
	if (::bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw ServerOpenSocketError(__FUNCTION__);

	if (::listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw ServerOpenSocketError(__FUNCTION__);
}

void Communicator::handleClient(SOCKET client_sock)
{
	std::string msg = "";
	try
	{
		do
		{
			CommunicationHelper::sendHello(client_sock);

			unsigned int message_length = CommunicationHelper::getIntPartFromSocket(client_sock, sizeof(byte) * MESSAGE_LENGTH);
			msg = CommunicationHelper::getStringPartFromSocket(client_sock, message_length);
		}
		while (msg != "exit");

	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	closesocket(client_sock);
}

void Communicator::acceptNewClients()
{
	while (true) {
		SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
			throw ServerConnectionError(__FUNCTION__);

		// create new thread for client	and detach from it
		std::thread tr(&Communicator::handleClient, this, client_socket);
		tr.detach();
	}
}
