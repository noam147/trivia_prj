#include "MenuRequestHandler.h"

MenuRequestHandler::~MenuRequestHandler()
{
	std::cout << "Deleting user" << std::endl;

	if (m_user.getRoomId() != -1)
		m_handlerFactory.getRoomManager().getRoom(m_user.getRoomId()).removeUser(m_user);
	this->m_handlerFactory.getLoginManager().logOut(m_user.getUserName());
}

MenuRequestHandler::MenuRequestHandler(RequestHandleFactory& handlerFactory, LoggedUser user) :m_handlerFactory(handlerFactory),m_user(user)
{
	this->m_handlerFactory.getStatisticsManager();
	
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
    char msgType = info.buffer[0];
    if (msgType == LOGOUT_REQUEST || msgType == GET_ROOM_REQUEST
        || msgType == GET_PERSONAL_STAT_REQUEST || msgType == GET_HIGH_SCORE_REQUEST || msgType == JOIN_ROOM_REQUEST
        || msgType == CREATE_ROOM_REQUEST|| msgType == GET_ADD_QUESTION_CODE||msgType == GET_PLAYER_IN_ROOM_REQUEST)
        return true;

    return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo info)
{
	char a = info.buffer[0];
	switch (info.buffer[0]) {
	case LOGOUT_REQUEST:
		return this->signout(info);
		break;
	case GET_ROOM_REQUEST:
		return this->getRooms(info);
		break;
	case GET_PLAYER_IN_ROOM_REQUEST:
		return this->getPlayersInRoom(info);
		break;
	case GET_PERSONAL_STAT_REQUEST:
		return this->getPlayerStats(info);
		break;
	case GET_HIGH_SCORE_REQUEST:
		return this->getPlayerHighscore(info);
		break;
	case JOIN_ROOM_REQUEST:
		return this->joinRoom(info);
		break;
	case CREATE_ROOM_REQUEST:
		return this->createRoom(info);
		break;
	case GET_ADD_QUESTION_CODE:
		return this->addQuestion(info);
		break;
	default:
		throw RequestError();
	}
}

