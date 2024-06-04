
#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandleFactory& handlerFactory):m_handlerFactory(handlerFactory)
{
}

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
		if (info.buffer[0] == SIGN_UP_REQUEST)
		{
			return this->signup(info);
		}
		else if (info.buffer[0] == LOGIN_REQUEST)
		{
			
			return this->login(info);
		}

}



RequestResult LoginRequestHandler::login(RequestInfo info)
{
	
	RequestResult r;
	LoginRequest l;
	std::string str = "";

	for (int i = 0; i < info.buffer.size(); i++)
	{
		str += info.buffer[i];
	}
	try
	{
		 l = JsonRequestPacketDeserializer::deserializeLoginRequest(CommunicationHelper::stringToCharArr(str));
	}
	catch (const RequestError& e)
	{
		r.newHandler = nullptr;
		r.response = CommunicationHelper::createErrorResponse();
		return r;
	}
	catch (...)
	{
		r.newHandler = nullptr;
		r.response = CommunicationHelper::createErrorResponse();
		return r;
	}

	if (this->m_handlerFactory.getLoginManager().logIn(l.userName, l.password) == true)
	{
		r.newHandler = this->m_handlerFactory.createMenuRequestHandler(LoggedUser(l.userName));
		//r.newHandler = new MenuRequestHandler(this->m_handlerFactory,LoggedUser(l.userName));

		LoginResponse logResponse;
		logResponse.status = LOGIN_RESPONSE_SUCCESS;
		r.response = JsonResponsePacketSerializer::serializeResponse(logResponse);
		return r;
	}
	else
	{
		r.newHandler = this->m_handlerFactory.createLoginRequestHandler();
		LoginResponse logResponse;
		logResponse.status = LOGIN_REQUEST_FAIL;//change status to what?
		r.response = JsonResponsePacketSerializer::serializeResponse(logResponse);

		return r;
	}
	return r;

}

RequestResult LoginRequestHandler::signup(RequestInfo info)
{
	RequestResult r;
	SignupRequest s;
	std::string str = "";
	for (int i = 0; i < info.buffer.size(); i++)
	{
		str += info.buffer[i];
	}
	try
	{
		s = JsonRequestPacketDeserializer::deserializeSignupRequest(CommunicationHelper::stringToCharArr(str));
	}
	catch (const RequestError& e)
	{
		r.newHandler = nullptr;
		r.response = CommunicationHelper::createErrorResponse();
		return r;
	}
	catch (...)
	{
		r.newHandler = nullptr;
		r.response = CommunicationHelper::createErrorResponse();
		return r;
	}
	if (this->m_handlerFactory.getLoginManager().signUp(s.userName, s.password, s.email) == true)
	{
		r.newHandler = this->m_handlerFactory.createLoginRequestHandler();
		SignupResponse signResponse;
		signResponse.status = SIGNUP_RESPONSE_SUCCESS;//change status?
		r.response = JsonResponsePacketSerializer::serializeResponse(signResponse);
		return r;
	}
	else//if the user name alredyexsist
	{
		r.newHandler = this->m_handlerFactory.createLoginRequestHandler();
		SignupResponse signResponse;
		signResponse.status = SIGN_UP_REQUEST_FAIL;//change status to what?
		r.response = JsonResponsePacketSerializer::serializeResponse(signResponse);
		return r;
	}

}

