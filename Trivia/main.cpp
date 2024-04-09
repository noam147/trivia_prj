#pragma comment (lib, "ws2_32.lib")
#include "WSAInitializer.h"
#include "server.h"
#include <iostream>

int main() {
	WSAInitializer wsa_init;
	server serve;
	serve.run();
	return 0;
}