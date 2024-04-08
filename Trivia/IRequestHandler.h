#pragma once
#include <ctime>
#include <vector>
#include "CommunicationHelper.h"
#include "JsonRequestPacketDeserializer.h"
struct RequestResult;//declare struct here
struct RequestInfo {
	int id;//request id
	std::time_t receivalTime;
	std::vector<char> buffer;

};
class IRequestHandler
{
	virtual bool isRequestRelevant(RequestInfo info) =0;
	virtual RequestResult handleRequest(RequestInfo info) =0;
};

struct RequestResult//actualize struct here
{
	char* response;
	IRequestHandler* newHandler;
};