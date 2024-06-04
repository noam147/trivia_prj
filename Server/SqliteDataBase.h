#pragma once
#include "IDataBase.h"
#include <fstream>
#include<algorithm>
#define MACH 5//result of sucsess
#define FAIL 0
#define CORRECT 20
#define WRONG 10



class SqliteDataBase:public IDataBase//maybe put mutex when i accsses the file - id the _db opening the file after it opened at the first time?
{
public:
	void insertUserToStatistic(string username,float avgAnswer,int correct,int totalAnswers,int numGames);
	void clearDB();
	bool open() override;
	bool close() override;
	int doesUserxsist(std::string username) override;
	int doesPasswordMach(std::string username, std::string password) override;
	int addNewUser(std::string username, std::string password, std::string email) override;
	bool createTables();
	void printTables();

	std::vector<Question> getQuestions(int numQuestions) override;
	float getPlayerAverageAnswerTime(std::string playerName) override;
	int getNumOfCorrectAnswers(std::string playerName) override;
	int getNumOfTotalAnswers(std::string playerName) override;
	int getNumOfPlayerGames(std::string playerName) override;
	int getPlayerScore(std::string playerName) override;
	std::vector<userDetails> getHighScores() override;

	int submitGameStatistics(GameData gamedata, std::string username) override;
	bool addQuestionToDB(std::string question, std::string rightQuestion, std::vector<std::string> wrongQuestions) override;
	
private:
	bool createUsersTable();
	bool createStatisticsTable();
	bool createQuestionsTable();


	void setNumberOfGames(int num,std::string username);
	void setPlayerAverageAnswerTime(float time,std::string username);
	void setNumOfCorrectAnswers(int num,std::string username);
	void setNumOfTotalAnswers(int num, std::string username);

	static bool execSqlCommand(const char* sqlStatement, sqlite3* db);
	static int helpFindPassword(void* data, int argc, char** argv, char** azColName);
	static int helpFindUser(void* data, int argc, char** argv, char** azColName);
	static int helpPrint(void* data, int argc, char** argv, char** azColName);

	static int getPlayerAverageAnswerTime(void* data, int argc, char** argv, char** azColName);
	static int getNumOfCorrectAnswers(void* data, int argc, char** argv, char** azColName);
	static int getNumOfTotalAnswers(void* data, int argc, char** argv, char** azColName);
	static int getNumOfPlayerGames(void* data, int argc, char** argv, char** azColName);
	static int getHighScores(void* data, int argc, char** argv, char** azColName);
	static int helpGetQuestions(void* data, int argc, char** argv, char** azColName);

	static bool sortScores(userDetails u1,userDetails u2);
	bool sortStringScores(string u1, string u2);
	void insertExampleOfQuestionsForStart();
	
	int helpGetPlayerInfo(string playername,string functoActivate);
	sqlite3* _db;
};