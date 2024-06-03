#pragma once

#include "RoomRequestHandler.h"
class RoomMemberRequestHandler : public RoomRequestHandler
{
public:
	RoomMemberRequestHandler(LoggedUser user, Room& room, RequestHandleFactory& handlerFactory) :RoomRequestHandler(user, room, handlerFactory)
	{

	}
	~RoomMemberRequestHandler();

	bool isRequestRelevant(RequestInfo request) override;
	RequestResult handleRequest(RequestInfo request) override;

private:
	RequestResult leaveRoom(RequestInfo request);
};