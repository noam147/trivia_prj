#include "LoginManager.h"



LoginManager::LoginManager()
{
	this->m_dataBase->open();
}

bool LoginManager::signUp(std::string username, std::string password, std::string email)
{
	if (m_dataBase->doesUserxsist(username))
	{
		return false;//throw error
	}
	else
	{
		return this->m_dataBase->addNewUser(username, password, email);//if the adding done good- returns true
	}
	return true;
}

bool LoginManager::logIn(std::string username, std::string password)
{
	
	if (m_dataBase->doesUserxsist(username) == MACH && m_dataBase->doesPasswordMach(username, password) == MACH)
	{
		for (int i = 0; i < m_loggedUsers.size(); i++)//user can not be connected from two windows at the same time
		{
			if (m_loggedUsers[i].getUserName() == username)
			{
				return false;
			}
		}
		m_loggedUsers.push_back(LoggedUser(username,-1));
		return true;
	}
	else
	{
		return false;
	}
	return true;
}

void LoginManager::logOut(std::string username)
{
	for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); it++)
	{
		if (it->getUserName() == username)
		{
			m_loggedUsers.erase(it);
			return;
		}
	}
}

bool LoginManager::isUserExsist(std::string username)
{
	return m_dataBase->doesUserxsist(username);
}
