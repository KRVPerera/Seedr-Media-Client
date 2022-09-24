#pragma once

#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	wxButton *refreshBtn;

	void OnRefreshButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

enum Buttons
{
	REFRESH_BUTTON = 1
};