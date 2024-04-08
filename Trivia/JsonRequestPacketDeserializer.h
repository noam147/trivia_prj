#pragma once
#include <string>
//#include "json.hpp"
#include "JsonResponsePacketSerializer.h"
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
class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(const char* buffer);//example of buffer: 40038{"password":"1234","username":"user1"}
	static SignupRequest deserializeSignupRequest(const char* Buffer);
private:

};
