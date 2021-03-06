#ifndef ANSWERNODE_H_
#define ANSWERNODE_H_

#include <vector>
#include "chatlogic.h"
#include "chatbot.h"

class AnswerNode {
    public:
        const std::string GREETING_MSG = R"("Welcome to the Admin Chatbot Demonstration.
            With the appropriate credentials, new Answers and keywords can
            be added to the data file.")";
        void SetAnswerRecs(std::vector<AnswerRec> *answerRecs) {_answerRecs = answerRecs; }
        std::vector<AnswerRec>* GetAnswerRecs() {return _answerRecs; }
        void MoveChatbotHere(ChatBot chatbot);


    private:
        std::vector<AnswerRec>* _answerRecs;
        ChatBot _chatBot;
};



#endif /* ANSWERNODE_H_ */