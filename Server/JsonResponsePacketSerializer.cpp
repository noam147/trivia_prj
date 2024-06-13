
#include "JsonResponsePacketSerializer.h"
#include <iostream>
#include <string>
#define _CRT_SECURE_NO_WARNINGS

void to_json(json& j, const PlayerResults& pr) {
    j = json{
        {"username", pr.username},
        {"correctAnswerCount", pr.correctAnswerCount},
        {"wrongAnswerCount", pr.wrongAnswerCount},
        {"averageAnswerTime", pr.averageAnswerTime}
    };
}


std::string JsonResponsePacketSerializer::serializeResponse(ErrorResponse error)
{
    std::string msg = "{\"message\":\""+error.message+"\"}";
    //json j = json::parse(R"({"message":"ERROR"})");
    json j = json::parse(msg);
    std::string jsonString = j.dump();//json to string
    std::string updateMsg = addLengthToMsg(jsonString);//add length to msg
    char codeMsg = ERROR_RESPONSE;
    updateMsg = codeMsg + updateMsg;//add codemsg

    return updateMsg;
}

std::string JsonResponsePacketSerializer::serializeResponse(LoginResponse log)
{

    std::string msg = "{\"status\":\"" + std::to_string(log.status) + "\"}";
    json j = json::parse(msg);

    std::string jsonString = j.dump();
    std::string updateMsg = addLengthToMsg(jsonString);
    char codeMsg = log.status;
    updateMsg = codeMsg + updateMsg;//add codemsg
    return updateMsg;
    //char* bytes = new char[updateMsg.size() + 1];
    //strcpy_s(bytes, updateMsg.size() + 1, updateMsg.c_str());

    //return bytes;
}

std::string JsonResponsePacketSerializer::serializeResponse(SignupResponse sign)
{
    std::string msg = "{\"status\":\"" + std::to_string(sign.status) + "\"}";
    json j = json::parse(msg);
    std::string jsonString = j.dump();
    std::string updateMsg = addLengthToMsg(jsonString);
    char codeMsg = sign.status;
    updateMsg = codeMsg + updateMsg;//add code

    return updateMsg;
}
std::string JsonResponsePacketSerializer::serializeResponse(LogoutResponse sign)
{
    std::string msg = "{\"status\":\"" + std::to_string(sign.status) + "\"}";
    json j = json::parse(msg);
    std::string jsonString = j.dump();
    std::string updateMsg = addLengthToMsg(jsonString);
    char codeMsg = sign.status;
    updateMsg = codeMsg + updateMsg;//add code

    return updateMsg;
}

std::string JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse sign)
{
    std::string msg = "{\"status\":\"" + std::to_string(sign.status) + "\"}";
    json j = json::parse(msg);
    std::string jsonString = j.dump();
    std::string updateMsg = addLengthToMsg(jsonString);
    char codeMsg = JOIN_ROOM_RESPONSE_SUCCESS;
    updateMsg = codeMsg + updateMsg;//add code

    return updateMsg;
}

std::string JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse sign)
{
    std::string msg = "{\"status\":\"" + std::to_string(sign.status) + "\"}";
    json j = json::parse(msg);
    std::string jsonString = j.dump();
    std::string updateMsg = addLengthToMsg(jsonString);
    char codeMsg = CREATE_ROOM_RESPONSE_SUCCESS;
    updateMsg = codeMsg + updateMsg;//add code
    return updateMsg;
}

std::string JsonResponsePacketSerializer::serializeResponse(GetRoomResponse sign)//change to see admin and players in room
{
    std::string roomNames = "\"Rooms\": [";
    for (auto room : sign.roomList)
        roomNames += "\"" + room.name + "\",";
    if (roomNames.back() == ',')
        roomNames.pop_back();
    roomNames += "]";
    std::string jsonMsg = "{" + roomNames + "}";
    std::string updateMsg = addLengthToMsg(jsonMsg);
    char codeMsg = GET_ROOM_RESPONSE_SUCCESS;
    updateMsg = codeMsg + updateMsg;//add code

    return updateMsg;
}

std::string JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse sign)
{
    std::string userNames = "\"Users\": [";
    for (auto name : sign.userNames)
        userNames += "\"" + name + "\", ";
    if (userNames.back() == ',')
        userNames.pop_back();
    userNames += "]";
    std::string jsonMsg = "{" + userNames + "}";
    std::string updateMsg = addLengthToMsg(jsonMsg);
    char codeMsg = GET_PLAYER_IN_ROOM_RESPONSE_SUCCESS;
    updateMsg = codeMsg + updateMsg;//add code
    return updateMsg;
}

std::string JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse sign)
{

    //parse highScores
    std::string HighScores = "\"HighScores\":[";
    for (const auto& user : sign.users)
        HighScores += "{\"" + user.user_name + "\":\"" + std::to_string(user.score) + "\"},";
    if (!sign.users.empty())
        HighScores.pop_back();
    HighScores += ']';

    std::string jsonMsg = "{" + HighScores + "}";
    std::string updateMsg = addLengthToMsg(jsonMsg);
    char codeMsg = GET_HIGH_SCORE_RESPONSE_SUCCESS;
    updateMsg = codeMsg + updateMsg;//add code
    return updateMsg;
}

