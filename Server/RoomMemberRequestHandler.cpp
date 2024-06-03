#include "RoomMemberRequestHandler.h"
#include "RequestHandleFactory.h"

/*
RoomMemberRequestHandler::~RoomMemberRequestHandler()
{
	this->leaveRoom(RequestInfo());
}*/

RoomMemberRequestHandler::~RoomMemberRequestHandler()
{
	this->leaveRoom(RequestInfo());
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo request)
{
	char codeMsg = request.buffer[0];
	if (codeMsg == LEAVE_ROOM_REQUEST || codeMsg == GET_ROOM_STATE_REQUEST)
		return true;
	return false;
}
RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info)
{
	char a = info.buffer[0];
	switch (a) {
	case GET_ROOM_STATE_REQUEST:

		//need to check - can be errors in here.. 
		return this->getRoomState(info);
		break;
	case LEAVE_ROOM_REQUEST:
		return this->leaveRoom(info);
		break;
	default:
		throw RequestError();
	}
	return RequestResult();
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo request)
{

	this->m_room.removeUser(this->m_user);
	this->m_user.setRoomId(-1);
	RequestResult r;
	r.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUserName());
	r.response = JsonResponsePacketSerializer::serializeResponse(LEAVE_ROOM_RESPONSE_SUCCESS);
	return r;
}
