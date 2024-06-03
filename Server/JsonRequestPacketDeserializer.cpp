#include "JsonRequestPacketDeserializer.h"
#include <iostream>

/*int main()
{
    json j = json::parse(R"({"username":"user1","password":"1234"})");//login request
    std::string msgToSend = "4";//with start code to login
    std::string jsonString = j.dump();
    std::string updateMsg = JsonResponsePacketSerializer::addLengthToMsg(jsonString);
    updateMsg = msgToSend + updateMsg;
    char* bytes = new char[updateMsg.size() + 1];
    strcpy_s(bytes, updateMsg.size() + 1, updateMsg.c_str());
    LoginRequest e = JsonRequestPacketDeserializer::deserializeLoginRequest(bytes);
    std::cout << e.userName << e.password << "\n";
    ErrorResponse error;
    error.message = "EEEERRRRORRRR";
    JsonResponsePacketSerializer::serializeResponse(error);

    j = json::parse(R"({"username":"user2","password":"0000","email":"something@gmail.com"})");//login request
     msgToSend = "5";//with start code to login
     jsonString = j.dump();
     updateMsg = JsonResponsePacketSerializer::addLengthToMsg(jsonString);
    updateMsg = msgToSend + updateMsg;
     bytes = new char[updateMsg.size() + 1];
    strcpy_s(bytes, updateMsg.size() + 1, updateMsg.c_str());
    SignupRequest s = JsonRequestPacketDeserializer::deserializeSignupRequest(bytes);
    std::cout << s.userName << s.password <<s.email <<"\n";
    return 0;
}*/

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const char* buffer)
{
    LoginRequest e;
    try{
    std::string buff(buffer);//get into string format
    buff = buff.substr(1);//remove the first byte - the code msg

    int len = std::stoi(buff.substr(0, 4));//get len of msg - 4 bytes

    std::string jsonMsg = buff.substr(4, len);
    json j = json::parse(jsonMsg);
   
        e.userName = j["username"].dump();
        e.password = j["password"].dump();
        e.userName = e.userName.substr(1, e.userName.size() - 2);//get rid from the " "
        e.password = e.password.substr(1, e.password.size() - 2);
        if (e.password == "" || e.userName == "")
        {
            throw RequestError();
        }
    }
    catch (...)
    {
       throw RequestError();
    }
    return e;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const char* Buffer)
{
    SignupRequest s;
    try {
    std::string buff(Buffer);//get into string format
    buff = buff.substr(1);//remove the first byte - the code msg

    int len = std::stoi(buff.substr(0, 4));
    std::string jsonMsg = buff.substr(4, len);
    json j = json::parse(jsonMsg);
        s.userName = j["username"].dump();
        s.password = j["password"].dump();
        s.email = j["email"].dump();
        s.userName = s.userName.substr(1, s.userName.size()-2);
        s.password = s.password.substr(1, s.password.size() - 2);
        s.email = s.email.substr(1, s.email.size() - 2);
        if (s.email == "" || s.password == "" || s.userName == "")
        {
            throw RequestError();
        }
    }
    catch (...)
    {
        throw RequestError();
    }
   
    return s;
}


// gets a buffer containing the 
GetPlayersRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(const char* buffer)
{
    GetPlayersRequest e;
    try {
        std::string buff(buffer);//get into string format
        buff = buff.substr(1);//remove the first byte - the code msg

        int len = std::stoi(buff.substr(0, 4));//get len of msg - 4 bytes

        std::string jsonMsg = buff.substr(4, len);
        json j = json::parse(jsonMsg);

        if (j["roomId"].is_number_unsigned()) {
            e.roomId = j["roomId"];
        }
        else {
            throw RequestError();
        }
    }
    catch (...)
    {
        throw RequestError();
    }
    return e;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const char* buffer)
{
    JoinRoomRequest e;
    
    
    try {
        std::string buff(buffer);//get into string format
        buff = buff.substr(1);//remove the first byte - the code msg

        int len = std::stoi(buff.substr(0, 4));//get len of msg - 4 bytes

        std::string jsonMsg = buff.substr(4, len);
        json j = json::parse(jsonMsg);

        if (j["roomName"].is_string()) {
            e.roomname = j["roomName"];
        }
        else {
            throw RequestError();
        }
    }
    catch (...)
    {
        throw RequestError();
    }
    return e;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const char* buffer)
{
    CreateRoomRequest e;
    try {
        std::string buff(buffer);//get into string format
        buff = buff.substr(1);//remove the first byte - the code msg

        int len = std::stoi(buff.substr(0, 4));//get len of msg - 4 bytes

        std::string jsonMsg = buff.substr(4, len);
        json j = json::parse(jsonMsg);

        if (j["maxUsers"].is_number_unsigned() && j["questionCount"].is_number_unsigned() 
            && j["questionTimeout"].is_number_unsigned() && (j["roomName"].is_string() && j["roomName"] != "")) {
            e.maxUsers = j["maxUsers"];
            e.questionCount = j["questionCount"];
            e.questionTimeout = j["questionTimeout"];
            e.roomName = j["roomName"].get<std::string>();
        }
        else {
            throw RequestError();
        }
    }
    catch (...)
    {
        throw RequestError();
    }
    return e;

}

AddQuestionToDB JsonRequestPacketDeserializer::deserializeAddQuestionRequest(const char* buffer)
{
    AddQuestionToDB e;
    try {
        std::string buff(buffer);//get into string format
        buff = buff.substr(1);//remove the first byte - the code msg

        int len = std::stoi(buff.substr(0, 4));//get len of msg - 4 bytes

        std::string jsonMsg = buff.substr(4, len);
        json j = json::parse(jsonMsg);

        if ((j["question"].is_string() && j["question"] != "")&& (j["rightAnswer"].is_string() && j["rightAnswer"] != "")) 
        {
            e.question = j["question"];
            e.answers = j["wrongAnswers"].get<std::vector<std::string>>();
            e.rightAnswer = j["rightAnswer"];
        }
        else 
        {
            throw RequestError();
        }
    }
    catch (...)
    {
        throw RequestError();
    }
    return e;
}

SendAnswerMessageFields JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(const char* buffer)
{
    SendAnswerMessageFields answerData;


    try {
        std::string buff(buffer);//get into string format
        buff = buff.substr(1);//remove the first byte - the code msg

        int len = std::stoi(buff.substr(0, 4));//get len of msg - 4 bytes

        std::string jsonMsg = buff.substr(4, len);
        json j = json::parse(jsonMsg);

        if (j["answerIndex"].is_number_integer()) {
            answerData.answerIndex = j["answerIndex"];
        }
        else {
            throw RequestError();
        }
    }
    catch (...)
    {
        throw RequestError();
    }
    return answerData;
}
