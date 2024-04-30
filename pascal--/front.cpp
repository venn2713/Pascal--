#include "front.h"


MyFrame5::MyFrame5(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxSize(700, 500), wxDefaultSize);
	this->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DDKSHADOW));

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer(wxVERTICAL);

	m_scintilla2 = new wxStyledTextCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxEmptyString);
	m_scintilla2->SetUseTabs(true);
	m_scintilla2->SetTabWidth(4);
	m_scintilla2->SetIndent(4);
	m_scintilla2->SetTabIndents(true);
	m_scintilla2->SetBackSpaceUnIndents(true);
	m_scintilla2->SetViewEOL(false);
	m_scintilla2->SetViewWhiteSpace(false);
	m_scintilla2->SetMarginWidth(2, 0);
	m_scintilla2->SetIndentationGuides(true);
	m_scintilla2->SetReadOnly(false);
	m_scintilla2->SetMarginType(1, wxSTC_MARGIN_SYMBOL);
	m_scintilla2->SetMarginMask(1, wxSTC_MASK_FOLDERS);
	m_scintilla2->SetMarginWidth(1, 16);
	m_scintilla2->SetMarginSensitive(1, true);
	m_scintilla2->SetProperty(wxT("fold"), wxT("1"));
	m_scintilla2->SetFoldFlags(wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);
	m_scintilla2->SetMarginType(0, wxSTC_MARGIN_NUMBER);
	m_scintilla2->SetMarginWidth(0, m_scintilla2->TextWidth(wxSTC_STYLE_LINENUMBER, wxT("_99999")));
	m_scintilla2->MarkerDefine(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS);
	m_scintilla2->MarkerSetBackground(wxSTC_MARKNUM_FOLDER, wxColour(wxT("BLACK")));
	m_scintilla2->MarkerSetForeground(wxSTC_MARKNUM_FOLDER, wxColour(wxT("WHITE")));
	m_scintilla2->MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS);
	m_scintilla2->MarkerSetBackground(wxSTC_MARKNUM_FOLDEROPEN, wxColour(wxT("BLACK")));
	m_scintilla2->MarkerSetForeground(wxSTC_MARKNUM_FOLDEROPEN, wxColour(wxT("WHITE")));
	m_scintilla2->MarkerDefine(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY);
	m_scintilla2->MarkerDefine(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS);
	m_scintilla2->MarkerSetBackground(wxSTC_MARKNUM_FOLDEREND, wxColour(wxT("BLACK")));
	m_scintilla2->MarkerSetForeground(wxSTC_MARKNUM_FOLDEREND, wxColour(wxT("WHITE")));
	m_scintilla2->MarkerDefine(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS);
	m_scintilla2->MarkerSetBackground(wxSTC_MARKNUM_FOLDEROPENMID, wxColour(wxT("BLACK")));
	m_scintilla2->MarkerSetForeground(wxSTC_MARKNUM_FOLDEROPENMID, wxColour(wxT("WHITE")));
	m_scintilla2->MarkerDefine(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY);
	m_scintilla2->MarkerDefine(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY);
	m_scintilla2->SetSelBackground(true, wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
	m_scintilla2->SetSelForeground(true, wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));
	m_scintilla2->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	m_scintilla2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	bSizer13->Add(m_scintilla2, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);

	m_panel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_panel2->SetFont(wxFont(9, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Bauhaus 93")));
	m_panel2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNSHADOW));

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	fgSizer1->SetFlexibleDirection(wxBOTH);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* m_staticText11;
	m_staticText11 = new wxStaticText(m_panel2, wxID_ANY, wxT("   Debug line:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText11->Wrap(-1);
	m_staticText11->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));
	m_staticText11->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNSHADOW));
	m_staticText11->SetMinSize(wxSize(-1, 20));


	fgSizer1->Add(m_staticText11, 0, wxEXPAND, 5);


	m_panel2->SetSizer(fgSizer1);
	m_panel2->Layout();
	fgSizer1->Fit(m_panel2);
	bSizer2->Add(m_panel2, 1, wxALL | wxEXPAND, 5);

	m_button1 = new wxButton(this, wxID_ANY, wxT("Run"), wxPoint(20, 20), wxDefaultSize, 0);
	m_button1->SetForegroundColour(wxColour(0, 128, 0));
	m_button1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));

	bSizer2->Add(m_button1, 0, wxALIGN_CENTER | wxALL, 5);

	m_panel3 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_panel3->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNSHADOW));

	bSizer2->Add(m_panel3, 1, wxEXPAND | wxALL, 5);


	bSizer13->Add(bSizer2, 0, wxEXPAND, 20);

	m_staticText10 = new wxStaticText(this, wxID_ANY, wxT("..."), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText10->Wrap(-1);
	m_staticText10->SetMinSize(wxSize(-1, 80));

	bSizer13->Add(m_staticText10, 0, wxEXPAND | wxALL, 5);


	this->SetSizer(bSizer13);
	this->Layout();

	this->Centre(wxBOTH);
}

MyFrame5::~MyFrame5()
{
}

#include <wx/wx.h>

class MyApp : public wxApp {
public:
	virtual bool OnInit() {
		MyFrame5* frame = new MyFrame5(nullptr, wxID_ANY, "My App");
		frame->Show(true);
		return true;
	}
};

wxIMPLEMENT_APP(MyApp);

int main(int argc, char* argv[]) {
	return wxEntry(argc, argv);
}
