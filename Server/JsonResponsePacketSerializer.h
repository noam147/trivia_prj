
#pragma once
#include <sstream>
#include <iomanip>
#include <string>
#include "RoomManager.h"
#include "json.hpp"
#include "RequestError.hpp"
#include "userDetalis.h"
#include "CommunicationHelper.h"

#define DO_NOT_READY_FOR_NEXT_QUESTION -3
#define END_QUESTIONS -1
#define KEEP_QUESTIONS 0

using json = nlohmann::json;

struct ErrorResponse {
	std::string message;
};
struct LoginResponse {
	int status;
};
struct SignupResponse {
	int status;
};
typedef struct{
	int status;
} LogoutResponse;

typedef struct {
	int status;
} JoinRoomResponse;

typedef struct {
	int status;
} CreateRoomResponse;

typedef struct {
	std::vector<RoomData> roomList;
} GetRoomResponse;

typedef struct {
	std::vector<std::string> userNames;
} GetPlayersInRoomResponse;

typedef struct {
	std::vector<std::string> playerStatistics;
}GetPlayerStatisticsResponse;

typedef struct {
	std::vector<userDetails> users;
} GetHighScoreResponse;

struct CloseRoomResponse {
	int status;
};

struct StartGameResponse {
	int status;
};

struct LeaveGameResponse {
	int status;
};

struct GetRoomStateResponse {
	int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int AnswerCount;
	unsigned int AnswerTimeOut;
};

struct GetQuestionResponse
{
	unsigned int status;
	std::string question;
	std::map<unsigned int, std::string>answers;
};
struct AddQuestionToDB
{
	std::string question;
	std::string rightAnswer;
	std::vector<std::string>answers;//wrong answers
};

struct SubmitAnswerResponse
{
	//unsigned int status;
	//unsigned int correctAnswerId;
	bool hasUserAnswerRight;
};
struct PlayerResults
{
	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averageAnswerTime;
};

struct GetGameResultsResponse
{
	std::vector<PlayerResults> results;
};



class JsonResponsePacketSerializer//msgs from the server to client
{
public:
	static std::string serializeResponse(ErrorResponse error); //: Buffer
	static  std::string serializeResponse(LoginResponse log); //: Buffer
	static  std::string serializeResponse(SignupResponse sign); //: Buffer
	static  std::string serializeResponse(LogoutResponse sign); //: Buffer
	static  std::string serializeResponse(JoinRoomResponse sign); //: Buffer
	static  std::string serializeResponse(CreateRoomResponse sign); //: Buffer
	static  std::string serializeResponse(GetRoomResponse sign); //: Buffer
	static  std::string serializeResponse(GetPlayersInRoomResponse sign); //: Buffer
	static  std::string serializeResponse(GetHighScoreResponse sign); //: Buffer
	static  std::string serializeResponse(GetPlayerStatisticsResponse sign); //: Buffer

	static std::string serializeResponse(CloseRoomResponse crRes); //: buffer
	static std::string serializeResponse(StartGameResponse sgRes); //: buffer
	static std::string serializeResponse(LeaveGameResponse lgRes); //: buffer
	static std::string serializeResponse(GetRoomStateResponse grsRes);
		

	static std::string serializeResponse(GetGameResultsResponse grRes);
	static std::string serializeResponse(SubmitAnswerResponse sbRes);
	static std::string serializeResponse(GetQuestionResponse gqRes);
	static std::string serializeResponse(char codeMsg);//serialse succsess response
	static std::string addLengthToMsg(std::string msg);//function will take regular msg and insert zeros to gete the protocol correctly, example: input: msg = "hello" output: "0005hello"
private:
	
};

