#pragma once
#include "Game.h"
#include "IDataBase.h"
#include "Room.h"
class GameManager
{
public:
	Game* createGame(Room room,IDataBase* db);
	Game* getGameByName(std::string name);
	void deleteGame(int gameId);
private:
	IDataBase* m_database;// why game mannger need the db?
	std::vector<Game> m_games;
	int gamesIdCounter;
};