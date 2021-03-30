#ifndef ADMINUTILITY_H_
#define ADMINUTILITY_H_

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "answernode.h"

struct AnswerRec;

/**
 * Utility class for both the adminusers and adminChatbot applications. Descriptions
 * for class methods/functions are on the adminutility.cpp implementation.
 */ 
class AdminUtility {
    public:
        std::unique_ptr<std::string> _jsonData = std::make_unique<std::string>();

        const std::string userAdminFile{"../data/adminusers.txt"};
        const std::string userAdminFilePathLock{"../data/adminusers.lock"};
        const std::string dataPath = "../";
        const std::string imgBasePath = dataPath + "images/";

        bool isUserPassValid(std::string &user, std::string &pass, std::vector<std::string> *pdata);
        std::string encrypt(std::string msg);
        std::string decrypt(std::string msg);
        bool isAthenticated(std::string &user, std::string &pass);
        int GetRandomizedNumBetween(int first, int second);
        std::vector<AnswerRec> GetAnswerRecsFromFile(std::string filename);
        std::string* GetJsonFromAnswerRecs();
        bool IsJsonValid(std::string json);
        bool WriteJsonToFile(std::string filename);

    private: 
        bool isOnlyASCIIAndNotSpace(const std::string &strval);

};


#endif /* ADMINUTILITY_H_ */