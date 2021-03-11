#include <wx/filename.h>
#include <wx/colour.h>
#include <wx/image.h>
#include <string>
#include "chatbot.h"
#include "chatlogic.h"
#include "chatgui.h"
#include "adminutility.h"
#include "answers.h"

const long ChatBotFrame::ID_STATICTEXT1 = wxNewId();
const long ChatBotFrame::ID_USERCTRL1 = wxNewId();
const long ChatBotFrame::ID_ADMINLOGIN = wxNewId();
const long ChatBotFrame::ID_PASSWORDTEXT = wxNewId();
const long ChatBotFrame::ID_PASSTEXTCTRL = wxNewId();
const long ChatBotFrame::ID_ADDANSWERBUTTON = wxNewId();

// size of chatbot window
const int width = 414;
const int height = 736;

// wxWidgets APP
IMPLEMENT_APP(ChatBotApp);

std::string dataPath = "../";
std::string imgBasePath = dataPath + "images/";

bool ChatBotApp::OnInit() {
    // create window with name and show it
    ChatBotFrame *chatBotFrame = new ChatBotFrame(wxT("AdminChatBot - Logged in as Guest user."));
    chatBotFrame->Show(true);

    return true;
}

// wxWidgets FRAME
ChatBotFrame::ChatBotFrame(const wxString &title) : 
    wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(width, height), wxCLOSE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxCAPTION) {
    // create back panel.
    ChatBotFrameBackPanel *ctrlPanel = new ChatBotFrameBackPanel(this);
    wxFont font(9, wxFONTFAMILY_DEFAULT, wxNORMAL, wxNORMAL);

    //Set icon
    wxIcon iconBot; 
    wxBitmap bitmap(wxT("../images/bot.png"), wxBITMAP_TYPE_PNG); 
    iconBot.CopyFromBitmap(bitmap); 
    SetIcon(iconBot);
    
    // create controls and assign them to control panel
    _panelDialog = new ChatBotPanelDialog(ctrlPanel, wxID_ANY);
    this->SetChatLogic(_panelDialog->GetChatLogic());

    _topPanel = new wxPanel(ctrlPanel, wxID_ANY);
    _topPanel->SetBackgroundColour(wxColour(192, 192, 192));
    _topSizer = new wxGridSizer(2, 3, 1, 0);
    
    _userText = new wxStaticText(_topPanel, ID_STATICTEXT1, _("User Name:"), wxDefaultPosition, wxSize(84,25), 0, _T("ID_STATICTEXT1"));
    _topSizer->Add(_userText, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);

    _textCtrlUser = new wxTextCtrl(_topPanel, ID_USERCTRL1, wxEmptyString, wxDefaultPosition, wxSize(94,34), wxTAB_TRAVERSAL, wxDefaultValidator, _T("ID_USERCTRL1"));
    _topSizer->Add(_textCtrlUser, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    _adminLogin = new wxButton(_topPanel, ID_ADMINLOGIN, _("Admin Login"), wxDefaultPosition, wxSize(109,34), 0, wxDefaultValidator, _T("ID_ADMINLOGIN"));
    _adminLogin->SetFont(font);
    _topSizer->Add(_adminLogin, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    _passwordText = new wxStaticText(_topPanel, ID_PASSWORDTEXT, _("Password:"), wxDefaultPosition, wxSize(79,23), 0, _T("ID_PASSWORDTEXT"));
    _topSizer->Add(_passwordText, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);

    _passTextCtrl = new wxTextCtrl(_topPanel, ID_PASSTEXTCTRL, wxEmptyString, wxDefaultPosition, wxSize(96,34), wxTE_PASSWORD|wxTAB_TRAVERSAL, wxDefaultValidator, _T("ID_PASSTEXTCTRL"));
    _topSizer->Add(_passTextCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    _addAnswerButton = new wxButton(_topPanel, ID_ADDANSWERBUTTON, _("Modify Data"), wxDefaultPosition, wxSize(110,34), 0, wxDefaultValidator, _T("ID_ADDANSWERBUTTON"));
    _addAnswerButton->SetFont(font);
    _addAnswerButton->Disable();
    _topSizer->Add(_addAnswerButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    _topPanel->SetSizer(_topSizer);

    Connect(ID_ADMINLOGIN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ChatBotFrame::OnAdminLoginClick);
    Connect(ID_ADDANSWERBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ChatBotFrame::OnAddAnswerClick);
    _textCtrlUser->Connect(wxEVT_KEY_DOWN,(wxObjectEventFunction)&ChatBotFrame::OntopPanelKeyDown,0,this);
    _passTextCtrl->Connect(wxEVT_KEY_DOWN,(wxObjectEventFunction)&ChatBotFrame::OntopPanelKeyDown,0,this);

    // create text control for user input
    int idTextXtrl = 1;
    _userTextCtrl = new wxTextCtrl(ctrlPanel, idTextXtrl, "", wxDefaultPosition, wxSize(width, 50), wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);
    Connect(idTextXtrl, wxEVT_TEXT_ENTER, wxCommandEventHandler(ChatBotFrame::OnEnter));

    // create vertical sizer for panel alignment and add panels
    wxBoxSizer *vertBoxSizer = new wxBoxSizer(wxVERTICAL);
    vertBoxSizer->Add(_topPanel, 1, wxEXPAND, 0); 
    vertBoxSizer->Add(_panelDialog, 8, wxEXPAND | wxALL, 0);
    vertBoxSizer->Add(_userTextCtrl, 1, wxEXPAND | wxALL, 5);
    ctrlPanel->SetSizer(vertBoxSizer);

    // position window in screen center
    this->Centre();
}

void ChatBotFrame::OnAdminLoginClick(wxCommandEvent& event) {
    this->AuthenticateAdmin();
}

void ChatBotFrame::AuthenticateAdmin() {
    AdminUtility au;
    std::string userSend = std::string(_textCtrlUser->GetValue().mb_str());
    std::string passSend = std::string(_passTextCtrl->GetValue().mb_str());

    if (au.isAthenticated(userSend, passSend)) {
        if (_adminLogin->GetLabelText().compare("Admin Login") == 0) {
            this->SetTitle("AdminChatBot - Logged in as Admin User.");
            _addAnswerButton->Enable();   
            _adminLogin->SetLabelText("Log Off Admin");
             wxMessageBox( wxT("Successfully logged in"), 
                wxT("Admin"), wxICON_INFORMATION);

        }
    }
    else {
        if (_adminLogin->GetLabelText().compare("Admin Login") != 0) {
            this->SetTitle("AdminChatBot - Logged in as Guest user.");
            _addAnswerButton->Disable();   
            _adminLogin->SetLabelText("Admin Login");
            wxMessageBox( wxT("Successfully logged off"), 
                wxT("Guest"), wxICON_INFORMATION);
        }
        else {
            wxMessageBox( wxT("Sorry, you did not authenticate."), 
                wxT("Failure"), wxICON_INFORMATION);
        }
    }

    _passTextCtrl->SetValue("");
    _textCtrlUser->SetValue("");

}

void ChatBotFrame::OntopPanelKeyDown(wxKeyEvent& event) {
    int keycode = event.GetKeyCode();
    if (keycode == 9 && _textCtrlUser->HasFocus()) {
        _passTextCtrl->SetFocus();
    }
    else if (keycode == 9 && _passTextCtrl->HasFocus()) {
        _adminLogin->SetFocus();
    }
    else if (keycode == 13 && _passTextCtrl->HasFocus()) {
        this->AuthenticateAdmin();
    }
    else {
        event.Skip();
    }
}

void ChatBotFrame::OnAddAnswerClick(wxCommandEvent& event) {
    Answers aDialog(NULL);
    ChatLogic *chatLogic = this->GetChatLogic();
    AnswerNode *an = chatLogic->GetAnswerNode();

    aDialog.answerTextCtrl->SetValue("hello");
    aDialog.ShowModal();       
}

void ChatBotFrame::OnEnter(wxCommandEvent &WXUNUSED(event))
{
    // retrieve text from text control
    wxString userText = _userTextCtrl->GetLineText(0);

    // add new user text to dialog
    _panelDialog->AddDialogItem(userText, true);

    // delete text in text control
    _userTextCtrl->Clear();

    // send user text to chatbot 
    _panelDialog->GetChatLogicHandle()->SendMessageToChatbot(std::string(userText.mb_str()));
}

ChatBotFrameBackPanel::ChatBotFrameBackPanel(wxFrame *parent) : wxPanel(parent) {}

BEGIN_EVENT_TABLE(ChatBotPanelDialog, wxPanel)
EVT_PAINT(ChatBotPanelDialog::paintEvent) // catch paint events
END_EVENT_TABLE()

ChatBotPanelDialog::ChatBotPanelDialog(wxWindow *parent, wxWindowID id) : wxScrolledWindow(parent, id) {   
    // sizer will take care of determining the needed scroll size
    _dialogSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(_dialogSizer);

    // allow for PNG images to be handled
    wxInitAllImageHandlers();

    //// STUDENT CODE
    ////

    // create chat logic instance
    //_chatLogic = new ChatLogic(); 
    //_chatLogic = std::make_unique<ChatLogic>();

    // pass pointer to chatbot dialog so answers can be displayed in GUI
    _chatLogic->SetPanelDialogHandle(this);

    // load answer graph from file
    //_chatLogic->LoadAnswerGraphFromFile(dataPath + "src/answergraph.txt");

    //Load answers from Json file.
    _chatLogic->LoadAnswersFromJsonFile(dataPath + "data/answers.json");
    
    ////
    //// EOF STUDENT CODE
}

ChatBotPanelDialog::~ChatBotPanelDialog() {
    //// STUDENT CODE
    ////

    //delete _chatLogic; //Task 1. do not need this.

    ////
    //// EOF STUDENT CODE
}

void ChatBotPanelDialog::AddDialogItem(wxString text, bool isFromUser) {
    // add a single dialog element to the sizer
    ChatBotPanelDialogItem *item = new ChatBotPanelDialogItem(this, text, isFromUser);
    _dialogSizer->Add(item, 0, wxALL | (isFromUser == true ? wxALIGN_LEFT : wxALIGN_RIGHT), 8);
    _dialogSizer->Layout();

    // make scrollbar show up
    this->FitInside(); // ask the sizer about the needed size
    this->SetScrollRate(5, 5);
    this->Layout();

    // scroll to bottom to show newest element
    int dx, dy;
    this->GetScrollPixelsPerUnit(&dx, &dy);
    int sy = dy * this->GetScrollLines(wxVERTICAL);
    this->DoScroll(0, sy);
}

void ChatBotPanelDialog::PrintChatbotResponse(std::string response) {
    // convert string into wxString and add dialog element
    wxString botText(response.c_str(), wxConvUTF8);
    AddDialogItem(botText, false);
}

void ChatBotPanelDialog::paintEvent(wxPaintEvent &evt) {
    wxPaintDC dc(this);
    render(dc);
}

void ChatBotPanelDialog::paintNow() {
    wxClientDC dc(this);
    render(dc);
}

void ChatBotPanelDialog::render(wxDC &dc)
{
    wxImage image;
    image.LoadFile(imgBasePath + "winter_landscape.jpg");

    wxSize sz = this->GetSize();
    wxImage imgSmall = image.Rescale(sz.GetWidth(), sz.GetHeight(), wxIMAGE_QUALITY_HIGH);

    _image = wxBitmap(imgSmall);
    dc.DrawBitmap(_image, 0, 0, false);
}

ChatBotPanelDialogItem::ChatBotPanelDialogItem(wxPanel *parent, wxString text, bool isFromUser)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_NONE)
{
    // retrieve image from chatbot
    wxBitmap *bitmap = isFromUser == true ? nullptr : ((ChatBotPanelDialog*)parent)->GetChatLogicHandle()->GetImageFromChatbot(); 

    // create image and text
    _chatBotImg = new wxStaticBitmap(this, wxID_ANY, (isFromUser ? wxBitmap(imgBasePath + "user.png", wxBITMAP_TYPE_PNG) : *bitmap), wxPoint(-1, -1), wxSize(-1, -1));
    _chatBotTxt = new wxStaticText(this, wxID_ANY, text, wxPoint(-1, -1), wxSize(150, -1), wxALIGN_CENTRE | wxBORDER_NONE);
    _chatBotTxt->SetForegroundColour(isFromUser == true ? wxColor(*wxBLACK) : wxColor(*wxWHITE));

    // create sizer and add elements
    wxBoxSizer *horzBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    horzBoxSizer->Add(_chatBotTxt, 8, wxEXPAND | wxALL, 1);
    horzBoxSizer->Add(_chatBotImg, 2, wxEXPAND | wxALL, 1);
    this->SetSizer(horzBoxSizer);

    // wrap text after 150 pixels
    _chatBotTxt->Wrap(150);

    // set background color
    this->SetBackgroundColour((isFromUser == true ? wxT("YELLOW") : wxT("BLUE")));
}

