#pragma once

#include <map>
#include <string>
#include <iostream>
#include "sqlite3.h"
#include "userDetalis.h"
#include "Question.h"
#define DB_NAME "data.db"
using std::cout;
using std::string;
using std::endl;
struct GameData;

class IDataBase
{
public:
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual int doesUserxsist(std::string username) = 0;
	virtual int doesPasswordMach(std::string username,std::string password) = 0;
	virtual int addNewUser(std::string username, std::string password,std::string email) = 0;

	virtual std::vector<Question> getQuestions(int numQuestions) = 0;
	virtual float getPlayerAverageAnswerTime(std::string playerName) = 0;
	virtual int getNumOfCorrectAnswers(std::string) = 0;
	virtual int getNumOfTotalAnswers(std::string) = 0;
	virtual int getNumOfPlayerGames(std::string playerName) = 0;
	virtual int getPlayerScore(std::string playerName) = 0;
	virtual std::vector<userDetails> getHighScores() = 0;
	
	virtual int submitGameStatistics(GameData gamedata,std::string username) = 0;

	virtual bool addQuestionToDB(std::string question,std::string rightQuestion,std::vector<std::string> wrongQuestions) =0;
};