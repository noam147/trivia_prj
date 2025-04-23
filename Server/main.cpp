#pragma comment (lib, "ws2_32.lib")
#include "Communicator.h"
#include "WSAInitializer.h"
#include <iostream>
#include "IDataBase.h"
#include "SqliteDataBase.h"

#include "RoomAdminRequestHandler.h"

int main() {
	SqliteDataBase s2;
	s2.open();
	s2.printTables();
	Server s;
	s.run();
	return 0;
}
