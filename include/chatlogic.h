#ifndef CHATLOGIC_H_
#define CHATLOGIC_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <vector>
#include <string>
#include "chatgui.h"
#include "answernode.h"

// forward declarations
class ChatBot;

class ChatLogic {
    public:
        // constructor / destructor
        ChatLogic();
        ~ChatLogic();

        // getter / setter
        void SetPanelDialogHandle(ChatBotPanelDialog *panelDialog);
        void SetChatbotHandle(ChatBot *chatbot);

        // proprietary functions
        void LoadAnswerGraphFromFile(std::string filename);  //Old
        void LoadAnswersFromJsonFile(std::string filename);
        void RunDataSynchronization(std::string filename);
        void SendMessageToChatbot(std::string message);
        void SendMessageToUser(std::string message);
        AnswerNode *GetAnswerNode() {return _answerNode.get();}
        wxBitmap *GetImageFromChatbot();

    private:
        std::unique_ptr<AnswerNode> _answerNode = std::make_unique<AnswerNode>();
        bool _running = false; // set to stop thread
        bool _closed = false; // set by thread to indicate it ended

        // data handles
        ChatBot *_chatBot;
        ChatBotPanelDialog *_panelDialog;
    
        // proprietary type definitions
        typedef std::vector<std::pair<std::string, std::string>> tokenlist;

        // proprietary functions
        template <typename T>
        void AddAllTokensToElement(std::string tokenID, tokenlist &tokens, T &element);
};

#endif /* CHATLOGIC_H_ */