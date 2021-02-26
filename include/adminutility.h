#ifndef ADMINUTILITY_H_
#define ADMINUTILITY_H_

#include <iostream>
#include <vector>
#include <string>

class AdminUtility {
    public:
        const std::string userAdminFile{"../data/adminusers.txt"};
        const std::string userAdminFilePathLock{"../data/adminusers.lock"};

        //For debugging purposes
        //const std::string userAdminFilePathLock{"./data/adminusers.lock"};
        //const std::string userAdminFile{"./data/adminusers.txt"};

        bool isUserPassValid(std::string &user, std::string &pass, std::vector<std::string> *pdata);
        std::string encrypt(std::string msg);
        std::string decrypt(std::string msg);
        bool isAthenticated(std::string &user, std::string &pass);

    private: 
        bool isOnlyASCIIAndNotSpace(const std::string &strval);

};


#endif /* ADMINUTILITY_H_ */