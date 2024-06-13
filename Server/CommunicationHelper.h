#pragma once

#include <vector>
#include <string>
#include <WinSock2.h>
#include "JsonResponsePacketSerializer.h"

// To CLient
enum MessageType : byte
{
	ERROR_RESPONSE = 49,
	LOGIN_RESPONSE_SUCCESS,
	SIGNUP_RESPONSE_SUCCESS,
	LOGOUT_RESPONSE_SUCCESS,
	JOIN_ROOM_RESPONSE_SUCCESS,
	GET_ROOM_RESPONSE_SUCCESS,
	GET_PLAYER_IN_ROOM_RESPONSE_SUCCESS,
	CREATE_ROOM_RESPONSE_SUCCESS,
	GET_HIGH_SCORE_RESPONSE_SUCCESS,
	GET_PERSONAL_STAT_RESPONSE_SUCCESS,
	GET_ADD_QUESTION_CODE_SUCCESS,
	CLOSE_ROOM_RESPONSE_SUCCESS,//60
	START_GAME_RESPONSE_SUCCESS,
	GET_ROOM_STATE_RESPONSE_SUCCESS,
	LEAVE_ROOM_RESPONSE_SUCCESS,
	GET_GAME_RESULT_RESPONSE_SUCCESS,
	SUBMIT_ANSWER_RESPONSE_SUCCESS,//65
	GET_QUESTION_RESPONSE_SUCCESS,
	LEAVE_GAME_RESPONSE_SUCCESS,
	KICK_RESPONSE_SUCCESS
};
/* public enum DeserializeMessageCode
        {
            ERROR_CODE = 40,
            LOGIN_CODE,
            SIGNUP_CODE,
            LOGOUT_CODE,
            JOIN_ROOM_CODE,
            GET_ROOM_CODE,
            GET_PLAYER_IN_ROOM_CODE,
            CREATE_ROOM_CODE,
            GET_HIGH_SCORE_CODE,
            GET_PERSONAL_STAT_CODE,*/

// From Client
enum clientMessageType : byte
{
	LOGIN_REQUEST = 1,
	SIGN_UP_REQUEST,
	LOGOUT_REQUEST,
	LOGIN_REQUEST_FAIL,
	SIGN_UP_REQUEST_FAIL,
	JOIN_ROOM_REQUEST,
	GET_ROOM_REQUEST,
	GET_PLAYER_IN_ROOM_REQUEST,
	CREATE_ROOM_REQUEST,
	GET_HIGH_SCORE_REQUEST,//10
	GET_PERSONAL_STAT_REQUEST,
	GET_ADD_QUESTION_CODE,
	CLOSE_ROOM_REQUEST,
	START_GAME_REQUEST,
	GET_ROOM_STATE_REQUEST,//15
	LEAVE_ROOM_REQUEST,
	SUBMIT_ANSWER_REQUEST,
	GET_QUESTION_REQUEST,//18
	LEAVE_GAME_REQUEST,
	GET_GAME_RESULT_REQUEST,
	KICK_REQUEST
};

class CommunicationHelper
{
public:
	static int getMessageTypeCode(const SOCKET sc);
	static void sendHello(SOCKET sc);
	static int getIntPartFromSocket(const SOCKET sc, const int bytesNum);
	static int getLengthPartFromSocket(const SOCKET sc, const int bytesNum,char& codeMsg);
	static std::string getPartFromSocket(const SOCKET sc, const int bytesNum);
	static void sendData(const SOCKET sc, const std::string message);
	static std::string getPaddedNumber(const int num, const int digits);
	static char* stringToCharArr(std::string str);
	static std::string createErrorResponse();


private:
	static std::string getPartFromSocket(const SOCKET sc, const int bytesNum, const int flags);

};

