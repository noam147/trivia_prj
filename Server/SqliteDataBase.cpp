#include "SqliteDataBase.h"
#include "Game.h"//gamedata

/*	const char* sqlStatement = "create table statistics (\
	username TEXT NOT NULL,\
	numberOfGames INTEGER,\
	numberOfAnswers INTEGER,\
	numberOfRightAnswers INTEGER,\
	avgTimeForAnswer REAL\);";//real is float
	bool flag = execSqlCommand(sqlStatement, _db);
	return flag;*/
void SqliteDataBase::insertUserToStatistic(string username,float avgAnswer, int correct, int totalAnswers, int numGames)
{
	string str = "INSERT INTO statistics (username,numberOfGames,numberOfAnswers,numberOfRightAnswers,avgTimeForAnswer) VALUES ('" + username + "', '" + std::to_string(numGames) + "', '" + std::to_string(totalAnswers) + "', '" + std::to_string(correct) + "', '" + std::to_string(avgAnswer) +"'); ";
	const char* sqlStatement = str.c_str();
	cout << sqlStatement << "\n";
	bool flag = execSqlCommand(sqlStatement, _db);
}

void SqliteDataBase::clearDB()
{
	close();
	std::ofstream file(DB_NAME);
	file << "";
	file.close();
}

bool SqliteDataBase::open()
{
	bool flag = false;
	std::ifstream file(DB_NAME);
	if (file.is_open() && file.peek() != std::ifstream::traits_type::eof())//if file is good
	{
		file.close();
	}
	else
	{
		flag = true;
		file.close();
		//std::cout << "file is not exsist or empty - continue\n";
		
		
	}
	int res = sqlite3_open(DB_NAME, &_db);
	if (res != SQLITE_OK)
	{
		cout << "ho no\n";
	}
	if (flag)
	{
		createTables();
	}
	
	return res;
}

bool SqliteDataBase::close()
{
	sqlite3_close(_db);
	return false;
}

int SqliteDataBase::doesUserxsist(std::string username)
{
	printTables();
	string curr = username;
	string str = "select * from USERS;";
	char* errMessage = nullptr;
	const char* sqlStatement = str.c_str();
	try
	{
		int res = sqlite3_exec(_db, sqlStatement, SqliteDataBase::helpFindUser, &username, &errMessage);
		if (strcmp(curr.c_str(), username.c_str()) != 0)
		{
			return MACH;
		}
	}
	catch (...)
	{

	}
	return 0;
}

int SqliteDataBase::doesPasswordMach(std::string username, std::string password)
{
	//printTables();
	std::string curr = password;
	string str = "select * from USERS where password = '" +password+ "' and username = '"+username+"'; ";
	cout << str<<"\n";
	char* errMessage = nullptr;
	const char* sqlStatement = str.c_str();
	try
	{
		int res = sqlite3_exec(_db, sqlStatement,SqliteDataBase::helpFindPassword, &password, &errMessage);
		if (strcmp(curr.c_str(), password.c_str()) != 0)
		{
			return MACH;
		}
	}
	catch (...)
	{

	}
	return 0;
}

int SqliteDataBase::addNewUser(std::string username, std::string password, std::string email)
{

	string str = "INSERT INTO USERS (username,password,email) VALUES ('" + username + "', '" + password + "', '" + email + "'); ";
	const char* sqlStatement = str.c_str();
	cout << sqlStatement << "\n";
	bool flag = execSqlCommand(sqlStatement, _db);

	this->insertUserToStatistic(username,0,0,0,0);
	return flag;
}

bool SqliteDataBase::createTables()
{
	bool flag = true;
	flag = this->createUsersTable();
	flag = this->createStatisticsTable()&&flag;
	flag =  this->createQuestionsTable()&&flag;
	return flag;
}

