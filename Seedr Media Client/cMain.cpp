#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "KRV Downloader", wxPoint(30, 30), wxSize(800, 600))
{
	int gridSize = nFieldHeight * nFieldWidth;
	btn = new wxButton * [nFieldHeight * nFieldWidth];
	wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);

	nField = new int[gridSize];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);


	for (int x = 0; x < nFieldWidth; x++)
	{
		for (int y = 0; y < nFieldHeight; y++)
		{
			int index = y * nFieldWidth + x;
			btn[index] = new wxButton(this, 10000 + index);
			btn[index]->SetFont(font);
			grid->Add(btn[index], 1, wxEXPAND | wxALL);

			btn[index]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);

			nField[index] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}

cMain::~cMain()
{
	delete[] btn;
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	int eventObjectId = evt.GetId() - 10000;
	int x = eventObjectId % nFieldWidth;
	int y = eventObjectId / nFieldWidth;

	int index = y * nFieldWidth + x;

	if (bFirstClick) {
		int mines = 30;

		while (mines) {
			int rx = rand() % nFieldWidth;
			int ry = rand() % nFieldHeight;

			int rindex = ry * nFieldWidth + rx;
			if (nField[rindex] == 0 && rx != x && ry != y) {
				nField[rindex] = -1;
				mines--;
			}
		}

		bFirstClick = false;
	}

	// disable button to prevent repeated clicks
	btn[index]->Enable(false);

	// if a mine is clicked
	if (nField[index] == -1) {
		wxMessageBox("Booom");

		// reset game
		bFirstClick = true;
		for (int x = 0; x < nFieldWidth; x++)
		{
			for (int y = 0; y < nFieldHeight; y++)
			{
				int cIndex = y * nFieldWidth + x;
				nField[cIndex] = 0;
				btn[cIndex]->SetLabel("");
				btn[cIndex]->Enable(true);
			}
		}
	}
	else {

		// count neighbour mines
		int mine_count = 0;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight) {
					if (nField[(y + j) * nFieldWidth + (x + i)] == -1) {
						mine_count++;
					}
				}
			}
		}

		if (mine_count > 0) {

			btn[index]->SetLabel(std::to_string(mine_count));
		}
	}

	evt.Skip();
}
