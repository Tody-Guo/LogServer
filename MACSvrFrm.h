///-----------------------------------------------------------------
///
/// @file      MACSvrFrm.h
/// @author    tody_guo
/// Created:   2011-8-16 11:33:59
/// @section   DESCRIPTION
///            MACSvrFrm class declaration
///
///------------------------------------------------------------------

#ifndef __MACSVRFRM_H__
#define __MACSVRFRM_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif
#include <wx/socket.h>
#include <wx/file.h>



//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/menu.h>
#include <wx/timer.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
#include <wx/button.h>
////Header Include End

////Dialog Style Start
#undef MACSvrFrm_STYLE
#define MACSvrFrm_STYLE wxCAPTION | wxSYSTEM_MENU | wxSTAY_ON_TOP | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class MACSvrFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		MACSvrFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("MAC Reciever"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = MACSvrFrm_STYLE);
		virtual ~MACSvrFrm();
		void WxButton1Click(wxCommandEvent& event);
		void WxButton2Click(wxCommandEvent& event);
		void WxaboutClick(wxCommandEvent& event);
		void WxclearClick(wxCommandEvent& event);
		void WxTimer1Timer(wxTimerEvent& event);
		void Mnusavedata1016Click(wxCommandEvent& event);
		void LineSelectClick(wxCommandEvent& event);
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxMenuBar *WxMenuBar1;
		wxTimer *WxTimer1;
		wxButton *WxButton2;
		wxStatusBar *WxStatusBar1;
		wxTextCtrl *WxMemo1;
		wxButton *WxButton1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
            // ID for sockets
            SERVER_ID = 100,
            SOCKET_ID,
            
			////GUI Enum Control ID Start
			ID_MNU_MENUITEM1_1006 = 1006,
			ID_MNU_ACTION_1012 = 1012,
			ID_MNU_SUBMENUITEM11_1017 = 1017,
			ID_MNU_SAVEDATA_1016 = 1016,
			
			ID_WXTIMER1 = 1014,
			ID_WXBUTTON2 = 1005,
			ID_WXSTATUSBAR1 = 1004,
			ID_WXMEMO1 = 1003,
			ID_WXBUTTON1 = 1002,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
        wxSocketServer *m_server;
	    long TotalConn;
	    long rejectConn;
	    wxString dateFile;
	    int isLoaded;
	    int isRunning;
	    int lockIncome;
	    wxString nowLine ;
		wxString testLine[];

	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
        void OnServerEvent(wxSocketEvent& event);
        void OnSocketEvent(wxSocketEvent& event);
        void getMsg(wxSocketBase *sock);
        void updateStatusBar();

};

#endif
