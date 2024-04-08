#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.buffer[0] == LOGIN_REQUEST || info.buffer[0] == SIGN_UP_REQUEST)
	{
		return true;
	}
	return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
	RequestResult r;
	
	if (isRequestRelevant(info))
	{
		if (info.buffer[0] == LOGIN_REQUEST)
		{
			//r.response = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
		}
		
	}
	return RequestResult();
}
