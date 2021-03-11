#ifndef ANSWERS_H_
#define ANSWERS_H_

//(*Headers(Answers)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/gbsizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include "answernode.h"
//*)

class Answers: public wxDialog
{
	public:

		Answers(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~Answers();

		//(*Declarations(Answers)
		wxButton* cancelButton;
		wxButton* saveButton;
		//wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxTextCtrl* answerTextCtrl;
		//wxTextCtrl* keyTextCtrl;
		//*)

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
		//(*Handlers(Answers)
		void OnClose(wxCloseEvent& event);
		void OncancelButtonClick(wxCommandEvent& event);
		void OnsaveButtonClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};



#endif /* ANSWERS_H_ */