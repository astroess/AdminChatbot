#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream> 
#include <memory>
#include <algorithm>
#include <signal.h>

using std::cout;
using std::cin;
using std::string;

bool processAddAdminUser(std::vector<string> *pdata);
void processListAdminUser();
void processDeleteAdminUser();
bool loadAdminFile(std::vector<string> *admindata);
void createLockFile();
bool isLockFilePresent();
bool writeOutAdminFile(std::vector<string> *admindata);
bool isUserPassValid(string &user, string &pass, std::vector<string> *pdata);
bool isOnlyASCIIAndNotSpace(const std::string &strval);
std::string encrypt(std::string msg);
std::string decrypt(std::string msg);

//const std::string userAdminFilePathLock{"../data/adminusers.lock"};
//const std::string userAdminFile{"../data/adminusers.txt"};
//For debugging purposes
const std::string userAdminFilePathLock{"./data/adminusers.lock"};
const std::string userAdminFile{"./data/adminusers.txt"};

void signal_callback_handler(int signum) {
    cout << "Please type \"Q\" to exit program." << "\n";
}
/**
 */ 
int main() {
    signal(SIGINT, signal_callback_handler);
    bool continueParentLoop;
    std::string pVal;
    std::unique_ptr<std::vector<string>> admindata = std::make_unique<std::vector<string>>();

    cout << "***Welcome to the Admin User Configuration Tool for the AdminChatbot***\n\n";    
    if (isLockFilePresent()) {
        _Exit(-1);
    }

    do {
        continueParentLoop = false;
        cout << "Please select one of the following numbers 3 numbers (type actual number), \n or Q to quit.\n";
        cout << "1. Add Admin User\n";
        cout << "2. Delete Admin User\n";
        cout << "3. List Current Admin Users\n";
        cout << "Q. Quit\n";
        cout << "$ ";

        cin >> pVal;
        cout << "\n";
        if (pVal.compare("Q") == 0 || pVal.compare("q") == 0) {
            break;
        }

        if (cin.fail() || (pVal.compare("1") != 0 && pVal.compare("2") != 0) &&
                           pVal.compare("3") != 0) {
            continueParentLoop = true;
        }
        else {
            //Create lock file
            createLockFile();

            //Then load file.
            if (!loadAdminFile(admindata.get())) {
                cout << "There was a problem opening the adminUsers file.\n";      
            }
        }
        
        if (pVal.compare("1") == 0) {
            continueParentLoop = processAddAdminUser(admindata.get());
        }
        else if (pVal.compare("2") == 0) {
            processDeleteAdminUser();
        }
        else if (pVal.compare("3") == 0) {
            processListAdminUser();
        }
        
        cin.clear();
    } while (continueParentLoop);

    //Write out adminusers file.
    if (!writeOutAdminFile(admindata.get())) {
        std::cerr << "There was a problem writing the admin user's data to the file.\n";
    }
    else {
        cout << "***Thanks. The adminusers utility program has ended.***\n\n";
    }

    //Remove lock file.
    remove(userAdminFilePathLock.c_str());

    return 0;
}

//Implementation
bool processAddAdminUser(std::vector<string> *pdata) {
    string uname, pass, qvar;
    bool continueAddLoop;

    do {
        continueAddLoop = false;
        cout << "User Name (between 8 and 12 ASCII characters): ";
        cin >> uname;
        cout << "Password (between 8 and 12 ASCII characters): ";
        cin >> pass;

        if (!isUserPassValid(uname, pass, pdata)) {
            cout << "Either the user name or password did not pass validation.\n";
            continueAddLoop = true;
        }

    } while(continueAddLoop);

    pdata->emplace_back(uname + "::::" + encrypt(pass));
    cout << "\nAdmin User has been added.\n\n";

    return true;
}

void processListAdminUser() {
    cout << "Got to processListAdminUser()\n";
}

void processDeleteAdminUser() {
    cout << "Got to processDeleteAdminUser()\n";

}

bool isUserPassValid(string &user, string &pass, std::vector<string> *pdata) {
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
        std::string delimiter = "::::";
        std::string ucheck = itr.substr(0, itr.find(delimiter)); 

        if (user.compare(ucheck) == 0) {
            return false;
        }
    }

    return true;
}

void createLockFile() {
    std::fstream fs;
    fs.open(userAdminFilePathLock, std::ios::out);
    fs.close();
}

bool isOnlyASCIIAndNotSpace(const std::string &strval) {
    for (auto c: strval) {
        if (static_cast<unsigned char>(c) > 127 || static_cast<unsigned char>(c) == 32) {
            return false;
        }
    }

    return true;
}

bool isLockFilePresent() {
    
    if (FILE *file = fopen(userAdminFilePathLock.c_str(), "r")) {
        cout << "Sorry, lock file is still present.  This means that someone else is running this program, \n";
        cout << "Or the file was left there due to a previous crash. To continue, please remove it if you know that\n";
        cout << "you're the only person using the adminusers utility.\n\n";
        cout << "Path of lock file is: " + userAdminFilePathLock + "\n\n";
        fclose(file);

        return true;
    }
    else {
        return false;
    }
}

bool loadAdminFile(std::vector<string> *pdata) {
    std::ifstream adminFile(userAdminFile, std::fstream::in);
    if (adminFile.is_open()) {
        for (std::string line; std::getline(adminFile, line); ) {
            pdata->emplace_back(line);
        }
        
        adminFile.close();
        return true;
    }
    else {
        std::cerr << "adminusers file could not be opened." << "\n";
        return false;
    }
    
}

/**
 * XOR encryption
 */ 
std::string encrypt(std::string msg) {
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

std::string decrypt(std::string msg) {
    return encrypt(msg); // lol
}

bool writeOutAdminFile(std::vector<string> *admindata) {
    std::fstream outData(userAdminFile, std::ios::out | std::ios::trunc);
    
    if (outData) {
        for (string itr : *admindata) {
            outData << itr;
            outData << "\n";
        }

        outData.close();
        return true;
    }
    else {
        std::cerr << "adminusers file could not be opened." << "\n";
        return false;
    }
}
