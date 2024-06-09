#include "RequestHandleFactory.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "GameRequestHandler.h"
RequestHandleFactory::RequestHandleFactory():m_StatisticsManager(m_database)
{
	this->m_database = new SqliteDataBase();
	m_database->open();
	m_StatisticsManager.setDataBase(m_database);
}

LoginRequestHandler* RequestHandleFactory::createLoginRequestHandler()
{
	LoginRequestHandler* l = new LoginRequestHandler(*this);
	return l;
}

LoginManager& RequestHandleFactory::getLoginManager()
{
	return this->m_loginManager;
}

MenuRequestHandler* RequestHandleFactory::createMenuRequestHandler(LoggedUser user)
{
	MenuRequestHandler* m = new MenuRequestHandler(*this,user);
	return m;
}

StatisticsManager& RequestHandleFactory::getStatisticsManager()
{
	return this->m_StatisticsManager;
}

RoomManager& RequestHandleFactory::getRoomManager()
{
	return this->m_roomManager;
}

RoomRequestHandler* RequestHandleFactory::createRoomAdminRequestHandler(LoggedUser user, Room& room)
{
	RoomRequestHandler* roomAdmin = new RoomAdminRequestHandler(user,room,*this);
	//IRequestHandler* i = roomAdmin;
	return roomAdmin;
}

RoomRequestHandler* RequestHandleFactory::createRoomMemberRequestHandler(LoggedUser user, Room& room)
{
	try
	{
		RoomRequestHandler* roomMember = new RoomMemberRequestHandler(user, room, *this);
		return roomMember;
	}
	catch (...)
	{
		return new RoomRequestHandler(user,room,*this);
	}
	
}

GameRequestHandler* RequestHandleFactory::createGameRequestHandler(LoggedUser user)
{
	//here game does not get the valuesfrom gamr infunction
	//throw RequestError();//until be fixed...

	Game* g = this->m_gameManager.createGame(this->m_roomManager.getRoom(user.getRoomId()),this->m_database);//check the get room id
	GameRequestHandler* game = new GameRequestHandler(*this,*g,user, this->m_roomManager.getRoom(user.getRoomId()).getRoomData().timePerQuestion);
	return game;
}

GameRequestHandler* RequestHandleFactory::createGameRequestHandler(LoggedUser user, string roomName)
{
	Game* g = this->m_gameManager.getGameByName(this->m_roomManager.getRoomByName(roomName).getRoomData().name);
	if (g == nullptr)
	{
		throw RequestError();
	}
	
	g->insertPlayer(user.getUserName());

	GameRequestHandler* game = new GameRequestHandler(*this, *g, user,this->m_roomManager.getRoomByName(roomName).getRoomData().timePerQuestion);
	
	return game;
}

GameManager& RequestHandleFactory::getGameManager()
{
	return this->m_gameManager;
}

void RequestHandleFactory::addQuestionToDB(AddQuestionToDB add)
{
	
	this->m_database->addQuestionToDB(add.question,add.rightAnswer,add.answers);
}
