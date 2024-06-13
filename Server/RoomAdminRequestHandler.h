#pragma once
#include "RoomRequestHandler.h"

class RoomAdminRequestHandler :public RoomRequestHandler
{
public:
	RoomAdminRequestHandler(LoggedUser& user, Room& room, RequestHandleFactory& handlerFactory) :RoomRequestHandler(user, room, handlerFactory)
	{
	}
	~RoomAdminRequestHandler();
	RequestResult handleRequest(RequestInfo request) override;
	bool isRequestRelevant(RequestInfo request) override;
private:
	RequestResult startGame(RequestInfo request);
	RequestResult closeRoom(RequestInfo request);
	RequestResult kickPlayer(RequestInfo request);
	RequestResult banPlayer(RequestInfo request);
};