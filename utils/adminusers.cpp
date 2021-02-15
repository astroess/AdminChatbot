#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream> 

using std::cout;
using std::cin;
using std::string;

void processAddAdminUser(std::vector<string> *pdata);
void processListAdminUser();
void processDeleteAdminUser();
bool loadAdminFile(std::ifstream *adminFile, std::vector<string> *admindata);

const std::string userAdminFilePath{"./data/adminusers.txt"};

int main() {
    bool continueParentLoop;
    std::string pVal;
    std::ifstream adminFile;
    std::vector<string> admindata;

    cout << "***Welcome to the Admin User Configuration Tool for the AdminChatbot***\n\n";    

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
            //take backup of file.
            //Then load file.
            if (!loadAdminFile(&adminFile, &admindata)) {
                cout << "There was a problem opening the adminUsers file.\n";
                return -1;
            }
        }
        
        if (pVal.compare("1") == 0) {
            processAddAdminUser(&admindata);
        }
        else if (pVal.compare("2") == 0) {
            processDeleteAdminUser();
        }
        else if (pVal.compare("3") == 0) {
            processListAdminUser();
        }
        
        //Resave the new list.

        cin.clear();
    } while (continueParentLoop);

    cout << "***Thanks for Playing!!***\n\n";

    return 0;
}

//Implementation
void processAddAdminUser(std::vector<string> *pdata) {

}

void processListAdminUser() {
    cout << "Got to processListAdminUser()\n";
}

void processDeleteAdminUser() {
    cout << "Got to processDeleteAdminUser()\n";

// while (getline(fin,line))
// {
//     line.replace(line.find(deleteline),deleteline.length(),"");
//     temp << line << endl;

// }

}

bool doesSettingsFileExist() {
    return false;
}

bool loadAdminFile(std::ifstream *adminFile, std::vector<string> *pdata) {
    adminFile->open(userAdminFilePath, std::fstream::in | std::fstream::out | std::fstream::app);
    if (adminFile->is_open()) {
        for (std::string line; std::getline(*adminFile, line); ) {
            cout << line << "\n";
            pdata->emplace_back(line);
        }

        return true;
    }
    else {
        std::cerr << "adminusers file could not be opened." << "\n";
        return false;
    }
       
}

// void eraseFileLine(std::string path, std::string eraseLine) {
//     std::string line;
//     std::ifstream fin;
    
//     fin.open(path);
//     // contents of path must be copied to a temp file then
//     // renamed back to the path file
//     std::ofstream temp;
//     temp.open("temp.txt");

//     while (getline(fin, line)) {
//         // write all lines to temp other than the line marked for erasing
//         if (line != eraseLine)
//             temp << line << std::endl;
//     }

//     temp.close();
//     fin.close();

//     // required conversion for remove and rename functions
//     const char * p = path.c_str();
//     remove(p);
//     rename("temp.txt", p);
// }

// void exampleJson() {

//     // 1. Parse a JSON string into DOM.
//     const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
//     Document d;
//     d.Parse(json);
 
//     // 2. Modify it by DOM.
//     Value& s = d["stars"];
//     s.SetInt(s.GetInt() + 1);
 
//     // 3. Stringify the DOM
//     StringBuffer buffer;
//     Writer<StringBuffer> writer(buffer);
//     d.Accept(writer);
 
//     // Output {"project":"rapidjson","stars":11}
//     std::cout << buffer.GetString() << std::endl;

// }