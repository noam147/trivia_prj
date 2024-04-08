#include "JsonResponsePacketSerializer.h"
#include <iostream>
#include <string>
#define _CRT_SECURE_NO_WARNINGS
char* JsonResponsePacketSerializer::serializeResponse(ErrorResponse error)
{
    std::string msg = "{\"message\":\""+error.message+"\"}";
    //json j = json::parse(R"({"message":"ERROR"})");
    json j = json::parse(msg);
    std::string jsonString = j.dump();//json to string
    std::string updateMsg = addLengthToMsg(jsonString);//add length to msg
    updateMsg = std::to_string(ERROR_RESPONSE) + updateMsg;//add codemsg

    char* bytes = new char[updateMsg.size() + 1];
    strcpy_s(bytes, updateMsg.size() + 1, updateMsg.c_str());//copy
    return bytes;
}

char* JsonResponsePacketSerializer::serializeResponse(LoginResponse log)
{

    std::string msg = "{\"status\":\"" + std::to_string(log.status) + "\"}";
    json j = json::parse(msg);

    std::string jsonString = j.dump();
    std::string updateMsg = addLengthToMsg(jsonString);
    updateMsg = std::to_string(LOGIN_RESPONSE) + updateMsg;//add codemsg

    char* bytes = new char[updateMsg.size() + 1];
    strcpy_s(bytes, updateMsg.size() + 1, updateMsg.c_str());

    return bytes;
}

char* JsonResponsePacketSerializer::serializeResponse(SignupResponse sign)
{
    std::string msg = "{\"status\":\"" + std::to_string(sign.status) + "\"}";
    json j = json::parse(msg);
    std::string jsonString = j.dump();
    std::string updateMsg = addLengthToMsg(jsonString);
    updateMsg = std::to_string(SIGNUP_RESPONSE) + updateMsg;//add code

    char* bytes = new char[updateMsg.size() + 1];
    strcpy_s(bytes, updateMsg.size() + 1, updateMsg.c_str());
    return bytes;
}
std::string JsonResponsePacketSerializer::addLengthToMsg(std::string msg)
{
    std::string msgSize = std::to_string(msg.size());
    while (msgSize.size() < 4)//while the length is below 4 - we need to add zeros
    {
        msgSize = "0" + msgSize;
    }
    return msgSize + msg;
}

