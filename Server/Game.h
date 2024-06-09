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
	bool isAnswerCurrentQuestion;
	bool isPlayerFinishAnswerAllTheQuestions;
	GameData(Question q)// for question constructor
		: currentQuestion(q),
		correctAnswerCount(0),
		wrongAnswerCount(0),
		averageAnswerTime(0),
		isAnswerCurrentQuestion(true),//start from true
		isPlayerFinishAnswerAllTheQuestions(false) {}
};
class Game
{
public:
	Game(std::vector<Question> questions, std::vector<string> usersInRoom, IDataBase* dataBase,int GameId,string name);
	Question getQuestionForUser(string user);
	RequestResult submitAnswer(SendAnswerMessageFields userAnswer,std::string username);
	void removePlayer(string user);
	int getGameId() const;
	std::string getName() const;
	bool checkIfAllPlayersFinishToAnswer();//for game result
	std::map<string, GameData> getPlayersAndData();
	void deleteDict();

	bool checkIfAllPlayersAnsweredCurrentQuestion();
	void insertPlayer(std::string user);
private:
	void submitGameStatsToDB(GameData gamedata,std::string username);

	std::vector<Question> m_questions;
	std::map<std::string, GameData>* m_players = new std::map<std::string, GameData>();
	IDataBase* m_database;
	std::string m_gameName;
	int m_gameId;


};