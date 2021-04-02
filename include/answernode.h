#ifndef ANSWERNODE_H_
#define ANSWERNODE_H_

#include <vector>
#include "chatbot.h"
#include "adminutility.h"

//Structure for answer json data.
struct AnswerRec {
    std::vector<std::string> keywords;
    std::string answer;
};

/**
 * The AnswerNode class is declared as a unique pointer in the ChatLogic class.
 * This unique pointer is moved around the application as needed.  The class
 * holds the ongoing dynamic Json data throughout the application. 
 */
class AnswerNode {
    public:
        const std::string GREETING_MSG = "Welcome to the Admin Chatbot Demonstration. With the appropriate credentials, new Answers and keywords can be added to the chatbot data file.";
        void SetAnswerRecs(std::vector<AnswerRec> answerRecs) {_answerRecs = answerRecs; }
        std::vector<AnswerRec> GetAnswerRecs() {return _answerRecs; }
        void MoveChatbotHere(ChatBot chatbot);
        void SetDisplayGreeting(bool displayGreeting) {_displayGreeting = displayGreeting;}
        bool IsDisplayGreeting() {return _displayGreeting;}
        void SetCurrentAnswerRec(AnswerRec currentAnswerRec) {_currentAnswerRec = currentAnswerRec;}
        AnswerRec GetCurrentAnswerRec() {return _currentAnswerRec; }
        void SetRawJsonData(std::string jsonData) {_jsonData = jsonData;}
        std::string GetRawJsonData() {return _jsonData;}
        bool CheckAndUpdateFileJson(std::string filename);
        int GetCurrentJsonFileDate() {return _fileDate;}
        int GetFileDate() {return _fileDate;}
        void SetFileDate(int fileDate) {_fileDate = fileDate;}

    private:
        std::vector<AnswerRec> _answerRecs;
        ChatBot _chatBot;
        AnswerRec _currentAnswerRec;
        bool _displayGreeting;
        std::string _jsonData;
        int _fileDate;
};



#endif /* ANSWERNODE_H_ */