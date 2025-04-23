#include "Game.h"
Game::Game(std::vector<Question> questions, std::vector<string> usersInRoom, IDataBase* dataBase, int GameId,std::string name):m_questions(questions),m_database(dataBase)
{
	this->m_gameId = GameId;
	this->m_gameName = name;
	for (int i = 0; i < usersInRoom.size(); i++)
	{
		GameData gamedata(m_questions[0]);//check size not here
		this->m_players->insert(std::make_pair(usersInRoom[i], gamedata));
	}

}

Question Game::getQuestionForUser(string user)
{
	try
	{


		GameData& current = this->m_players->find(user)->second;
		if (current.isPlayerFinishAnswerAllTheQuestions == true)//if player trying to ask multiple time when alredy finished
		{
			return Question("-1", std::vector<string>(), END_QUESTIONS);
		}

		if (m_questions.size() - 1 < current.correctAnswerCount + current.wrongAnswerCount)//if the questions ended
		{
			//check to prevent multiply request to db
			current.averageAnswerTime /= this->m_questions.size();//get the avg of answer time
			current.isPlayerFinishAnswerAllTheQuestions = true;
			this->submitGameStatsToDB(current, user);//send to db when end
			return Question("-1", std::vector<string>(), END_QUESTIONS);
		}
		current.currentQuestion = this->m_questions[current.correctAnswerCount + current.wrongAnswerCount];
		return current.currentQuestion;
	}
	catch (...)
	{
		throw RequestError();
	}
}

RequestResult Game::submitAnswer(SendAnswerMessageFields userAnswer,std::string username)
{
	GameData& currgameData = this->m_players->find(username)->second;
	if (currgameData.isPlayerFinishAnswerAllTheQuestions == true)
	{
		throw RequestError();
	}
	currgameData.averageAnswerTime += userAnswer.answerTime;//add time - avg at end
	SubmitAnswerResponse submit;
	RequestResult r;
	r.newHandler = nullptr;
	if (this->m_players->find(username)->second.currentQuestion.getCorrectAnswerId() == userAnswer.answerIndex)
	{
		submit.hasUserAnswerRight = true;
		currgameData.correctAnswerCount++;
	}
	else
	{
		submit.hasUserAnswerRight = false;
		currgameData.wrongAnswerCount++;
	}
	r.response = JsonResponsePacketSerializer::serializeResponse(submit);
	
	
	return r;
}


void Game::removePlayer(string user)
{
	for (auto it = this->m_players->begin(); it != this->m_players->end(); it++)
	{
		string curr = it->first;
		if (user == curr)
		{
			if(!it->second.isPlayerFinishAnswerAllTheQuestions)//if we did not insert it into db
				this->submitGameStatsToDB(it->second,user);//it->second is user's game data
			//this->m_players->erase(it);
		}
	}
	this->m_players->find(user)->second.hasLeaved = true;
	this->m_players->find(user)->second.averageAnswerTime /= this->m_players->find(user)->second.correctAnswerCount + this->m_players->find(user)->second.wrongAnswerCount;
	this->m_players->find(user)->second.isPlayerFinishAnswerAllTheQuestions = true;
	
}

int Game::getGameId() const
{
	return this->m_gameId;
}

std::string Game::getName() const
{
	return this->m_gameName;
}

bool Game::checkIfAllPlayersFinishToAnswer()
{
	for (auto it = this->m_players->begin(); it != m_players->end(); it++)
	{
		if (it->second.isPlayerFinishAnswerAllTheQuestions == false)
		{
			return false;
		}
	}
	return true;
}

std::map<string, GameData> Game::getPlayersAndData()
{
	return *this->m_players;
}

void Game::deleteDict()
{
	if (m_players != nullptr)
	{
		this->m_players->clear();
		delete this->m_players;
		this->m_players = nullptr;
	}
}

void Game::insertPlayer(std::string user)
{
	this->m_players->insert(std::make_pair(user, GameData(m_questions[0])));
}

bool Game::checkIfEveryOneLeft() const
{
	for (auto it = this->m_players->begin(); it != m_players->end(); it++)
	{
		if (it->second.hasLeaved == false)
		{
			return false;
		}
	}
	return true;
}

void Game::submitGameStatsToDB(GameData gamedata,std::string username)
{

	this->m_database->submitGameStatistics(gamedata, username);
	//update in statistics table

}
