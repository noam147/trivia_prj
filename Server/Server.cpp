#include "Server.h"
#include "Communicator.h"
Server::Server()
{
}
void Server::run()
{
	try {
		
		WSAInitializer wsa_init;
		_c = new Communicator();
		_c->startHandleRequests();
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
		
	}
	delete _c;
}
