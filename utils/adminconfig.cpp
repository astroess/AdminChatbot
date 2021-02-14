#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;
using std::cout;
using std::cin;

void exampleJson();
void processAddAdminUser();
void processAddCategories();

int main() {
    bool continueParentLoop;
    std::string pVal;

    cout << "***Welcome to the Admin Configuration Tool for the AdminChatbot***\n\n";    

    do {
        continueParentLoop = false;
        cout << "Please select 1. for \"Admin Users\" or 2. \"Categories\" or Q to quit.\n";
        cout << "1. AdminUsers\n";
        cout << "2. Categories\n";
        cout << "Q. Quit\n";
        cout << "$ ";

        cin >> pVal;
        cout << "\n";
        if (pVal.compare("Q") == 0 || pVal.compare("q") == 0) {
            break;
        }

        if (cin.fail() || (pVal.compare("1") != 0 && pVal.compare("2") != 0)) {
            continueParentLoop = true;
        }
        else if (pVal.compare("1") == 0) {
            processAddAdminUser();
        }
        else if (pVal.compare("2") == 0) {
            processAddCategories();
        }
        
        cin.clear();
    } while (continueParentLoop);

    cout << "***Thanks for Playing!!***\n\n";

    return 0;
}

void processAddAdminUser() {
    cout << "Got to processAddAdminUser()\n";
}

void processAddCategories() {
    cout << "Got to processAddCategories()\n";
}

void exampleJson() {

    // 1. Parse a JSON string into DOM.
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    Document d;
    d.Parse(json);
 
    // 2. Modify it by DOM.
    Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);
 
    // 3. Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
 
    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;

}