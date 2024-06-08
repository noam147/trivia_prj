#include "Room.h"

Room::Room(RoomData roomdata,LoggedUser owner): m_owner(owner)
{
	this->addUser(owner);//the owner is also  in room..
	this->m_metadata = roomdata;
}

void Room::addUser(LoggedUser user)
{
	this->m_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	for (auto it = this->m_users.begin(); it != this->m_users.end(); it++)
	{
		if (it->getUserName() == user.getUserName())
		{
			this->m_users.erase(it);
			return;
		}
	}
}

std::vector<std::string> Room::getAllUsers()
{
	
	std::vector<std::string> users;
	for (auto it = this->m_users.begin(); it != this->m_users.end(); it++)
	{
		users.push_back(it->getUserName());
	}
	return users;
}

RoomData Room::getRoomData()
{
	return this->m_metadata;
}

void Room::startGame(LoggedUser user)
{
	if (this->m_owner.getUserName() == user.getUserName())
	{
		this->m_metadata.isActive = true;
	}
	
}
