#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(Buttons::REFRESH_BUTTON, OnRefreshButtonClicked)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "KRV Downloader", wxPoint(30, 30), wxSize(800, 600))
{
	refreshBtn = new wxButton (this, Buttons::REFRESH_BUTTON, "Refresh");
	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	refreshBtn->SetFont(font);
	wxGridSizer* grid = new wxGridSizer(1, 3, 0, 0);

	grid->Add(refreshBtn, 1, wxEXPAND | wxALL);
		
	this->SetSizer(grid);
	grid->Layout();
}

cMain::~cMain()
{
	delete refreshBtn;
}

void cMain::OnRefreshButtonClicked(wxCommandEvent& evt)
{
	int eventObjectId = evt.GetId() - 10000;

	// if a mine is clicked
	refreshBtn->Enable(false);

	evt.Skip();
}
