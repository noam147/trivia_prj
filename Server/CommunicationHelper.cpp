#include "CommunicationHelper.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using std::string;

// recieves the type code of the message from socket (3 bytes)
// and returns the code. if no message found in the socket returns 0 (which means the client disconnected)
int CommunicationHelper::getMessageTypeCode(const SOCKET sc)
{
	std::string msg = getPartFromSocket(sc, 3, 0);

	if (msg == "")
		return 0;

	int res = std::atoi(msg.c_str());
	return  res;
}


// sends hello to client, used for testing
void CommunicationHelper::sendHello(SOCKET sc) 
{
	sendData(sc, "hello");
}

// recieve data from socket according byteSize
// returns the data as int
int CommunicationHelper::getIntPartFromSocket(const SOCKET sc, const int bytesNum)
{
	return atoi(getPartFromSocket(sc, bytesNum, 0).c_str());
}

int CommunicationHelper::getLengthPartFromSocket(const SOCKET sc, const int bytesNum,char& codeMsg)
{
	if (bytesNum == 0)
	{
		return 0;
	}
	char* data = new char[bytesNum];
	memset(data, '\0', bytesNum);
	int res = recv(sc, &codeMsg, 1, 0);
	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}
	res = recv(sc, data, bytesNum - 1, 0);
	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}
	int len = 0;
	try
	{
		len = data[3] + data[2] * 127 + data[1] * 127 * 127 + data[0] * 127 * 127 * 127;
	}
	catch (...)
	{
		delete[] data;
		throw RequestError();
	}
	delete[] data;
	return len;
}


// return string after padding zeros if necessary
string CommunicationHelper::getPaddedNumber(const int num, const int digits)
{
	std::ostringstream ostr;
	ostr << std::setw(digits) << std::setfill('0') << num;
	return ostr.str();

}

// recieve data from socket according byteSize
// this is private function
std::string CommunicationHelper::getPartFromSocket(const SOCKET sc, const int bytesNum)
{
	return getPartFromSocket(sc, bytesNum, 0);
}
char* CommunicationHelper::stringToCharArr(std::string str)
{
	char* bytes = new char[str.size() + 1];
	strcpy_s(bytes, str.size() + 1, str.c_str());
	return bytes;
}
std::string CommunicationHelper::createErrorResponse()
{
	ErrorResponse e;
	e.message = "invalid msg";
	return JsonResponsePacketSerializer::serializeResponse(e);
}

// send data to socket
// this is private function
void CommunicationHelper::sendData(const SOCKET sc, const std::string message)
{
	const char* data = message.c_str();

	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

std::string CommunicationHelper::getPartFromSocket(const SOCKET sc, const int bytesNum, const int flags)
{
	if (bytesNum == 0)
	{
		return "";
	}

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, flags);
	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}
	data[bytesNum] = 0;
	std::string received(data);
	delete[] data;
	return received;
}
