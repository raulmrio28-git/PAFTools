// PAFTools.cpp : main project file.

#include "stdafx.h"
#include "mainform.h"

using namespace PAFTools;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew mainform());
	return 0;
}
