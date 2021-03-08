#include <iostream>
#include "answernode.h"
#include "chatbot.h"


void AnswerNode::MoveChatbotHere(ChatBot chatbot) {
    _chatBot = std::move(chatbot);
    _chatBot.SetCurrentMessage();
}