#include "AESCryptoAlgorithem.h"
#include <iostream>
#include <string>
#include <aes.h>
#include <modes.h>
#include <filters.h>
#include <hex.h>
#include <secblock.h>

void AESCryptoAlgorithem::encrypt(std::string& key) {
    using namespace CryptoPP;
    try {
        std::string ciphertext;
        CBC_Mode<AES>::Encryption encryption((byte*)m_key.data(), m_key.size(), (byte*)m_iv.data());

        StringSource ss(key, true,
            new StreamTransformationFilter(encryption,
                new StringSink(ciphertext),
                StreamTransformationFilter::PKCS_PADDING
            )
        );

        std::string encoded;
        StringSource(ciphertext, true,
            new HexEncoder(
                new StringSink(encoded)
            )
        );

        key = encoded;
    }
    catch (const Exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void AESCryptoAlgorithem::decrypt(std::string& key)
{
    using namespace CryptoPP;
    try {
        std::string decoded;
        StringSource(key, true,
            new HexDecoder(
                new StringSink(decoded)
            )
        );
        std::string plaintext;
        CBC_Mode<AES>::Decryption decryption((byte*)m_key.data(), m_key.size(), (byte*)m_iv.data());

        StringSource ss(decoded, true,
            new StreamTransformationFilter(decryption,
                new StringSink(plaintext)
            )
        );

        key = plaintext;
    }
    catch (const Exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
