#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string username, int roomId)
{
	_userName = username;
	m_roomId = roomId;
}

LoggedUser::LoggedUser(std::string name)
{
	_userName = name;
	m_roomId = -1;
}

 std::string LoggedUser::getUserName()
{
	return _userName;
}

int LoggedUser::getRoomId() {
	return m_roomId;
}

void LoggedUser::setRoomId(int roomId)
{
	m_roomId = roomId;
}
