
#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandleFactory& handlerFactory):m_handlerFactory(handlerFactory)
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.buffer[0] == LOGIN_REQUEST || info.buffer[0] == SIGN_UP_REQUEST||info.buffer[0] == EMAIL_VERAFICATION_REQUEST)
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
		else if (info.buffer[0] == EMAIL_VERAFICATION_REQUEST)
		{
			return this->getEmailVerafication(info);
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
	if (this->m_handlerFactory.getLoginManager().isUserExsist(s.userName) == false)
	{
		//here we change it to email verf
		this->m_email = s.email;
		this->m_pass = s.password;
		this->m_username = s.userName;
		std::mt19937 rng(static_cast<unsigned long>(std::time(nullptr)));
		std::uniform_int_distribution<std::mt19937::result_type> distribution(100000, 999999);
		this->m_code = distribution(rng);
		SignupResponse signResponse;
		r.newHandler = nullptr;
		signResponse.status = SIGNUP_RESPONSE_SUCCESS;
		r.response = JsonResponsePacketSerializer::serializeResponse(signResponse);
		string msg = "python emailSendVerafication.py " + this->m_email + " "+std::to_string(m_code);
		system(msg.c_str());//unsafe!
		return r;//do not sign up right now
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

RequestResult LoginRequestHandler::getEmailVerafication(RequestInfo info)
{
	if (m_code == 0)
	{
		throw RequestError();//still didnt get signup msg
	}
	RequestResult r;
	r.newHandler = nullptr;
	r.response = JsonResponsePacketSerializer::serializeResponse(SIGN_UP_REQUEST_FAIL);
	int code = 0;
	string msg = "";
	for (char ch : info.buffer)
		msg += ch;
	code = JsonRequestPacketDeserializer::deserializeEmailVerRequest(msg);
	if (this->m_code == code)
	{
		this->m_handlerFactory.getLoginManager().signUp(m_username, m_pass, m_email);
		r.response = JsonResponsePacketSerializer::serializeResponse(EMAIL_SUCCSEES);
	}
	return r;
}

