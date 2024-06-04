#pragma once
#include "Question.h"
#include <map>
#include "LoggedUser.h"
#include "IDataBase.h"
#include "IRequestHandler.h"
#include "JsonResponsePacketSerializer.h"

struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averageAnswerTime;
	GameData(Question q)// for question constructor
		: currentQuestion(q),  
		correctAnswerCount(0),
		wrongAnswerCount(0),
		averageAnswerTime(0) {}
};
class Game
{
public:
	Game(std::vector<Question> questions, std::vector<string> usersInRoom, IDataBase* dataBase,int GameId);
	Question getQuestionForUser(string user);
	RequestResult submitAnswer(SendAnswerMessageFields userAnswer,std::string username);
	void removePlayer(string user);
private:
	void submitGameStatsToDB(GameData gamedata,std::string username);

	std::vector<Question> m_questions;
	std::map<string, GameData> m_players;
	IDataBase* m_database;
	int m_gameId;


};