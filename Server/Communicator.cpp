
#include "Communicator.h"
#include "CommunicationHelper.h"
#include "ServerConnectionError.hpp"
#include "ServerOpenSocketError.hpp"
#include "RequestHandleFactory.h"
#include "AESCryptoAlgorithem.h"
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
	:Server(),m_serverSocket(INVALID_SOCKET),m_crypto(new AESCryptoAlgorithem)
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
	delete m_crypto;
}

std::string Communicator::addLengthToMsg(std::string msg)
{
	int length = msg.size();
	std::string str(4, '\0');  // Initialize the string with four null characters

	// Correct byte manipulation
	str[3] = (char)(length & 0xFF);
	length >>= 8;
	str[2] = (char)(length & 0xFF);
	length >>= 8;
	str[1] = (char)(length & 0xFF);
	length >>= 8;
	str[0] = (char)(length & 0xFF);

	return str + msg;
}


void Communicator::send(string msg, SOCKET client_sock)
{
	char msgCode = msg[0];
	msg = msg.substr(1);
	m_crypto->encrypt(msg);
	msg = addLengthToMsg(msg);
	msg = msgCode + msg;
	CommunicationHelper::sendData(client_sock, msg);
	std::cout << "message sent: " << msg << std::endl;

}

void Communicator::recive(SOCKET client_sock, string& msg)
{
	char codeMsg = ' ';
	unsigned int message_length = CommunicationHelper::getLengthPartFromSocket(client_sock, sizeof(byte) * (MESSAGE_LENGTH + 1), codeMsg);
	msg = CommunicationHelper::getPartFromSocket(client_sock, message_length);//problem with this
	m_crypto->decrypt(msg);
	msg = codeMsg + CommunicationHelper::getPaddedNumber(message_length, 4) + msg;//full msg
	std::cout << "message recived: " << msg << std::endl;
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
	std::string msgToSend = "nothing to show here";
	
	IRequestHandler* currentStatus = this->m_handlerFactory_.createLoginRequestHandler();
	//currentStatus = this->m_handlerFactory_.createRoomAdminRequestHandler(LoggedUser("1"),Room(RoomData()));
	
	this->m_clients.insert(std::make_pair(client_sock,currentStatus));
	try
	{
		do
		{
			recive(client_sock, msg);
			RequestInfo info;
			info.buffer = std::vector<char>(msg.begin(), msg.end());//get msg buffer
			info.receivalTime = std::time(nullptr);//get current time
			auto it = this->m_clients.find(client_sock);

			if (it != this->m_clients.end())
			{
				if (currentStatus == nullptr)
				{
					currentStatus = this->m_handlerFactory_.createLoginRequestHandler();
				}
				try {
					if (currentStatus->isRequestRelevant(info))
					{
						//currentStatus->handleRequest(info);
						RequestResult r = currentStatus->handleRequest(info);
						if (r.newHandler)
						{
							::operator delete(currentStatus);//free memory
							currentStatus = nullptr;
							currentStatus = r.newHandler;
						}
						if (r.response.size() != 0)
						{
							msgToSend = r.response;
						}
						else
						{
							msgToSend = JsonResponsePacketSerializer::serializeResponse(ErrorResponse());
						}
						r.response = "";
					}
					else//if request does not relevant
					{
						msgToSend = JsonResponsePacketSerializer::serializeResponse(ErrorResponse());
					}
				}
				catch (const BaseException& e)
				{
					std::cerr << "Caught BaseException: " << e.what() << std::endl;
				}
				catch(...)
				{
					std::exception_ptr exptr = std::current_exception(); // Capture the current exception
					try {
						if (exptr) {
							std::rethrow_exception(exptr); // Rethrow the captured exception
						}
					}
					catch (const std::exception& e) {
						std::cerr << "Caught exception: " << e.what() << std::endl;
					}
					catch (...) {
						std::cerr << "Caught unknown exception." << std::endl;
					}
				}

				
				
			}
			send(msgToSend, client_sock);
			msgToSend = "invalid msg";
		}
		while (msg != "exit");

	}
	catch (const std::exception& e)
	{
		//::operator delete(currentStatus);
		currentStatus->~IRequestHandler();
		std::cout << "Error: " << e.what() << std::endl;
		
	}
	
	this->m_clients.erase(client_sock);
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

string Communicator::checkIfLoginReturnUserName(string msg)
{
	LoginRequest l;
	try {
	 l = JsonRequestPacketDeserializer::deserializeLoginRequest(msg.c_str());
	}
	catch (const RequestError& e)
	{
		return "";
	}
	catch (...)
	{
		return "";
	}
	return l.userName;
}
