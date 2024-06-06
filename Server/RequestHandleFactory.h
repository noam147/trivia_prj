#pragma once

#include "IRequestHandler.h"
#include "SqliteDataBase.h"
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "StatisticsManager.h"

class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;
//class RoomRequestHandler;
#include "RoomRequestHandler.h"
#include "MenuRequestHandler.h"
#include "GameManager.h" 
class MenuRequestHandler;
class LoginRequestHandler;
class LoginManager; 
class GameRequestHandler;
class RequestHandleFactory
{
public:
	RequestHandleFactory();
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();

	RoomRequestHandler* createRoomAdminRequestHandler(LoggedUser user, Room& room);
	RoomRequestHandler* createRoomMemberRequestHandler(LoggedUser user, Room& room);
	
	GameRequestHandler* createGameRequestHandler(LoggedUser user);//for admin
	GameRequestHandler* createGameRequestHandler(LoggedUser user,string roomName);//for member
	GameManager& getGameManager();


	void addQuestionToDB(AddQuestionToDB add);//put this here?
private:
	LoginManager m_loginManager;
	IDataBase* m_database = new SqliteDataBase();
	RoomManager m_roomManager;
	StatisticsManager m_StatisticsManager;
	GameManager m_gameManager;



};

