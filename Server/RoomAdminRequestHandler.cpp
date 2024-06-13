#include "RoomAdminRequestHandler.h"
#include "RequestHandleFactory.h"
#include "IRequestHandler.h"
/*
RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo request)
{
    return RequestResult();
}*/

RoomAdminRequestHandler::~RoomAdminRequestHandler()
{
	this->closeRoom(RequestInfo());
	//this->m_handlerFactory.getLoginManager().logOut(this->m_user.getUserName());
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info)
{
	char a = info.buffer[0];
	switch (a) {
	case GET_ROOM_STATE_REQUEST:
		return this->getRoomState(info);
		break;
	case START_GAME_REQUEST:
		return this->startGame(info);
		break;
	case CLOSE_ROOM_REQUEST:
		return this->closeRoom(info);
		break;
	case KICK_REQUEST:
		return this->kickPlayer(info);
	default:
		throw RequestError();
	}
    return RequestResult();
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo request)
{

	char codeMsg = request.buffer[0];
	if (codeMsg == CLOSE_ROOM_REQUEST || codeMsg == START_GAME_REQUEST || codeMsg == GET_ROOM_STATE_REQUEST||codeMsg == KICK_REQUEST)
		return true;
	return false;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo request)
{
	RequestResult r;
	this->m_user.setRoomId(this->m_room.getRoomData().id);
	r.newHandler = (IRequestHandler*)m_handlerFactory.createGameRequestHandler(this->m_user);//replace to game handler
	this->m_room.startGame(this->m_user);//room active - game started
	r.response = JsonResponsePacketSerializer::serializeResponse(START_GAME_RESPONSE_SUCCESS);
	return r;
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo request)
{
	//send to eveyone - room destroyed
	std::vector<std::string> players = this->m_room.getAllUsers();
	this->m_handlerFactory.getRoomManager().deleteRoom(this->m_handlerFactory.getRoomManager().getIdOfRoom(this->m_room));
	RequestResult r;
	this->m_user.setRoomId(-1);
	r.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
	r.response = JsonResponsePacketSerializer::serializeResponse(CLOSE_ROOM_RESPONSE_SUCCESS);
	//now again the user is without room
	return r;
}

RequestResult RoomAdminRequestHandler::kickPlayer(RequestInfo request)
{
	std::string msg = "";
	for (char ch : request.buffer)
		msg += ch;
	
	string user = JsonRequestPacketDeserializer::deserializeKickPlayerRequest(msg).playerToKick;//user to kick
	this->m_room.removeUser(user);

	return RequestResult();
}

