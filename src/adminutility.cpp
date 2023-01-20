#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

#include "adminutility.h"

using std::string;
using namespace rapidjson;

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

    //Check for duplicates again.
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
 * Checks the adminusers.txt file to see if the user can authenticate.
 * If the users doesn't exist, false is returned.
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

/**
 * Calculates random number between to ints.
 */ 
int AdminUtility::GetRandomizedNumBetween(int first, int second) {
    std::random_device rd;  
    std::mt19937 gen(rd()); //Seeded with rd()
    std::uniform_int_distribution<> distrib(first, second);
 
    return distrib(gen);

}

/**
 * Loads the answer records from the answers.json file and returns a Vector
 * of AnswerRec stuctures.
 */
std::vector<AnswerRec> AdminUtility::GetAnswerRecsFromFile(std::string filename) {
    std::ifstream answersFile(filename, std::fstream::in);
    std::vector<AnswerRec> answerRecs;
    
    if (!answersFile.is_open()) {
        std::cerr << "Could not open file for reading!\n";
    }

    IStreamWrapper answerStream {answersFile};

    //Put Document And data struncture on the heap.
    std::unique_ptr<Document> answersDoc = std::make_unique<Document>();

    answersDoc->ParseStream(answerStream);
    if (answersDoc->HasParseError()) {
        std::cout << "Error  : " << answersDoc->GetParseError()  << '\n'
                  << "Offset : " << answersDoc->GetErrorOffset() << '\n';
        answersFile.close();
    }

    AnswerRec ar;
    for (auto const& p : (*answersDoc)["data"].GetArray()) {
        for (auto const& in : p["keywords"].GetArray()) {
            ar.keywords.emplace_back(in.GetString());
        }
        ar.answer = p["answer"].GetString();
        answerRecs.emplace_back(ar);

        ar.answer = "";
        ar.keywords.clear();
    }

    //Add raw data field to class.
    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);
    answersDoc->Accept(writer);
    *_jsonData = buffer.GetString();

    return answerRecs;
}

/**
 * Return the AnswerRecs as a Json data string pointer.  
 */
std::string* AdminUtility::GetJsonFromAnswerRecs() {
    return _jsonData.get();
}

/**
 * Method/function to determine if a Json string is valid.
 */
bool AdminUtility::IsJsonValid(std::string json) {
    Document jsonDoc;

    jsonDoc.Parse(json.c_str());
    if (jsonDoc.HasParseError()) {
        return false;
    }
    else {
        return true;
    }
}

/**
 * Method/function to write data to the answers.json file.  This method gets
 * called when there is a change in the json data in memory.
 */
bool AdminUtility::WriteJsonToFile(std::string jsonData) {
    
    std::ofstream dfile(dataPath + "data/answers.json");
    if (dfile.is_open()) {
        dfile << jsonData;
        return true;
    }
    else {
        return false;
    }
}