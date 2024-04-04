#pragma once
#include <exception>
#include <string>

class BaseException : public std::exception
{
public:
	BaseException(const std::string& message) : m_message(message) {}
	virtual ~BaseException() noexcept = default;
	virtual const char* what() const noexcept { return m_message.c_str(); }

protected:
	std::string m_message;
};
