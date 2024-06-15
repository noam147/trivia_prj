
#pragma once
#include "IRequestHandler.h"
#include "RequestHandleFactory.h"
#include "MenuRequestHandler.h"
#include <random>
class RequestHandleFactory;
class LoginRequestHandler : public IRequestHandler
{
public:
	~LoginRequestHandler() = default;
	LoginRequestHandler(RequestHandleFactory& handlerFactory);
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;

private:
	RequestResult login(RequestInfo info);
	RequestResult signup(RequestInfo info);
	RequestResult getEmailVerafication(RequestInfo info);
	string m_username = "";
	string m_pass = "";
	string m_email = "";
	int m_code = { 0 };
	RequestHandleFactory& m_handlerFactory;
};

