#pragma once
#include <string>

class LoggedUser
{
public:
	LoggedUser(std::string username, int roomId );
	LoggedUser(std::string name);
	std::string getUserName();
	int getRoomId();
	void setRoomId(int roomId);
private:
	std::string _userName;
	int m_roomId;
};