void SqliteDataBase::printTables()
{
	string str = "select * from USERS;";
	char* errMessage = nullptr;
	const char* sqlStatement = str.c_str();
	try
	{
		int res = sqlite3_exec(_db, sqlStatement, SqliteDataBase::helpPrint, nullptr, &errMessage);
	}
	catch (...)
	{

	}
	cout << "finish printusers\n";
	str = "select * from questions;";
	const char* sqlStatement2 = str.c_str();
	try
	{
		int res = sqlite3_exec(_db, sqlStatement2, SqliteDataBase::helpPrint, nullptr, &errMessage);
	}
	catch (...)
	{

	}
	cout << "finish print questions\n";

	str = "select * from statistics;";
	const char* sqlStatement3 = str.c_str();
	try
	{
		int res = sqlite3_exec(_db, sqlStatement3, SqliteDataBase::helpPrint, nullptr, &errMessage);
	}
	catch (...)
	{

	}
	cout << "finish print statistics\n";
}

std::vector<Question> SqliteDataBase::getQuestions(int numQuestions)
{
	string str = "select * from questions order by RANDOM() limit "+std::to_string(numQuestions)+";";
	cout << str << "\n";
	std::vector<Question> questions;
	char* errMessage = nullptr;
	const char* sqlStatement = str.c_str();
	try
	{
		int res = sqlite3_exec(_db, sqlStatement, SqliteDataBase::helpGetQuestions, &questions, &errMessage);
		if (errMessage)
		{
			cout << errMessage << "\n";
		}
	}
	catch (...)
	{

	}
	cout << "finish print\n";
	return questions;
}

float SqliteDataBase::getPlayerAverageAnswerTime(std::string playerName)
{
	std::string curr = playerName;
	float avg = -1;
	string str = "select * from statistics where username = '" + playerName + "'; ";
	cout << str << "\n";
	char* errMessage = nullptr;
	const char* sqlStatement = str.c_str();
	try
	{
		int res = sqlite3_exec(_db, sqlStatement, SqliteDataBase::getPlayerAverageAnswerTime, &avg, &errMessage);
		if (avg != -1)
		{
			return avg;
		}
	}
	catch (...)
	{

	}
	return FAIL;
}

int SqliteDataBase::getNumOfCorrectAnswers(std::string playerName)
{
	int numCorrectAnswers = -1;
	string str = "select * from statistics where username = '" + playerName + "'; ";
	cout << str << "\n";
	char* errMessage = nullptr;
	const char* sqlStatement = str.c_str();
	try
	{
		int res = sqlite3_exec(_db, sqlStatement, SqliteDataBase::getNumOfCorrectAnswers, &numCorrectAnswers, &errMessage);
		if (numCorrectAnswers != -1)
		{
			return numCorrectAnswers;
		}
	}
	catch (...)
	{

	}
	return FAIL;
}

int SqliteDataBase::getNumOfTotalAnswers(std::string playerName)
{
	int numAnswers = -1;
	string str = "select * from statistics where username = '" + playerName + "'; ";
	cout << str << "\n";
	char* errMessage = nullptr;
	const char* sqlStatement = str.c_str();
	try
	{
		int res = sqlite3_exec(_db, sqlStatement, SqliteDataBase::getNumOfTotalAnswers, &numAnswers, &errMessage);
		if (numAnswers != -1)
		{
			return numAnswers;
		}
	}
	catch (...)
	{

	}
	return FAIL;
}

int SqliteDataBase::getNumOfPlayerGames(std::string playerName)
{
	int playerGames = -1;
	string str = "select * from statistics where username = '" + playerName + "'; ";
	cout << str << "\n";
	char* errMessage = nullptr;
	const char* sqlStatement = str.c_str();
	try
	{
		int res = sqlite3_exec(_db, sqlStatement, SqliteDataBase::getNumOfPlayerGames, &playerGames, &errMessage);
		if (playerGames != -1)
		{
			return playerGames;
		}
	}
	catch (...)
	{

	}
	return FAIL;
}

