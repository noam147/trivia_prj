#pragma once
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo info) override;//func check if msg is sign in or login type of msg
	RequestResult handleRequest(RequestInfo info) override;//need to fix
};

