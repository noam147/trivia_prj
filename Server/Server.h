#pragma once
#pragma comment (lib, "ws2_32.lib")
//#include "Communicator.h"
class Communicator;
#include "WSAInitializer.h"
#include "LoginManager.h"
#include "RequestHandleFactory.h"
#include "IDataBase.h"
class Server
{
public:
	Server();
	void run();
protected:
	IDataBase* m_database;
	RequestHandleFactory m_handlerFactory_;
	Communicator* _c;

};