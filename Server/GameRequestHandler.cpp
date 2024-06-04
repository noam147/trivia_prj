#include "GameRequestHandler.h"



GameRequestHandler::GameRequestHandler(RequestHandleFactory& handlerFacroty, Game& game, LoggedUser user):m_handlerFacroty(handlerFacroty),m_game(game),m_gameManager(handlerFacroty.getGameManager()),m_user(user)
{
}

GameRequestHandler::~GameRequestHandler()
{
    this->m_handlerFacroty.getLoginManager().logOut(this->m_user.getUserName());
    this->leaveGame(RequestInfo()); //the user still in game even if he exsit
    
}

bool GameRequestHandler::isRequestRelevant(RequestInfo info)
{
    char ch = info.buffer[0];
    if (ch == LEAVE_GAME_REQUEST || ch == GET_QUESTION_REQUEST||ch == SUBMIT_ANSWER_REQUEST||ch == GET_GAME_RESULT_REQUEST)
    {
        return true;
    }
    return false;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo info)
{
    char ch = info.buffer[0];
    switch (ch)
    {
    case LEAVE_GAME_REQUEST:
        return this->leaveGame(info);
        break;
    case GET_QUESTION_REQUEST:
        return this->getQuestion(info);
        break;
    case SUBMIT_ANSWER_REQUEST:
        return this->submitAnswer(info);
        break;
    case GET_GAME_RESULT_REQUEST:
        return this->getGameResults(info);
        break;
    default:
        throw RequestError();
        break;
    }
   
    return RequestResult();
}

RequestResult GameRequestHandler::getQuestion(RequestInfo info)
{
    RequestResult r;
    r.newHandler = nullptr;
    Question q = this->m_game.getQuestionForUser(this->m_user.getUserName());
    GetQuestionResponse getQuestion;
    getQuestion.question = q.getQuestion();
    std::vector<std::string> answers = q.getPossibleAnswers();

    for (int i = 0; i < answers.size(); i++)
    {
        getQuestion.answers.insert(std::make_pair(i, answers[i]));//index of question
    }
    getQuestion.status = KEEP_QUESTIONS;
    if (q.getCorrectAnswerId() == END_QUESTIONS)
    {
        //need to check if need to create resultHandler? seem pretty useless..
        //maybe here send the getGameResults
        getQuestion.status = END_QUESTIONS;
    }
    r.response = JsonResponsePacketSerializer::serializeResponse(getQuestion);
   

    this->m_start = std::chrono::high_resolution_clock::now();//set the timer
    return r;
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo info)
{
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = end - m_start;

    string msg = "";
    for (char ch : info.buffer)
    {
        msg += ch;
    }
    SendAnswerMessageFields answerDetails;
    answerDetails =  JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(CommunicationHelper::stringToCharArr(msg));
    answerDetails.answerTime = static_cast<float>(elapsed.count());
    return this->m_game.submitAnswer(answerDetails, this->m_user.getUserName());
}

RequestResult GameRequestHandler::getGameResults(RequestInfo info)
{
    RequestResult r;
    if (this->m_game.checkIfAllPlayersFinishToAnswer())
    {
        //need to serilze response of results
       // r.response = 
        r.newHandler = this->m_handlerFacroty.createMenuRequestHandler(this->m_user);//after result go into menu
    }

    throw RequestError();//not all players finish
}

RequestResult GameRequestHandler::leaveGame(RequestInfo info)
{
    RequestResult r;
    this->m_user.setRoomId(-1);
    this->m_game.removePlayer(this->m_user.getUserName());
    r.newHandler = m_handlerFacroty.createMenuRequestHandler(m_user);
    r.response = JsonResponsePacketSerializer::serializeResponse(LEAVE_GAME_RESPONSE_SUCCESS);
    return r;
}
