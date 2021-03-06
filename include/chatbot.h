#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <wx/bitmap.h>
#include <string>
#include <vector>

class GraphNode; // forward declaration
class ChatLogic; // forward declaration
class AnswerNode; //forward declaration

class ChatBot
{
private:
    // data handles (owned)
    wxBitmap *_image; // avatar image

    // data handles (not owned)
    GraphNode *_currentNode;
    GraphNode *_rootNode;
    ChatLogic *_chatLogic;
    AnswerNode *_answerNode;

    // proprietary functions
    int ComputeLevenshteinDistance(std::string s1, std::string s2);

public:
    // constructors / destructors
    ChatBot();                     // constructor WITHOUT memory allocation
    ChatBot(std::string filename); // constructor WITH memory allocation
    
    // Rule 1. Destructor.
    ~ChatBot(); 
    //// STUDENT CODE
    ////
    //Rule 2. Copy Constructor.
    ChatBot(const ChatBot &source);
    
    //Rule 3. Copy Assignment Operator.
    ChatBot &operator=(const ChatBot &source);

    //Rule 4. Move Constructor.
    ChatBot(ChatBot &&source);

    //Rule 5. Move Assignment Operator.    
    ChatBot &operator=(ChatBot &&source);

    ////
    //// EOF STUDENT CODE

    // getters / setters
    void SetCurrentNode(GraphNode *node);
    void SetCurrentNode(AnswerNode *answerNode);
    void SetRootNode(GraphNode *rootNode) { _rootNode = rootNode; }
    void SetAnswerNode(AnswerNode *answerNode) {_answerNode = answerNode;}
    void SetChatLogicHandle(ChatLogic *chatLogic) { _chatLogic = chatLogic; }
    wxBitmap *GetImageHandle() { return _image; }

    // communication
    void ReceiveMessageFromUser(std::string message);
};

#endif /* CHATBOT_H_ */