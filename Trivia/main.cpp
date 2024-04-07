#pragma comment (lib, "ws2_32.lib")
#include "Communicator.h"
#include "WSAInitializer.h"
#include <iostream>

int main() {
	try {
		WSAInitializer wsa_init;
		Communicator c;
		c.startHandleRequests();
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;
}