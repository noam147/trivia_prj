#include "GameManager.h"

Game* GameManager::createGame(Room room,IDataBase* db)
{
	this->m_database = db;
	gamesIdCounter++;
	room.getAllUsers();
	Game* g = new Game(this->m_database->getQuestions(room.getRoomData().numOfQuestionsInGame), room.getAllUsers(), this->m_database,this->gamesIdCounter,room.getRoomData().name);
	m_games.push_back(*g);
	return g;
}

Game* GameManager::getGameByName(std::string name)
{
	for (auto it = this->m_games.begin(); it != this->m_games.end(); it++)
	{
		if (it->getName() == name)
		{
			return &(*it);
		}
	}
	return nullptr;
}

void GameManager::deleteGame(int gameId)
{
	for (auto it = this->m_games.begin(); it != this->m_games.end(); it++)
	{
		if (it->getGameId() == gameId)
		{
			this->m_games.erase(it);
			return;
		}
	}
}
