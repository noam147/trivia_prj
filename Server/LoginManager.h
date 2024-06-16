#pragma once
#include "LoggedUser.h"
#include "SqliteDataBase.h"
#include <vector>
class LoginManager
{
public:
	LoginManager();
	bool signUp(std::string username, std::string password, std::string email);
	bool logIn(std::string username, std::string password);
	void logOut(std::string username);
	bool isUserExsist(std::string username);
private:
	IDataBase* m_dataBase = new SqliteDataBase;
	std::vector<LoggedUser> m_loggedUsers;
};