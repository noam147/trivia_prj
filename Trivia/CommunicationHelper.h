#pragma once

#include <vector>
#include <string>
#include <WinSock2.h>


enum MessageType : byte
{
	ERROR_RESPONSE = 1,
	LOGIN_RESPONSE = 2,
	SIGNUP_RESPONSE = 3,
	LOGOUT_RESPONSE = 4,
	GET_ROOM_RESPONSE = 5,
	GET_PLAYER_IN_ROOM_RESPONSE = 6,
	JOIN_ROOM_RESPONSE = 7,
	CREATE_ROOM_RESPONSE = 8,
	GET_HIGH_SCORE_RESPONSE = 9,
	GET_PERSONAL_STAT_RESPONSE = 10,
	CLOSE_ROOM_RESPONSE = 11,
	START_GAME_RESPONSE = 12,
	GET_ROOM_STATE_RESPONSE = 13,
	LEAVE_ROOM_RESPONSE = 14,
	GET_GAME_RESULT_RESPONSE = 15,
	SUBMIT_ANSWER_RESPONSE = 16,
	GET_QUESTION_RESPONSE = 17,
	LEAVE_GAME_RESPONSE = 18
};

class CommunicationHelper
{
public:
	static byte getMessageTypeCode(const SOCKET& sc);
	static void sendHello(const SOCKET& sc);
	static unsigned int getMessageLength(const SOCKET& sc);
	static std::string getStringPartFromSocket(const SOCKET& sc, const int bytesNum);
	static void sendData(const SOCKET& sc, const std::string message);
	static std::string getPaddedNumber(const int num, const int digits);

private:
	static char* getCharPartFromSocket(const SOCKET& sc, int bytesNum);
	static std::string getPartFromSocket(const SOCKET& sc, const int bytesNum);
	static std::string getPartFromSocket(const SOCKET& sc, const int bytesNum, const int flags);

};

