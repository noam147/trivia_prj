#include "RoomRequestHandler.h"
#include "RequestHandleFactory.h"
#include "IRequestHandler.h"
RoomRequestHandler::~RoomRequestHandler()
{
	this->m_handlerFactory.getLoginManager().logOut(this->m_user.getUserName());

	this->m_room.removeUser(m_user); 
}
RoomRequestHandler::RoomRequestHandler(LoggedUser user, Room& room, RequestHandleFactory& handlerFactory) : m_user(user), m_room(room), m_roomManager(handlerFactory.getRoomManager()), m_handlerFactory(handlerFactory)
{
	
}

bool RoomRequestHandler::isRequestRelevant(RequestInfo request)
{
	char codeMsg = request.buffer[0];
	if (codeMsg == CLOSE_ROOM_REQUEST || codeMsg == START_GAME_REQUEST || codeMsg == GET_ROOM_STATE_REQUEST)
		return true;
	/*if:
	CloseRoomRequest ?
StartGameRequest ?
GetRoomStateRequest*/
	return false;
}

RequestResult RoomRequestHandler::handleRequest(RequestInfo info)
{
	return RequestResult();
}
RequestResult RoomRequestHandler::getRoomState(RequestInfo request)
{
	try
	{
		this->m_room = this->m_handlerFactory.getRoomManager().getRoomByName(this->m_room.getRoomData().name);//set room again?
	}
	catch (RequestError e)
	{
		//for member:
		//check if admin closed room:
		RequestResult r;
		this->m_user.setRoomId(-1);
		r.newHandler = m_handlerFactory.createMenuRequestHandler(this->m_user);
		r.response = JsonResponsePacketSerializer::serializeResponse(LEAVE_ROOM_RESPONSE_SUCCESS);
		return r;
	}
	

//for member:
//check if admin closed room:
	m_user.setRoomId(this->m_room.getRoomData().id);
	//check if user got kick/ban - when he is not in room: or room doesnt exsist
	if (!this->m_roomManager.isRoomExsist(this->m_room.getRoomData().id) || !this->m_room.isUserInRoom(this->m_user.getUserName()))//if room closed
	{
		RequestResult r;
		this->m_user.setRoomId(-1);
		r.newHandler = m_handlerFactory.createMenuRequestHandler(this->m_user);
		r.response = JsonResponsePacketSerializer::serializeResponse(LEAVE_ROOM_RESPONSE_SUCCESS);
		return r;
	}


	//check if admin start room: (can not delete this becaue we have to get a new handler)
	if (this->m_room.getRoomData().isActive == true)
	{
		RequestResult r;
		r.newHandler = (IRequestHandler*)m_handlerFactory.createGameRequestHandler(this->m_user,this->m_room.getRoomData().name); // give the game handler to member
		r.response = JsonResponsePacketSerializer::serializeResponse(START_GAME_RESPONSE_SUCCESS);
		return r;

	}



	RoomData room = this->m_room.getRoomData();
	int roomState = this->m_roomManager.getRoomState(room.id);
	//CloseRoomResponse;
	//GetRoomResponse getroom;
	GetRoomStateResponse roomDetails;

	roomDetails.players = m_room.getAllUsers();
	roomDetails.hasGameBegun = room.isActive;//if game started
	roomDetails.AnswerCount = room.numOfQuestionsInGame;
	roomDetails.status = roomState;//what this is should be?
	roomDetails.AnswerTimeOut = room.timePerQuestion;
	
	RequestResult r;

	r.response = JsonResponsePacketSerializer::serializeResponse(roomDetails);
	r.newHandler = nullptr;
	return r;
}

