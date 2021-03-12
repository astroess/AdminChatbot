#ifndef ANSWERNODE_H_
#define ANSWERNODE_H_

#include <vector>
#include "chatbot.h"

//Structure for answer json data.
struct AnswerRec {
    std::vector<std::string> keywords;
    std::string answer;
};

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

    private:
        std::vector<AnswerRec> _answerRecs;
        ChatBot _chatBot;
        AnswerRec _currentAnswerRec;
        bool _displayGreeting;
        std::string _jsonData;
};



#endif /* ANSWERNODE_H_ */