int SqliteDataBase::getPlayerScore(std::string playerName)
{
	int numAnswers = this->getNumOfTotalAnswers(playerName);
	int correctAnswers = this->getNumOfCorrectAnswers(playerName);
	int wrongAnswers = numAnswers - correctAnswers;
	if (correctAnswers * CORRECT - wrongAnswers * WRONG < 0)
	{
		return 0;
	}
	return correctAnswers * CORRECT - wrongAnswers * WRONG;

}

std::vector<userDetails> SqliteDataBase::getHighScores()
{
	//neefd to get the 5 best results
	std::vector<std::string> usersVector;
	std::vector<userDetails> topFive;
	string str = "select * from USERS;";
	cout << str << "\n";
	char* errMessage = nullptr;
	const char* sqlStatement = str.c_str();
	try
	{
		printTables();
		//int res = sqlite3_exec(_db, sqlStatement, SqliteDataBase::getHighScores,  nullptr, &errMessage);
		int res = sqlite3_exec(_db, sqlStatement, SqliteDataBase::getHighScores, &usersVector, &errMessage);
			std::map<int, string> usersScore;

			std::vector<userDetails> v2;
			for (int i = 0; i < usersVector.size(); i++)
			{
				userDetails user;
				user.score = this->getPlayerScore(usersVector[i]);
				user.user_name = usersVector[i];
				v2.push_back(user);
			}
			std::sort(v2.begin(),v2.end(),this->sortScores);
			int size = 5;
			if (v2.size() < 5)
			{
				size = v2.size();
			}
			for (int i = 0; i < size; i++)
			{
				topFive.push_back(v2[i]);
			}
		
	}
	catch (...)
	{

	}
	return topFive;
}

int SqliteDataBase::submitGameStatistics(GameData gamedata,std::string username)
{
	//the statistic is on *all* the games combined
	int sumAnswers = gamedata.correctAnswerCount + gamedata.wrongAnswerCount + this->getNumOfTotalAnswers(username);
	int sumCorrectAnswers = this->getNumOfCorrectAnswers(username) + gamedata.correctAnswerCount;
	this->getNumOfPlayerGames(username);

	//formula for sum- newTime/(sumOfGames includeing cuurent game) + sumBefore
	float avgTimeForAnswer = gamedata.averageAnswerTime / this->getNumOfPlayerGames(username) + this->getPlayerAverageAnswerTime(username);
	
	this->setNumberOfGames(this->getNumOfPlayerGames(username)+1,username);//we update this each time game ended so it will be by 1 each time
	this->setNumOfCorrectAnswers(sumCorrectAnswers, username);
	this->setNumOfTotalAnswers(sumAnswers, username);
	this->setPlayerAverageAnswerTime(avgTimeForAnswer, username);
	return 0;
}

bool SqliteDataBase::addQuestionToDB(std::string question, std::string rightAnswer, std::vector<std::string> wrongQuestions)
{
	if (wrongQuestions.size() != 3)
	{
		return false;
	}
	//to do - check if question alredy exsist
	string str = "INSERT INTO questions (question,rightanswer,wronganswer1,wronganswer2,wronganswer3) VALUES ('" + question + "', '" + rightAnswer + "', '" + wrongQuestions[0] + "', '" + wrongQuestions[1]+ "', '" + wrongQuestions[2] + +"'); ";
	const char* sqlStatement = str.c_str();
	cout << sqlStatement << "\n";
	bool flag = execSqlCommand(sqlStatement, _db);
	return flag;
}

bool SqliteDataBase::createUsersTable()
{
	const char* sqlStatement = "create table USERS (username TEXT NOT NULL,password TEXT NOT NULL,email TEXT NOT NULL);";
	bool flag = execSqlCommand(sqlStatement, _db);
	return flag;
}

