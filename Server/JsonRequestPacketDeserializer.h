
#pragma once
#include <string>
//#include "json.hpp"
#include "JsonResponsePacketSerializer.h"
#include "IRequestHandler.h"
//using json = nlohmann::json;

struct LoginRequest {
	std::string userName;
	std::string password;
};
struct SignupRequest {
	std::string userName;
	std::string password;
	std::string email;
};
typedef struct{
	unsigned int roomId;
} GetPlayersRequest;

typedef struct {
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int questionTimeout;
} CreateRoomRequest;

typedef struct {
	std::string roomname;
} JoinRoomRequest;

typedef struct
{
	int answerIndex;
	float answerTime;
} SendAnswerMessageFields;
struct kickPlayerMessageFields
{
	std::string playerToKick;
};
struct banPlayerMessageFields
{
	std::string playerToBan;
};
class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(const char* buffer);//example of buffer: 40038{"password":"1234","username":"user1"}
	static SignupRequest deserializeSignupRequest(const char* Buffer);
	static GetPlayersRequest deserializeGetPlayersRequest(const char* buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(const char* buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(const char* buffer);
	static AddQuestionToDB deserializeAddQuestionRequest(const char* buffer);
	static SendAnswerMessageFields deserializeSubmitAnswerRequest(const char* buffer);

	static kickPlayerMessageFields deserializeKickPlayerRequest(std::string msg);
	static banPlayerMessageFields deserializeBanPlayerRequest(std::string msg);

	static int deserializeEmailVerRequest(std::string msg);
private:

};

