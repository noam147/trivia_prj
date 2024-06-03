#pragma once
#include "BaseException.hpp"
class RequestError : protected BaseException {
public:
	RequestError() : BaseException("Error: request is not valid\n") {};
};