bool SqliteDataBase::createStatisticsTable()
{
	const char* sqlStatement = "create table statistics (\
	username TEXT NOT NULL,\
	numberOfGames INTEGER,\
	numberOfAnswers INTEGER,\
	numberOfRightAnswers INTEGER,\
	avgTimeForAnswer REAL\);";//real is float
	bool flag = execSqlCommand(sqlStatement, _db);
	return flag;
}

bool SqliteDataBase::createQuestionsTable()
{
	
	const char* sqlStatement = "create table questions (question TEXT NOT NULL,rightanswer TEXT NOT NULL,wronganswer1 TEXT NOT NULL,wronganswer2 TEXT NOT NULL,wronganswer3 TEXT NOT NULL);";
	bool flag = execSqlCommand(sqlStatement, _db);
	this->insertExampleOfQuestionsForStart();
	return flag;
}

void SqliteDataBase::setNumberOfGames(int num,std::string username)
{
	string msg = "update statistics set numberOfGames = " + std::to_string(num) + " where username = "+username+";";
	const char* sqlStatement = msg.c_str();
	execSqlCommand(sqlStatement, _db);
}

void SqliteDataBase::setPlayerAverageAnswerTime(float time, std::string username)
{
	string msg = "update statistics set avgTimeForAnswer = " + std::to_string(time) + " where username = " + username + ";";
	const char* sqlStatement = msg.c_str();
	execSqlCommand(sqlStatement, _db);
}

void SqliteDataBase::setNumOfCorrectAnswers(int num, std::string username)
{
	string msg = "update statistics set numberOfRightAnswers = " + std::to_string(num) + " where username = " + username + ";";
	const char* sqlStatement = msg.c_str();
	execSqlCommand(sqlStatement, _db);
}

void SqliteDataBase::setNumOfTotalAnswers(int num, std::string username)
{
	string msg = "update statistics set numberOfAnswers = " + std::to_string(num) + " where username = " + username + ";";
	const char* sqlStatement = msg.c_str();
	execSqlCommand(sqlStatement, _db);
}


bool SqliteDataBase::execSqlCommand(const char* sqlStatement, sqlite3* db)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		if (errMessage)
		{
			std::cout << errMessage << "\n";
		}
	
		return false;
	}
	return true;
}

int SqliteDataBase::helpFindPassword(void* data, int argc, char** argv, char** azColName)
{
	string* password = static_cast<string*>(data);

	for (int i = 0; i < argc;i++)//should be only one username with name not multiple
	{
		if (strcmp(azColName[i], "password") == 0)
		{
			if (strcmp(argv[i], password->c_str()) == 0)
			{
				*password = ":)";
				return MACH;
			}
		}
		
	}
	return 0;
}

int SqliteDataBase::helpFindUser(void* data, int argc, char** argv, char** azColName)
{
	string* username = static_cast<string*>(data);
	for (int i = 0; i < argc; i++) {
		//cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
		if (strcmp(azColName[i], "username") == 0)
		{
			if (argv[i] == *username)
			{
				*username = ":)";
				return MACH;
			}
		}
	}
	return 0;
}

int SqliteDataBase::helpPrint(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++) {
		cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
	}
	
	return 0;
}

int SqliteDataBase::getPlayerAverageAnswerTime(void* data, int argc, char** argv, char** azColName)
{
	float* avg = static_cast<float*>(data);
	for (int i = 0; i < argc; i++) {
		//cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
		if (strcmp(azColName[i], "avgTimeForAnswer") == 0)
		{
				*avg = std::stof(argv[i]);
				return MACH;	
		}
	}
	return 0;
}

int SqliteDataBase::getNumOfCorrectAnswers(void* data, int argc, char** argv, char** azColName)
{
	int* num = static_cast<int*>(data);
	for (int i = 0; i < argc; i++) {
		//cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
		if (strcmp(azColName[i], "numberOfRightAnswers") == 0)
		{

				*num = atoi(argv[i]);
				return MACH;
			
		}
	}
	return 0;
}

