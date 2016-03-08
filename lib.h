#ifndef LIB_H
#define LIB_H

#include <sha3.h>
#include <string>

//#define SHA3_HASH(inputString) inputString _SHA3_HASH

/**
 * @brief SHA3-512 wrapper
 * @param input - The input to be hashed
 * @return A SHA3-512 hash
 */
std::string SHA3(std::string input) {
    CryptoPP::SHA3_512 hash;
    byte digest [CryptoPP::SHA3_512::DIGESTSIZE];

    hash.CalculateDigest(digest, (byte*)input.c_str(), input.length());
    std::string out;
    out.assign((char *)digest, sizeof(digest));

    return out;
}
/**
 * @brief operator _SHA3_HASH suffix for strings
 * @param input - The string prefix
 * @param length - does nothing, just there to satisfy compiler
 * @return A SHA3-512 hash
 */
std::string operator "" _SHA3_HASH(const char *input, unsigned int length){
    return SHA3(input);
}

#endif // LIB_H
