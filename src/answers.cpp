
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/wx.h>
#include "answers.h"
#include "adminutility.h"

const long Answers::ID_STATICTEXT1 = wxNewId();
const long Answers::ID_TEXTCTRL1 = wxNewId();
const long Answers::ID_STATICTEXT2 = wxNewId();
const long Answers::ID_TEXTCTRL2 = wxNewId();
const long Answers::ID_BUTTON1 = wxNewId();
const long Answers::ID_BUTTON2 = wxNewId();

BEGIN_EVENT_TABLE(Answers,wxDialog)
	//(*EventTable(Answers)
	//*)
END_EVENT_TABLE()

Answers::Answers(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size) {
	//(*Initialize(Answers)
	wxGridBagSizer* dialogGridBagSizer;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX, _T("id"));
	Move(wxDefaultPosition);
	dialogGridBagSizer = new wxGridBagSizer(1, 1);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Records to Modify:"), wxDefaultPosition, wxSize(160,17), 0, _T("ID_STATICTEXT2"));
	dialogGridBagSizer->Add(StaticText2, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	answerTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(500,250), wxTE_MULTILINE|wxTE_DONTWRAP|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	dialogGridBagSizer->Add(answerTextCtrl, wxGBPosition(1, 0), wxGBSpan(1, 3), wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cancelButton = new wxButton(this, ID_BUTTON1, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	dialogGridBagSizer->Add(cancelButton, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	saveButton = new wxButton(this, ID_BUTTON2, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	dialogGridBagSizer->Add(saveButton, wxGBPosition(2, 2), wxDefaultSpan, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(dialogGridBagSizer);
	dialogGridBagSizer->Fit(this);
	dialogGridBagSizer->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Answers::OncancelButtonClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Answers::OnsaveButtonClick);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&Answers::OnClose);
	//*)

	// std::string testme = "hello this is a string\nWhat's going on \"with\" this.";
	// answerTextCtrl->SetValue(testme);
}

Answers::~Answers() {
	//(*Destroy(Answers)
	//*)
}


void Answers::OnClose(wxCloseEvent& event) {
	Destroy();
}

void Answers::OncancelButtonClick(wxCommandEvent& event) {
	Destroy();
}

void Answers::OnsaveButtonClick(wxCommandEvent& event) {
	AdminUtility au;

	//1) Check for Json validity.  Call the adminutility.
	//2) If valid, write fresh to the answers.json file.
	//3) Msgbox that says success or failure.
	//4) close window.
	if (au.IsJsonValid(answerTextCtrl->GetValue().ToStdString())) {
		std::cout << "It is valid json.\n"; 

		if (au.WriteJsonToFile(answerTextCtrl->GetValue().ToStdString())) {
			wxMessageBox("Changes were successfully saved.", 
            wxT("Successfully Saved"), wxICON_INFORMATION);

			Destroy();
		}
		else {
			wxMessageBox("There was a problem saving the file.", 
            wxT("Not Saved."), wxICON_INFORMATION);
		}
	}
	else {
 		wxMessageBox("Sorry, Changes were not saved.  This is not valid JSON.", 
            wxT("Invalid Json"), wxICON_INFORMATION);
	}


}
