#include "Options.h"


#include <wx/stdpaths.h> 


const std::vector<Scattering::ScatteringPair> Options::scatteringPairs = { 
	{ "H-Ne", 1.9, 3.15, 1, 20}, {"H-Ar", 4.16, 3.62, 1, 40}, {"H-Kr", 5.9, 3.57, 1, 84}, {"H-Xe", 7.08, 3.82, 1, 131}
	// with better Bessel functions still does not appear to work correctly for H2, so I leave this commented out for now	
	/*, {"H2-Ar", 6.3, 3.57, 2, 40}, {"H2-Kr", 7.19, 3.72, 2, 84}, {"H2-Xe", 8.1, 3.92, 2, 131} */
};

Options::Options()
	: nrPoints(1000), scatteringPair(2)
{
}


void Options::Open()
{
	if (m_fileconfig) return;

	wxString dir = wxStandardPaths::Get().GetConfigDir() + wxFileName::GetPathSeparator();

	if(!wxFileName::DirExists(dir))
		wxFileName::Mkdir(dir, 0777, wxPATH_MKDIR_FULL);

	wxString iniFilePath = dir + "Scattering.ini";

	m_fileconfig = new wxFileConfig("Scattering", wxEmptyString, iniFilePath);

	wxConfigBase::Set(m_fileconfig);
}

void Options::Close()
{
	delete m_fileconfig;
	m_fileconfig = NULL;
	wxConfigBase::Set(NULL);
}

void Options::Load()
{
	wxConfigBase *conf=wxConfigBase::Get(false);
	if (conf)
	{
		nrPoints = conf->ReadLong("/nrPoints", 1000);
		scatteringPair = conf->ReadLong("/scatteringPair", 2);
	}
}

void Options::Save()
{
	wxConfigBase *conf=wxConfigBase::Get(false);
	if (conf)
	{
		conf->Write("/nrPoints", static_cast<long int>(nrPoints));
		conf->Write("/scatteringPair", scatteringPair);
	}

	if (m_fileconfig)
		m_fileconfig->Flush();
}
