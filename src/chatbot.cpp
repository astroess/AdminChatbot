#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>

#include "chatlogic.h"
#include "chatbot.h"
#include "answernode.h"
#include "adminutility.h"

ChatBot::ChatBot() {
    _image = nullptr;
    _chatLogic = nullptr;
    _answerNode = nullptr;
}

ChatBot::ChatBot(std::string filename) {
    _chatLogic = nullptr;
    _answerNode = nullptr;

    // load image into heap memory
    _image = new wxBitmap(filename, wxBITMAP_TYPE_PNG);
}

ChatBot::~ChatBot() {

    // deallocate heap memory
    // wxWidgets uses NULL and not nullptr
    if(_image != NULL) {
        delete _image;
        _image = NULL;
    }
}

ChatBot::ChatBot(const ChatBot &source) {
    _answerNode = source._answerNode;
    _chatLogic = source._chatLogic;
    _image = source._image;

}

/**
 * Copy Assignment Operator 
 */ 
ChatBot &ChatBot::operator=(const ChatBot &source) {
    if (this == &source) 
        return *this;
    
    if(_image != NULL) 
        delete _image;

    _image = new wxBitmap(*source._image);
    _answerNode = source._answerNode;
    _chatLogic = source._chatLogic;
    _chatLogic->SetChatbotHandle(this);

    return *this;
}

/**
 * Move Constructor
 */ 
ChatBot::ChatBot(ChatBot &&source) {
    _answerNode = source._answerNode;
    _chatLogic = source._chatLogic;
    _image = source._image;

    _chatLogic->SetChatbotHandle(this);

    source._answerNode = nullptr;
    source._chatLogic = nullptr;    
    delete source._image;
    source._image = NULL;

}

/**
 * Move Assignment Operator
 */ 
ChatBot &ChatBot::operator=(ChatBot &&source) {
    if (this == &source)
        return *this;

    if(_image != NULL) 
         delete _image;

    _image = new wxBitmap(*source._image);
    _answerNode = source._answerNode;
    _chatLogic = source._chatLogic;
    
    _chatLogic->SetChatbotHandle(this);

    source._answerNode = nullptr;
    source._chatLogic = nullptr;    
    source._image = NULL;

    return *this;
}

/**
 * Function to interpret message from user by calling the
 * ComputeLevenshteinDistance function.
 */
void ChatBot::ReceiveMessageFromUser(std::string message) {
    typedef std::pair<std::string, int> AnswerPair;
    std::vector<AnswerPair> answerPairValues;

    for (AnswerRec ar : _answerNode->GetAnswerRecs()) {
        for (std::string keyword : ar.keywords) {
            AnswerPair ap{ar.answer, ComputeLevenshteinDistance(keyword, message)};
            answerPairValues.emplace_back(ap);
        }
    }

    std::sort(answerPairValues.begin(), answerPairValues.end(), [](const AnswerPair &a, const AnswerPair &b) { return a.second < b.second; });
    
    //Add a Random element if the there is more than one lowest value.
    int tempVal = answerPairValues.at(0).second;
    int icount;
    for (icount=0; icount < answerPairValues.size(); icount++) {
        AnswerPair tmpPair = answerPairValues.at(icount);
        if (tempVal < tmpPair.second) {
            break;
        }
    }

    if (icount == 1) {
        _chatLogic->SendMessageToUser(answerPairValues.at(0).first);
    }
    else {
        //Randomize.
        AdminUtility au;
        _chatLogic->SendMessageToUser(answerPairValues.at(au.GetRandomizedNumBetween(0, icount - 1)).first);
    }
    
    answerPairValues.clear();
}

/**
 * Sets the current message.  If it is the first time being called, 
 * the general greeting message is displayed.
 */
void ChatBot::SetCurrentMessage() {
    
    if (_answerNode->IsDisplayGreeting()) {
        _chatLogic->SendMessageToUser(_answerNode->GREETING_MSG);
        _answerNode->SetDisplayGreeting(false);
    }
    else {

        _chatLogic->SendMessageToUser("");
    }
}

/**
 * Levenshtein distance calculation of the difference between 2 strings.
 */
int ChatBot::ComputeLevenshteinDistance(std::string s1, std::string s2) {
    // convert both strings to upper-case before comparing
    std::transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
    std::transform(s2.begin(), s2.end(), s2.begin(), ::toupper);

    // compute Levenshtein distance measure between both strings
    const size_t m(s1.size());
    const size_t n(s2.size());

    if (m == 0)
        return n;
    if (n == 0)
        return m;

    size_t *costs = new size_t[n + 1];

    for (size_t k = 0; k <= n; k++)
        costs[k] = k;

    size_t i = 0;
    for (std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i) {
        costs[0] = i + 1;
        size_t corner = i;

        size_t j = 0;
        for (std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j) {
            size_t upper = costs[j + 1];
            if (*it1 == *it2) {
                costs[j + 1] = corner;
            }
            else {
                size_t t(upper < corner ? upper : corner);
                costs[j + 1] = (costs[j] < t ? costs[j] : t) + 1;
            }

            corner = upper;
        }
    }

    int result = costs[n];
    delete[] costs;

    return result;
}