#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <wx/bitmap.h>
#include <string>
#include <vector>

class ChatLogic; // forward declaration
class AnswerNode; //forward declaration

class ChatBot {
    public:
        // constructors / destructors
        ChatBot();                     // constructor WITHOUT memory allocation
        ChatBot(std::string filename); // constructor WITH memory allocation
        ~ChatBot(); 
        
        //Copy Constructor.
        ChatBot(const ChatBot &source);
    
        //Copy Assignment Operator.
        ChatBot &operator=(const ChatBot &source);

        //Move Constructor.
        ChatBot(ChatBot &&source);

        //Move Assignment Operator.    
        ChatBot &operator=(ChatBot &&source);

        // getters / setters
        void SetCurrentMessage();
        void SetAnswerNode(AnswerNode *answerNode) {_answerNode = answerNode;}
        void SetChatLogicHandle(ChatLogic *chatLogic) { _chatLogic = chatLogic; }
        wxBitmap *GetImageHandle() { return _image; }

        // communication
        void ReceiveMessageFromUser(std::string message);

    private:
        // data handles (owned)
        wxBitmap *_image; // avatar image

        // data handles (not owned)
        ChatLogic *_chatLogic;
        AnswerNode *_answerNode;

        // proprietary functions
        int ComputeLevenshteinDistance(std::string s1, std::string s2);
};

#endif /* CHATBOT_H_ */