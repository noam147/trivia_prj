#include "GameRequestHandler.h"



GameRequestHandler::GameRequestHandler(RequestHandleFactory& handlerFacroty, Game& game, LoggedUser user,int timePerQuestion):m_handlerFacroty(handlerFacroty),m_game(game),m_gameManager(handlerFacroty.getGameManager()),m_user(user)
{
    m_timePerQuestion = timePerQuestion;
    this->m_initTime = timePerQuestion;
    this->m_isUserAnsweredCurrQuestion = true;
    this->m_destroyThread = false;
    std::thread t(&GameRequestHandler::updateTime, this);
    t.detach();
    this->m_start = std::chrono::high_resolution_clock::now();
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
    //wait until aLL PLAYER FINISH OR TIMER FINISHED - need to fix later
    RequestResult r;
    string username = m_user.getUserName();
    GetQuestionResponse getQuestion;
    r.newHandler = nullptr;
    //if time end- we want new question, if all players finish answer - we want new question
    //the issue is that in time the admin gets question he alredy 'close' the option to get questions here
    //if (!m_isTimeEnd || !this->m_game.checkIfAllPlayersAnsweredCurrentQuestion())
    if (!m_isTimeEnd)
    {
        std::vector<string> v;
        v.push_back("fake"); v.push_back("fake"); v.push_back("fake"); v.push_back("fake");
        getQuestion.question = "fake";
        getQuestion.status = DO_NOT_READY_FOR_NEXT_QUESTION;
        //maybe just send fake question?
        r.response = JsonResponsePacketSerializer::serializeResponse(getQuestion);
        return r;
    }
    m_isTimeEnd = false;
    {
        std::lock_guard<std::mutex> lock(m_timer_mutex); // Lock the mutex
        *m_timer_start = std::chrono::high_resolution_clock::now(); // Update the variable
    }
    std::cout << "update time now!\n";
    {
        std::lock_guard<std::mutex> lock(m_timer_mutex); // Lock the mutex
        auto milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(this->m_timer_start->time_since_epoch()).count();
        std::cout << "in gamemenu - not in thread- Milliseconds since epoch: " << milliseconds_since_epoch << std::endl;
    }
   
    /*while (true)
    {
        //need to check ALL users answered curr question before continue
        if (m_isTimeEnd || this->m_game.checkIfAllPlayersAnsweredCurrentQuestion())
        {
            //maybe just send fake question?
            m_isTimeEnd = false;
            break;
        }
    }*/
    this->m_game.checkIfAllPlayersAnsweredCurrentQuestion();//for checking
    Question q = this->m_game.getQuestionForUser(this->m_user.getUserName());
    std::cout << q.getQuestion()<<"\n";
    std::cout << q.getCorrectAnswerId() << "\n";
   
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
        //here cancel the thread
        this->m_timer_start = nullptr;
        this->m_destroyThread = true;
        getQuestion.status = END_QUESTIONS;
    }
    r.response = JsonResponsePacketSerializer::serializeResponse(getQuestion);
   

    
    return r;
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo info)
{
    if (this->m_game.getPlayersAndData().find(this->m_user.getUserName())->second.isPlayerFinishAnswerAllTheQuestions)
    {
        this->m_destroyThread = true;
        RequestResult r;
        r.newHandler = nullptr;
        r.response = JsonResponsePacketSerializer::serializeResponse(ERROR_RESPONSE);
        return r;
    }


    m_isTimeEnd = true;
    {
        std::lock_guard<std::mutex> lock(m_timer_mutex); // Lock the mutex
        *m_timer_start = std::chrono::high_resolution_clock::now(); // Update the variable
    }
    std::cout << "update time now!\n";
    {
        std::lock_guard<std::mutex> lock(m_timer_mutex); // Lock the mutex
        auto milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(this->m_timer_start->time_since_epoch()).count();
        std::cout << "in gamemenu - not in thread- Milliseconds since epoch: " << milliseconds_since_epoch << std::endl;
    }


   this->m_timePerQuestion = this->m_initTime;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = end - m_start;

    string msg = "";
    for (char ch : info.buffer)
    {
        msg += ch;
    }
    SendAnswerMessageFields answerDetails;
    answerDetails =  JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(CommunicationHelper::stringToCharArr(msg));
    std::cout << answerDetails.answerIndex << "\n";
    answerDetails.answerTime = static_cast<float>(elapsed.count());
    m_isUserAnsweredCurrQuestion = true;
    m_timePerQuestion = this->m_initTime;
    this->m_start = std::chrono::high_resolution_clock::now();//set the timer after get another answer
    return this->m_game.submitAnswer(answerDetails, this->m_user.getUserName());
}

