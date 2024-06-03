#pragma once
#include "IDataBase.h"
#include <cmath>
#include <vector>
class StatisticsManager
{
public:
	//StatisticsManager();
	StatisticsManager(IDataBase* database);
	void setDataBase(IDataBase* database);
	std::vector<userDetails> getHighScore();
	std::vector<string> getUserStatistics(string username);

private:
	IDataBase* m_database;
};