#include "GameManager.h"

Game* GameManager::createGame(Room room,IDataBase* db)
{
	this->m_database = db;
	gamesIdCounter++;
	room.getAllUsers();
	Game* g = new Game(this->m_database->getQuestions(room.getRoomData().numOfQuestionsInGame), room.getAllUsers(), this->m_database,this->gamesIdCounter);
	m_games.push_back(*g);
	return g;
}

void GameManager::deleteGame(int gameId)
{
	for (auto it = this->m_games.begin(); it != this->m_games.end(); it++)
	{

		//it->
	}
}
