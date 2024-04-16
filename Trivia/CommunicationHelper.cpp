#include "CommunicationHelper.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using std::string;

// recieves the type code of the message from socket (3 bytes)
// and returns the code. if no message found in the socket returns 0 (which means the client disconnected)
byte CommunicationHelper::getMessageTypeCode(const SOCKET& sc)
{
	byte msgType = getPartFromSocket(sc, 1, 0)[0];
	return  msgType;
}


// sends hello to client, used for testing
void CommunicationHelper::sendHello(const SOCKET& sc)
{
	sendData(sc, "hello");
}

//reverse an array of chars(dosn't have to be a string)
//used for the length
void rev(char* replace_begin, int length) {
	char* replace_end = replace_begin + length - 1;
	char temp = '\0';
	for (size_t i = 0; i < length / 2; i++)
	{
		temp = *replace_begin;
		*replace_begin = *replace_end;
		*replace_end = temp;
		replace_begin++;
		replace_end--;
	}
}


// get the length part of the message and return as int
unsigned int CommunicationHelper::getMessageLength(const SOCKET& sc)
{
	char* lengthChr = new char[sizeof(unsigned int)];// an array of chars, dosnt need a null terminator
	lengthChr = getCharPartFromSocket(sc, sizeof(unsigned int));
	rev(lengthChr, sizeof(unsigned int));
	int length = *reinterpret_cast<int*>(lengthChr);
	delete[] lengthChr;

	return 0;
}

// recieve data from socket according byteSize
// returns the data as string
string CommunicationHelper::getStringPartFromSocket(const SOCKET& sc, const int bytesNum)
{
	return getPartFromSocket(sc, bytesNum, 0);
}

//get part from message in char*
//bytes num returned will be bytesNum + 1(null terminator)
char* CommunicationHelper::getCharPartFromSocket(const SOCKET& sc, int bytesNum) {
	if (bytesNum == 0)
	{
		return nullptr;
	}

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, 0);
	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}
	data[bytesNum] = 0;
	return data;
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
std::string CommunicationHelper::getPartFromSocket(const SOCKET& sc, const int bytesNum)
{
	return getPartFromSocket(sc, bytesNum, 0);
}

// send data to socket
// this is private function
void CommunicationHelper::sendData(const SOCKET& sc, const std::string message)
{
	const char* data = message.c_str();

	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

std::string CommunicationHelper::getPartFromSocket(const SOCKET& sc, const int bytesNum, const int flags)
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
