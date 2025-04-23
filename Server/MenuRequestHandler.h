#pragma once


#pragma once

#include "IRequestHandler.h"
#include "RequestHandleFactory.h"
class RequestHandleFactory;
class MenuRequestHandler : public IRequestHandler
{
public:
	~MenuRequestHandler();
	MenuRequestHandler(RequestHandleFactory& handlerFactory,LoggedUser user);
	bool isRequestRelevant(RequestInfo info) override;//func check if msg is sign in or login type of msg
	RequestResult handleRequest(RequestInfo info) override;

private:
	// methodes
	RequestResult signout(RequestInfo info);
	RequestResult getRooms(RequestInfo info);
	RequestResult getPlayersInRoom(RequestInfo info);
	RequestResult joinRoom(RequestInfo info);
	RequestResult createRoom(RequestInfo info);
	RequestResult getPlayerHighscore(RequestInfo info);
	RequestResult getPlayerStats(RequestInfo info);
	RequestResult addQuestion(RequestInfo info);
	// members
	LoggedUser m_user;
	RequestHandleFactory& m_handlerFactory;

};

