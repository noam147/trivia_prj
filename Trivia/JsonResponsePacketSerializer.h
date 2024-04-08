#pragma once
#include <string>
#include "json.hpp"
#include "RequestError.hpp"
#include "CommunicationHelper.h"
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
class JsonResponsePacketSerializer//msgs from the server to client
{
public:
	static char* serializeResponse(ErrorResponse error); //: Buffer
	static  char* serializeResponse(LoginResponse log); //: Buffer
	static  char* serializeResponse(SignupResponse sign); //: Buffer

	static std::string addLengthToMsg(std::string msg);//function will take regular msg and insert zeros to gete the protocol correctly, example: input: msg = "hello" output: "0005hello"
private:
	
};
