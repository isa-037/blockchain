#pragma once
#include <string>
#include "stringhasher.h"
class nonceguesser {
public:
    nonceguesser(StringHasher hasher, std::string prefix,int nonce_size,std::string suffix);
    bool is_valid_nonce(const std::string& nonce);
    std::string generate_nonce(int idx);
private:
    StringHasher hasher;
    std::string prefix;
    std::string suffix;
    int nonce_size;
    std::string current_nonce;
};