std::string JsonResponsePacketSerializer::serializeResponse(GetPlayerStatisticsResponse sign)
{
    //parse stats
    std::string userStatistic = "\"UserStatistics\": [";
    for (auto stat : sign.playerStatistics)
        userStatistic += "\"" + stat + "\",";
    if (userStatistic.back() == ',')
        userStatistic.pop_back();
    userStatistic += ']';

    std::string jsonMsg = "{" + userStatistic + "}";
    std::string updateMsg = addLengthToMsg(jsonMsg);
    char codeMsg = GET_PERSONAL_STAT_RESPONSE_SUCCESS;
    updateMsg = codeMsg + updateMsg;//add code
    return updateMsg;
   
}
std::string JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse crRes)
{
    std::string msg = "{\"status\":\"" + std::to_string(crRes.status) + "\"}";
    json j = json::parse(msg);
    std::string jsonString = j.dump();
    std::string updateMsg = addLengthToMsg(jsonString);
    char codeMsg = CLOSE_ROOM_RESPONSE_SUCCESS;
    updateMsg = codeMsg + updateMsg;//add code

    return updateMsg;
}

std::string JsonResponsePacketSerializer::serializeResponse(StartGameResponse sgRes)
{
    std::string msg = "{\"status\":\"" + std::to_string(sgRes.status) + "\"}";
    json j = json::parse(msg);
    std::string jsonString = j.dump();
    std::string updateMsg = addLengthToMsg(jsonString);
    char codeMsg = START_GAME_RESPONSE_SUCCESS;
    updateMsg = codeMsg + updateMsg;//add code

    return updateMsg;
}

std::string JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse lgRes)
{
    std::string msg = "{\"status\":\"" + std::to_string(lgRes.status) + "\"}";
    json j = json::parse(msg);
    std::string jsonString = j.dump();
    std::string updateMsg = addLengthToMsg(jsonString);
    char codeMsg = LEAVE_GAME_RESPONSE_SUCCESS;
    updateMsg = codeMsg + updateMsg;//add code

    return updateMsg;
}

std::string JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse grsRes)
{

    json j;
    j["status"] = grsRes.status;
    j["HasGameBegun"] = grsRes.hasGameBegun;
    j["Players"] = grsRes.players;
    j["AnswerCount"] = grsRes.AnswerCount;
    j["AnswerTimeOut"] = grsRes.AnswerTimeOut;

    // Serialize the JSON object to a string
    std::string jsonString = j.dump();
    std::string updateMsg = addLengthToMsg(jsonString);
    char codeMsg = GET_ROOM_STATE_RESPONSE_SUCCESS;
    updateMsg = codeMsg + updateMsg; // Add code

    return updateMsg;
}

std::string JsonResponsePacketSerializer::serializeResponse(GetGameResultsResponse grRes)
{
    json j;
    j["results"] = grRes.results;
    std::string msg =  j.dump();
    msg = addLengthToMsg(msg);
    char codeMsg = GET_GAME_RESULT_RESPONSE_SUCCESS;
    msg = codeMsg +msg;
    return msg;
}
std::string JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse sbRes)
{
    json j;
    j["hasUserAnswerRight"] = sbRes.hasUserAnswerRight;
    std::string msg = j.dump();
    j = json::parse(msg);
    std::string jsonString = j.dump();
    std::string updateMsg = addLengthToMsg(jsonString);
    char codeMsg = SUBMIT_ANSWER_RESPONSE_SUCCESS;
    updateMsg = codeMsg + updateMsg;//add code

    return updateMsg;
}
std::string JsonResponsePacketSerializer::serializeResponse(GetQuestionResponse gqRes)
{
    char codeMsg = ':';
    //gqRes.status == 1 - end game 0-keep going
    if (gqRes.status == END_QUESTIONS)
    {
        codeMsg = ERROR_RESPONSE;//game end = can't ask for question
        return "{}";
    }
    if (gqRes.status == KEEP_QUESTIONS)
    {
        codeMsg = GET_QUESTION_RESPONSE_SUCCESS;
    }
    if (gqRes.answers.size() != 4)//if there are not 4 answers
    {
        codeMsg = ERROR_RESPONSE;
        return "{}";
    }
    std::string msg = "{\"status\":\"" + std::to_string(gqRes.status) + "\",\"question\":\""+gqRes.question+"\",\"answers\":\[\""+gqRes.answers.find(0)->second + "\",\"" + gqRes.answers.find(1)->second + "\",\"" + gqRes.answers.find(2)->second + "\",\"" + gqRes.answers.find(3)->second + "\"]}";
    json j = json::parse(msg);
    std::string jsonString = j.dump();
    std::string updateMsg = addLengthToMsg(jsonString);
    updateMsg = codeMsg + updateMsg;//add code

    return updateMsg;
}
std::string JsonResponsePacketSerializer::serializeResponse(char codeMsg)
{
    std::string msg = "{\"status\":\"" + std::to_string(codeMsg) + "\"}";
    msg = codeMsg + msg;
    return msg;
}
std::string JsonResponsePacketSerializer::addLengthToMsg(std::string msg)
{
    int length = msg.size();
    std::string str = "0000";
    str[3] = (char)(length % 127);

    str[3] = (char)(length % 127);
    length /= 127;
    str[2] = (char)(length % 127);
    length /= 127;
    str[1] = (char)(length % 127);
    length /= 127;
    str[0] = (char)(length % 127);

    return str + msg;
}
/* func didnt genarte 4 bytes
std::string JsonResponsePacketSerializer::addLengthToMsg(std::string msg)
{
    unsigned int length = msg.length();
    char msgSize[sizeof(unsigned int) + 1] = { '\0' };
    memcpy(msgSize, &length, sizeof(unsigned int));
    return msgSize + msg;
}*/