#include <iostream>
#include "answernode.h"
#include "chatbot.h"


void AnswerNode::MoveChatbotHere(ChatBot chatbot) {
    _chatBot = std::move(chatbot);
    _chatBot.SetCurrentMessage();
}

bool AnswerNode::CheckAndUpdateFileJson(std::string filename) {
    struct stat st;
    
    int ierr = stat (filename.c_str(), &st);

    if (ierr != 0) {
        std::cout << "error";
        return false;
    }
    else {
        _fileDate = st.st_mtime;

        return true;
    }
}
