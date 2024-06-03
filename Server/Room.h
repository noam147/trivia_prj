#pragma once
#include "LoggedUser.h"
#include <vector>
struct RoomData
{
	unsigned int id;
	std::string name;
	int maxPlayers;
	int numOfQuestionsInGame;
	int timePerQuestion;
	int isActive;
};
class Room
{

public:
	Room(RoomData roomdata, LoggedUser owner);
	void addUser(LoggedUser user);
	void  removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers();
	RoomData getRoomData();//add this, func wasn't in uml
	void startGame(LoggedUser user);
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
	LoggedUser m_owner; //maybe need to add?

};
