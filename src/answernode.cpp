#include <iostream>
#include <thread>
#include "answernode.h"
#include "chatbot.h"


/**
 * This member function moves that chatbot instance to AnswerNode.
 */
void AnswerNode::MoveChatbotHere(ChatBot chatbot) {
    _chatBot = std::move(chatbot);
    _chatBot.SetCurrentMessage();
}

/**
 * Checks to make sure the Json file is present, and then sets the
 * filedate for future file checks.
 */
bool AnswerNode::CheckAndUpdateFileJson(std::string filename) {
    struct stat st;
    
    int ierr = stat (filename.c_str(), &st);

    if (ierr != 0) {
        std::cerr << "Error with Json Data File.";
        return false;
    }
    else {
        _fileDate = st.st_mtime;
        return true;
    }
}