int SqliteDataBase::getNumOfTotalAnswers(void* data, int argc, char** argv, char** azColName)
{
	int* num = static_cast<int*>(data);
	for (int i = 0; i < argc; i++) {
		//cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
		if (strcmp(azColName[i], "numberOfAnswers") == 0)
		{
				*num = atoi(argv[i]);
				return MACH;
		}
	}
	return 0;
}

int SqliteDataBase::getNumOfPlayerGames(void* data, int argc, char** argv, char** azColName)
{
	int* num = static_cast<int*>(data);
	for (int i = 0; i < argc; i++) {
		//cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
		if (strcmp(azColName[i], "numberOfGames") == 0)
		{

				*num = atoi(argv[i]);
				return MACH;
			
		}
	}
	return 0;
}


int SqliteDataBase::getHighScores(void* data, int argc, char** argv, char** azColName)
{
	std::vector<string>* usersVector = static_cast<std::vector<string>*>(data);
	for (int i = 0; i < argc; i++) {
		if (strcmp(azColName[i], "username") == 0)
		{
			usersVector->push_back(string(argv[i]));
		}
	}
	return 0;
}

int SqliteDataBase::helpGetQuestions(void* data, int argc, char** argv, char** azColName)
{
	std::vector<Question>* questionsVector = static_cast<std::vector<Question>*>(data);
	std::string question;
	std::vector<string> possibleAnswers;
	string rightAnswer = "";
	int rightAnswerIndex = 0;
	for (int i = 0; i < argc; i++) 
	{
		if (strcmp(azColName[i], "question") == 0)
		{
			question = argv[i];
		}
		if (strcmp(azColName[i], "rightanswer") == 0)
		{
			rightAnswer = argv[i];
			possibleAnswers.push_back(argv[i]);
		}
		if (strcmp(azColName[i], "wronganswer1") == 0)
		{
			possibleAnswers.push_back(argv[i]);
		}
		if (strcmp(azColName[i], "wronganswer2") == 0)
		{
			possibleAnswers.push_back(argv[i]);
		}
		if (strcmp(azColName[i], "wronganswer3") == 0)
		{
			possibleAnswers.push_back(argv[i]);
		}
	}
	std::sort(possibleAnswers.begin(),possibleAnswers.end());//sort alphabetecly
	for (int i=0;i<possibleAnswers.size();i++)
	{
		if (possibleAnswers[i] == rightAnswer)
		{
			rightAnswerIndex = i;
		}
	}
	questionsVector->push_back(Question(question, possibleAnswers, rightAnswerIndex));
	return 0;
}

bool SqliteDataBase::sortScores(userDetails u1, userDetails u2)
{
	return (u1.score > u2.score);
}

bool SqliteDataBase::sortStringScores(string u1, string u2)
{
	return (this->getPlayerScore(u1) < this->getPlayerScore(u2));
}

void SqliteDataBase::insertExampleOfQuestionsForStart()
{
	std::vector<string> v;
	v.push_back("2");
	v.push_back("3");
	v.push_back("123");
	this->addQuestionToDB("1+1 = ?","11",v);
	v.clear();
	v.push_back("High Transfer Text Protocol");
	v.push_back("Hyperlinking Text Transfer Protocol");
	v.push_back("High Text Transfer Procedure");
	this->addQuestionToDB("What does HTTP stand for in web technology?", "Hyper Text Transfer Protocol", v);
}


/*
int SqliteDataBase::helpGetPlayerInfo(string playername, string functoActivate)
{
	std::string curr = playername;
	float avg = -1;
	string str = "select * from statistics where username = '" + playername + "'; ";
	cout << str << "\n";
	char* errMessage = nullptr;
	const char* sqlStatement = str.c_str();
	try
	{
		int res = sqlite3_exec(_db, sqlStatement, functoActivate, &avg, &errMessage);
		if (avg != -1)
		{
			return avg;
		}
	}
	catch (...)
	{

	}
	return FAIL;
}*/