RequestResult MenuRequestHandler::signout(RequestInfo info)
{
    RequestResult r;
    r.newHandler = new LoginRequestHandler(this->m_handlerFactory);
    LogoutResponse l;
    l.status = 1;
    r.response = JsonResponsePacketSerializer::serializeResponse(l);
	this->m_handlerFactory.getLoginManager().logOut(m_user.getUserName());//log out from the active users
    return r;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
    RequestResult r;
    //r.newHandler = new MenuRequestHandler(this->m_handlerFactory, this->m_user.getUserName());
	r.newHandler = nullptr;
    GetRoomResponse gr;
    gr.roomList = this->m_handlerFactory.getRoomManager().getRooms();
    r.response = JsonResponsePacketSerializer::serializeResponse(gr);
    return r;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo info)
{
	RequestResult r;
	GetPlayersRequest gprRequest;
	std::string str = "";

	for (int i = 0; i < info.buffer.size(); i++)
	{
		str += info.buffer[i];
	}
	try
	{
		gprRequest = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(CommunicationHelper::stringToCharArr(str));
	}
	catch (const RequestError& e)
	{
		r.newHandler = nullptr;
		r.response = CommunicationHelper::createErrorResponse();
		return r;
	}
	catch (...)
	{
		r.newHandler = nullptr;
		r.response = CommunicationHelper::createErrorResponse();
		return r;
	}

	//r.newHandler = new MenuRequestHandler(this->m_handlerFactory, this->m_user.getUserName());
	r.newHandler = nullptr;

	GetPlayersInRoomResponse gprResponse;
	gprResponse.userNames = this->m_handlerFactory.getRoomManager().getRoom(gprRequest.roomId).getAllUsers();
	r.response = JsonResponsePacketSerializer::serializeResponse(gprResponse);
	return r;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
	RequestResult r;
	JoinRoomRequest jrRequest;
	std::string str = "";

	for (int i = 0; i < info.buffer.size(); i++)
	{
		str += info.buffer[i];
	}
	try
	{
		jrRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(CommunicationHelper::stringToCharArr(str));
	}
	catch (const RequestError& e)
	{
		r.newHandler = nullptr;
		r.response = CommunicationHelper::createErrorResponse();
		return r;
	}
	catch (...)
	{
		r.newHandler = nullptr;
		r.response = CommunicationHelper::createErrorResponse();
		return r;
	}
	//to check if fer cuase problems and need an address
	
	Room& roomToJoin = this->m_handlerFactory.getRoomManager().getRoomByName(jrRequest.roomname);
	//Room* roomToJoin =&( this->m_handlerFactory.getRoomManager().getRoomByName(jrRequest.roomname));
	if (roomToJoin.getAllUsers().size() >= roomToJoin.getRoomData().maxPlayers)
	{
		r.newHandler = nullptr;
		r.response = CommunicationHelper::createErrorResponse();
		return r;
	}
	this->m_user.setRoomId(roomToJoin.getRoomData().id);
	roomToJoin.addUser(this->m_user);
	r.newHandler = this->m_handlerFactory.createRoomMemberRequestHandler(m_user,roomToJoin);
	JoinRoomResponse jrResponse;
	jrResponse.status = 1;
	r.response = JsonResponsePacketSerializer::serializeResponse(jrResponse);
	return r;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
	RequestResult r;
	CreateRoomRequest crRequest;
	std::string str = "";

	for (int i = 0; i < info.buffer.size(); i++)
	{
		str += info.buffer[i];
	}
	try
	{
		crRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(CommunicationHelper::stringToCharArr(str));
	}
	catch (const RequestError& e)
	{
		r.newHandler = nullptr;
		r.response = CommunicationHelper::createErrorResponse();
		return r;
	}
	catch (...)
	{
		r.newHandler = nullptr;
		r.response = CommunicationHelper::createErrorResponse();
		return r;
	}

	unsigned int id = 1;
	if (!(this->m_handlerFactory.getRoomManager().getRooms().empty())) {
		id = this->m_handlerFactory.getRoomManager().getRooms().back().id;
	}


	RoomData rd = { id, crRequest.roomName, crRequest.maxUsers, crRequest.questionCount, crRequest.questionTimeout, 0 };
	
	rd.name = crRequest.roomName;

		std::vector<RoomData> roomsData = this->m_handlerFactory.getRoomManager().getRooms();
		for (auto it = roomsData.begin(); it != roomsData.end(); it++)
		{
			if (it->name == rd.name)
			{
				r.newHandler = nullptr;
				ErrorResponse err;
				err.message = "there is alredy room with that name";
				r.response = JsonResponsePacketSerializer::serializeResponse(err);
				return r;
			}
		}
	
	
	Room* room2 = new Room(this->m_handlerFactory.getRoomManager().createRoom(this->m_user, rd));//had to use new to keep the class activated
	//add the adminin room constructor
	this->m_user.setRoomId(rd.id);//set the room id of user
	r.newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(m_user, *room2);
	//r.newHandler = new MenuRequestHandler(this->m_handlerFactory, this->m_user.getUserName());//delete this when finish write room admin class
	CreateRoomResponse crResponse;
	crResponse.status = 1;
	r.response = JsonResponsePacketSerializer::serializeResponse(crResponse);
	return r;
}

RequestResult MenuRequestHandler::getPlayerHighscore(RequestInfo info)
{
	RequestResult r;
	GetHighScoreResponse hsResponse = { this->m_handlerFactory.getStatisticsManager().getHighScore() };
	r.newHandler = new MenuRequestHandler(this->m_handlerFactory, this->m_user.getUserName());
	//r.newHandler = nullptr;
	r.response = JsonResponsePacketSerializer::serializeResponse(hsResponse);
	return r;
}

RequestResult MenuRequestHandler::getPlayerStats(RequestInfo info)
{
	RequestResult r;
	GetPlayerStatisticsResponse hsResponse = {this->m_handlerFactory.getStatisticsManager().getUserStatistics(this->m_user.getUserName())};
	//r.newHandler = new MenuRequestHandler(this->m_handlerFactory, this->m_user.getUserName());
	r.newHandler = nullptr;
	r.response = JsonResponsePacketSerializer::serializeResponse(hsResponse);


	for (size_t i = 0; i < 10; i++)
	{
		std::cout << r.response[i];
	}
	std::cout << "\n";
	return r;
}

RequestResult MenuRequestHandler::addQuestion(RequestInfo info)
{
	string msg = "";
	RequestResult r;
	for (int i = 0; i < info.buffer.size(); i++)
	{
		msg += info.buffer[i];
	}

	AddQuestionToDB question = JsonRequestPacketDeserializer::deserializeAddQuestionRequest(CommunicationHelper::stringToCharArr(msg));
	this->m_handlerFactory.addQuestionToDB(question);//add to db
	r.newHandler = nullptr;
	r.response = JsonResponsePacketSerializer::serializeResponse(GET_ADD_QUESTION_CODE_SUCCESS);
	return r;
}
