#include "server.h"
#include <iostream>

void server::run()
{
	this->m_commnicator.startHandleRequests();
}
