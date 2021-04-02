#ifndef ANSWERS_H_
#define ANSWERS_H_

#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/gbsizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include "answernode.h"

/**
 * The Answers class holds the wxWidgets initializations for the Answers dialog in 
 * the application.  The dialog allows an Admin user to modify the data.
 */
class Answers: public wxDialog {
	public:

		Answers(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~Answers();

		wxButton* cancelButton;
		wxButton* saveButton;
		wxStaticText* StaticText2;
		wxTextCtrl* answerTextCtrl;
		void SetAnswerNode(AnswerNode *answerNode) {_answerNode = answerNode;}
		
	protected:

		//(*Identifiers(Answers)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:
		AnswerNode *_answerNode;
		//(*Handlers(Answers)
		void OnClose(wxCloseEvent& event);
		void OncancelButtonClick(wxCommandEvent& event);
		void OnsaveButtonClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif /* ANSWERS_H_ */