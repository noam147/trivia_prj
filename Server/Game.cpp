#include "Game.h"

Game::Game(std::vector<Question> questions, std::vector<string> usersInRoom, IDataBase* dataBase, int GameId):m_questions(questions),m_database(dataBase)
{
	this->m_gameId = GameId;
	
	for (int i = 0; i < usersInRoom.size(); i++)
	{
		GameData gamedata(m_questions[0]);//check size not here
		this->m_players.insert(std::make_pair(usersInRoom[i], gamedata));
	}

}

Question Game::getQuestionForUser(string user)
{
	GameData& current = this->m_players.find(user)->second;
	if (current.isPlayerFinishAnswerAllTheQuestions == true)//if player trying to ask multiple time when alredy finished
	{
		return Question("-1", std::vector<string>(), END_QUESTIONS);
	}

	if (m_questions.size() - 1 < current.correctAnswerCount + current.wrongAnswerCount)//if the questions ended
	{
		//check to prevent multiply request to db
		current.averageAnswerTime /= this->m_questions.size();//get the avg of answer time
		current.isPlayerFinishAnswerAllTheQuestions = true;
		this->submitGameStatsToDB(current,user);//send to db when end
		return Question("-1", std::vector<string>(), END_QUESTIONS);
	}
	current.currentQuestion = this->m_questions[current.correctAnswerCount + current.wrongAnswerCount];
	return current.currentQuestion;
}

RequestResult Game::submitAnswer(SendAnswerMessageFields userAnswer,std::string username)
{
	GameData& currgameData = this->m_players.find(username)->second;
	if (currgameData.isPlayerFinishAnswerAllTheQuestions == true)
	{
		throw RequestError();
	}
	currgameData.averageAnswerTime += userAnswer.answerTime;//add time - avg at end
	SubmitAnswerResponse submit;
	RequestResult r;
	r.newHandler = nullptr;
	if (this->m_players.find(username)->second.currentQuestion.getCorrectAnswerId() == userAnswer.answerIndex)
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
	for (auto it = this->m_players.begin(); it != this->m_players.end(); it++)
	{
		string curr = it->first;
		if (user == curr)
		{
			this->submitGameStatsToDB(it->second,user);//it->second is user's game data
			this->m_players.erase(it);
			return;
		}
	}
}

bool Game::checkIfAllPlayersFinishToAnswer()
{
	for (auto it = this->m_players.begin(); it != m_players.end(); it++)
	{
		if (it->second.isPlayerFinishAnswerAllTheQuestions == false)
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
