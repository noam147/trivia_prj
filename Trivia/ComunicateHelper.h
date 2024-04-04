#pragma once

#include <vector>
#include <string>
#include <WinSock2.h>


enum MessageType : byte
{
	//none for now
};

class ComunicateHelper
{
public:
	static int getMessageTypeCode(const SOCKET sc);
	static int getIntPartFromSocket(const SOCKET sc, const int bytesNum);
	static std::string getStringPartFromSocket(SOCKET sc, const int bytesNum);
	static void sendData(const SOCKET sc, const std::string message);
	static void send_update_message_to_client(const SOCKET sc, const std::string& file_content, const std::string& second_username, const std::string& all_users);
	static std::string getPaddedNumber(const int num, const int digits);

private:
	static std::string getPartFromSocket(const SOCKET sc, const int bytesNum);
	static std::string getPartFromSocket(const SOCKET sc, const int bytesNum, const int flags);

};