RequestResult GameRequestHandler::getGameResults(RequestInfo info)
{
    RequestResult r;
    r.newHandler = nullptr;
    if (!this->m_game.checkIfAllPlayersFinishToAnswer())
    {
       r.response =  JsonResponsePacketSerializer::serializeResponse(ErrorResponse());
        return r;//not all players finish
    }
    this->m_handlerFacroty.getRoomManager().deleteRoom(m_user.getRoomId());
    this->m_user.setRoomId(-1);
    r.newHandler = this->m_handlerFacroty.createMenuRequestHandler(this->m_user);//after result go into menu
    GetGameResultsResponse playerSum;
    std::map<string, GameData> players= this->m_game.getPlayersAndData();
    for (auto it = players.begin(); it != players.end(); it++)
    {
        PlayerResults p;
        p.username = it->first;
        p.averageAnswerTime = it->second.averageAnswerTime;
        p.correctAnswerCount = it->second.correctAnswerCount;
        p.wrongAnswerCount = it->second.wrongAnswerCount;
        playerSum.results.push_back(p);
    }
    r.response = JsonResponsePacketSerializer::serializeResponse(playerSum);
    return r;
}

RequestResult GameRequestHandler::leaveGame(RequestInfo info)
{
    RequestResult r;
    this->m_user.setRoomId(-1);
    this->m_game.removePlayer(this->m_user.getUserName());
    r.newHandler = m_handlerFacroty.createMenuRequestHandler(m_user);

    if (this->m_game.getPlayersAndData().empty())
    {
        m_game.deleteDict();
        this->m_gameManager.deleteGame(this->m_game.getGameId());
       
    }

    r.response = JsonResponsePacketSerializer::serializeResponse(LEAVE_GAME_RESPONSE_SUCCESS);
    
    return r;
}

/*void GameRequestHandler::updateTime()
{
    while (true)
    {
       
        for (int i = m_timePerQuestion; i > 0;)
        {
            m_timePerQuestion--;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            i = m_timePerQuestion;
        }
        this->m_isTimeEnd = true;
        std::cout << "time end!\n";
        RequestInfo info;
        //this->m_game.getPlayersAndData().find(this->m_user.getUserName())->second.currentQuestion.getCorrectAnswerId();
        std::string msg = "00020{\"answerIndex\":-1}";
        for (char ch : msg)
        info.buffer.push_back(ch);
        m_timePerQuestion = this->m_initTime;
        if (this->m_destroyThread)
        {
            return;
        }
        //this->submitAnswer(info);//send fake answer
        
    }
}
*/

void GameRequestHandler::updateTime() 
{
    while (true)
    {
        if (m_timer_start == nullptr)
        {
            return;
        }
        *m_timer_start = std::chrono::high_resolution_clock::now();
        while (true)
        {
            {
                std::lock_guard<std::mutex> lock(m_timer_mutex); // Lock the mutex
                auto milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(this->m_timer_start->time_since_epoch()).count();
                std::cout << "Milliseconds since epoch: " << milliseconds_since_epoch << std::endl;
            }
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - *this->m_timer_start).count();
            if (elapsedTime >= m_initTime)
            {
                m_isTimeEnd = true;
                std::cout << "Time's up!\n";

                RequestInfo info;
                std::string msg = "00020{\"answerIndex\":-1}";
                for (char ch : msg)
                    info.buffer.push_back(ch);
                if (this->m_destroyThread == true)
                    return;
                this->submitAnswer(info);

                // Handle time-up logic here
                // For example, send a fake answer or trigger the next question
                // Ensure proper synchronization and error handling
                break; // Exit the loop after time's up
            }
            //std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Sleep for 1 second
           
        }
        if (this->m_destroyThread == true)
            return;
    }
}


