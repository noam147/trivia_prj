#pragma once
#include <string>;
class ICryptoAlgorythem
{
public:
	virtual void encrypt(std::string& key) = 0;
	virtual void decrypt(std::string& key) = 0;
};

