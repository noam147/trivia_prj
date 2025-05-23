#pragma once
#include "GameManager.h"
#include "RequestHandleFactory.h"

#include <chrono>//for timer
using namespace std::chrono;
class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(RequestHandleFactory& handlerFacroty, Game& game, LoggedUser user);
	~GameRequestHandler();
	bool isRequestRelevant(RequestInfo) override;
	RequestResult handleRequest(RequestInfo) override;
	

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;//for timer to see the time between quesitons
	Game& m_game;
	LoggedUser m_user;//current user that in room- in active game
	GameManager & m_gameManager;
	RequestHandleFactory& m_handlerFacroty;

	RequestResult getQuestion(RequestInfo info);
	RequestResult submitAnswer(RequestInfo info);
	RequestResult getGameResults(RequestInfo info);
	RequestResult leaveGame(RequestInfo info);

};