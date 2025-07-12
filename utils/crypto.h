# pragma once

#include <array>
#include <iostream>
#include <sodium.h>
#include <string>

// Generate a hash (including salt, params, etc.)
inline std::string getHash(const std::string& password)
{
    char hashed[crypto_pwhash_STRBYTES];

    if (crypto_pwhash_str(
        hashed,
        password.c_str(), password.size(),
        crypto_pwhash_OPSLIMIT_MODERATE,
        crypto_pwhash_MEMLIMIT_MODERATE) != 0)
    {
        throw std::runtime_error("Out of memory while hashing password.");
    }

    return std::string(hashed); // safe: null-terminated string
}

// Verify password against stored hash
inline bool verifyHash(const std::string& password, const std::string& storedHash)
{
    return crypto_pwhash_str_verify(
        storedHash.c_str(),
        password.c_str(), password.size()) == 0;
}
