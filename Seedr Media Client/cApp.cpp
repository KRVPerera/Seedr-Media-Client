#include "cApp.h"

#include "wx/log.h"
#include "wx/chartype.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{
}

cApp::~cApp()
{
}

bool cApp::OnInit()
{

	auto j3 = json::parse(R"({"happy": true, "pi": 3.141})");
	// explicit conversion to string
	std::string s = j3.dump();    // {"happy":true,"pi":3.141}

	// serialization with pretty printing
	// pass in the amount of spaces to indent
	std::cout << s << std::endl;
	wxLogMessage(s.c_str());

	m_frame1 = new cMain();
	m_frame1->Show();
	return true;
}
