#pragma once

#include "IRequestHandler.h"
class RequestHandleFactory;
//#include "RequestHandleFactory.h"

class RoomRequestHandler :public IRequestHandler
{
public:
	~RoomRequestHandler();
	RoomRequestHandler(LoggedUser user, Room& room, RequestHandleFactory& handlerFactory);
	virtual bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo info) override;
	RequestResult getRoomState(RequestInfo request);
protected:
	Room& m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandleFactory& m_handlerFactory;

};