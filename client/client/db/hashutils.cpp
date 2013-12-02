#include "hashutils.h"

const std::string HashUtils::generateSalt() {
    char salt[SHA256_DIGEST_LENGTH];
    const char alphanum[] =
        "0123456789"
        "!@#$%^&*"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        salt[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    salt[SHA256_DIGEST_LENGTH] = 0;
    std::string _salt = std::string(salt);
    return _salt;
}

const std::string HashUtils::generateHash(const std::string& password, const std::string& salt) {

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.size());
    SHA256_Update(&sha256, salt.c_str(), salt.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}
