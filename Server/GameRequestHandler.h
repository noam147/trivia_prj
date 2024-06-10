#pragma once
#include "GameManager.h"
#include "RequestHandleFactory.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>//for timer
using namespace std::chrono;
class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(RequestHandleFactory& handlerFacroty, Game& game, LoggedUser user,int timePerQuestion);
	~GameRequestHandler();
	bool isRequestRelevant(RequestInfo) override;
	RequestResult handleRequest(RequestInfo) override;
	

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;//for timer to see the time between quesitons
	Game& m_game;
	LoggedUser m_user;//current user that in room- in active game
	GameManager & m_gameManager;
	RequestHandleFactory& m_handlerFacroty;
	bool m_isTimeEnd = true;
	std::atomic<int> m_timePerQuestion;
	int m_initTime;
	bool m_isUserAnsweredCurrQuestion;
	RequestResult getQuestion(RequestInfo info);
	RequestResult submitAnswer(RequestInfo info);
	RequestResult getGameResults(RequestInfo info);
	RequestResult leaveGame(RequestInfo info);

	void updateTime();
	std::chrono::time_point<std::chrono::high_resolution_clock>* m_timer_start = new std::chrono::time_point<std::chrono::high_resolution_clock>(std::chrono::high_resolution_clock::now());
	std::atomic<bool> m_destroyThread;
	std::condition_variable m_cv;
	std::mutex m_timer_mutex;

	struct FriendLambda {
		GameRequestHandler& handler;
		FriendLambda(GameRequestHandler& h) : handler(h) {}
		bool operator()() const {
			return handler.m_timePerQuestion == handler.m_initTime || handler.m_destroyThread;
		}
	};
};