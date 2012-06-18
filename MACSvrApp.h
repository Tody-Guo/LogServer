//---------------------------------------------------------------------------
//
// Name:        MACSvrApp.h
// Author:      tody_guo
// Created:     2011-8-16 11:33:58
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __MACSVRFRMApp_h__
#define __MACSVRFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class MACSvrFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
