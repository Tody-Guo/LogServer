//---------------------------------------------------------------------------
//
// Name:        MACSvrApp.cpp
// Author:      tody_guo
// Created:     2011-8-16 11:33:58
// Description: 
//
//---------------------------------------------------------------------------

#include "MACSvrApp.h"
#include "MACSvrFrm.h"

IMPLEMENT_APP(MACSvrFrmApp)

bool MACSvrFrmApp::OnInit()
{
    MACSvrFrm* frame = new MACSvrFrm(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int MACSvrFrmApp::OnExit()
{
	return 0;
}
