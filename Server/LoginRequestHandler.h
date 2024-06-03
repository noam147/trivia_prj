
#pragma once
#include "IRequestHandler.h"
#include "RequestHandleFactory.h"
#include "MenuRequestHandler.h"
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
	RequestHandleFactory& m_handlerFactory;
};

