#include <iostream>
#include <vector>
#include <fstream>

#include "adminutility.h"

using std::string;

/**
 * Function to determine if the chosen username and password are valid.  If valid, the function
 * returns true. 
 */ 
bool AdminUtility::isUserPassValid(string &user, string &pass, std::vector<string> *pdata) {
    //Check length.
    if (user.length() > 12 || user.length() < 8) {
        return false;
    }

    if (pass.length() > 12 || pass.length() < 8) {
        return false;
    }

    if (!isOnlyASCIIAndNotSpace(user) || !isOnlyASCIIAndNotSpace(pass)) {
        return false;
    }

    //Check for duplicates
    for (string itr : *pdata) {
        string delimiter = "::::";
        string ucheck = itr.substr(0, itr.find(delimiter)); 

        if (user.compare(ucheck) == 0) {
            return false;
        }
    }

    return true;
}

/**
 * This function is part of the username and password validation.  Only
 * ASCII characters are allowed with the exception of a space.
 */ 
bool AdminUtility::isOnlyASCIIAndNotSpace(const string &strval) {
    for (auto c: strval) {
        if (static_cast<unsigned char>(c) > 127 || static_cast<unsigned char>(c) == 32) {
            return false;
        }
    }

    return true;
}

/**
 * This function ecrypts a string using XOR encryption.
 */ 
string AdminUtility::encrypt(string msg) {
    string key = "Stroessenreuther";

    // Make sure the key is at least as long as the message
    std::string tmp(key);
    while (key.size() < msg.size()) {
        key += tmp;
    }

    // And now for the encryption part
    for (std::string::size_type i = 0; i < msg.size(); ++i) {
        msg[i] ^= key[i];
    }

    return msg;
}

/**
 * Decrypts a string that was encrypted with the function above.
 */ 
string AdminUtility::decrypt(string msg) {
    return AdminUtility::encrypt(msg); 
}

/**
 *
 */  
bool AdminUtility::isAthenticated(std::string &user, std::string &pass) {
    bool isAuth = false;
    std::ifstream adminFile(userAdminFile, std::fstream::in);
    if (adminFile.is_open()) {
        for (std::string line; std::getline(adminFile, line); ) {
            
            std::string userf = line.substr(0, line.find("::::"));
            std::string passf = decrypt(line.substr(line.find("::::") + 4));

            if (userf.compare(user) == 0 && passf.compare(pass) == 0) {
                isAuth = true;
                break;
            }
        }
        
        adminFile.close();
    }

    return isAuth;
}