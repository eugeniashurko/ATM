#ifndef HASHUTILS_H
#define HASHUTILS_H

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

#include <openssl/sha.h>

namespace HashUtils {
    const std::string generateHash(const std::string& password, const std::string& salt);
    const std::string generateSalt();
}


#endif // HASHUTILS_H
