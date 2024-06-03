#include "StatisticsManager.h"



StatisticsManager::StatisticsManager(IDataBase* database)
{
	m_database = database;
}

void StatisticsManager::setDataBase(IDataBase* database)
{
	this->m_database = database;
}

std::vector<userDetails> StatisticsManager::getHighScore()
{
	return this->m_database->getHighScores();
}

std::vector<string> StatisticsManager::getUserStatistics(string username)
{
	std::vector<string> v;
	/*std::string msg = "{\"Average answer time\":\"" + std::to_string(this->m_database->getPlayerAverageAnswerTime(username)) + 
		"\",""\"NumOfCorrectAnswers\":\""+std::to_string(this->m_database->getNumOfCorrectAnswers(username)) + 
		"\",\"""NumOfGames\":\"" + std::to_string(this->m_database->getNumOfPlayerGames(username)) +
		"\",\"""PlayerScore\":\"" + std::to_string(this->m_database->getPlayerScore(username)) +
		"\",\"""NumOfTotalAnswers\":\"" + std::to_string(this->m_database->getNumOfTotalAnswers(username)) +
		"\"}";
	cout << msg << "\n";*/
	v.push_back(std::to_string(this->m_database->getPlayerAverageAnswerTime(username)));
	v.push_back(std::to_string(this->m_database->getNumOfCorrectAnswers(username)));
	v.push_back(std::to_string(this->m_database->getNumOfPlayerGames(username)));
	v.push_back(std::to_string(this->m_database->getPlayerScore(username)));
	v.push_back(std::to_string(this->m_database->getNumOfTotalAnswers(username)));
	return v;
}
