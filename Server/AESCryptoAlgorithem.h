#pragma once
#include "ICryptoAlgorithem.h"

class AESCryptoAlgorithem : public ICryptoAlgorythem
{
public:
	void encrypt(std::string& key) override;
	void decrypt(std::string& key) override;
private:
	const std::string m_key = "0123456789abcdef";
	const std::string m_iv = "1234567890abcdef";
};

