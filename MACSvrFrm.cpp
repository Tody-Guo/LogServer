///-----------------------------------------------------------------
///
/// @file      MACSvrFrm.cpp
/// @author    tody_guo
/// Created:   2011-8-16 11:33:59
/// @section   DESCRIPTION
///            MACSvrFrm class implementation
///
///------------------------------------------------------------------

#include "MACSvrFrm.h"

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// MACSvrFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(MACSvrFrm,wxFrame)
	////Manual Code Start
	EVT_SOCKET(SERVER_ID,  MACSvrFrm::OnServerEvent)
	EVT_SOCKET(SOCKET_ID,  MACSvrFrm::OnSocketEvent)
	////Manual Code End
	
	EVT_CLOSE(MACSvrFrm::OnClose)
	EVT_MENU(wxID_OPEN, MACSvrFrm::WxButton1Click)
	EVT_MENU(wxID_CLOSE, MACSvrFrm::WxButton2Click)
	EVT_MENU(ID_MNU_SUBMENUITEM11_1017, MACSvrFrm::LineSelectClick)
	EVT_MENU(wxID_CLEAR, MACSvrFrm::WxclearClick)
	EVT_MENU(ID_MNU_SAVEDATA_1016, MACSvrFrm::Mnusavedata1016Click)
	EVT_MENU(wxID_ABOUT, MACSvrFrm::WxaboutClick)
	EVT_TIMER(ID_WXTIMER1,MACSvrFrm::WxTimer1Timer)
	EVT_BUTTON(ID_WXBUTTON2,MACSvrFrm::WxButton2Click)
	EVT_BUTTON(ID_WXBUTTON1,MACSvrFrm::WxButton1Click)
END_EVENT_TABLE()
////Event Table End

MACSvrFrm::MACSvrFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

MACSvrFrm::~MACSvrFrm()
{
    delete m_server;
}

void MACSvrFrm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxButton1 = new wxButton(this, ID_WXBUTTON1, wxT("&Start"), wxPoint(691, 12), wxSize(75, 25), 0, wxDefaultValidator, wxT("WxButton1"));

	WxMemo1 = new wxTextCtrl(this, ID_WXMEMO1, wxEmptyString, wxPoint(9, 4), wxSize(636, 317), wxTE_MULTILINE, wxDefaultValidator, wxT("WxMemo1"));
	WxMemo1->SetMaxLength(0);
	WxMemo1->Enable(false);
	WxMemo1->SetFocus();
	WxMemo1->SetInsertionPointEnd();

	WxStatusBar1 = new wxStatusBar(this, ID_WXSTATUSBAR1);
	WxStatusBar1->SetFieldsCount(4);
	WxStatusBar1->SetStatusText(wxT("Status"),0);
	WxStatusBar1->SetStatusText(wxT("Total: 0"),1);
	WxStatusBar1->SetStatusText(wxT("Says: "),2);
	WxStatusBar1->SetStatusText(wxT("Reject:"),3);
	int WxStatusBar1_Widths[4];
	WxStatusBar1_Widths[0] = 150;
	WxStatusBar1_Widths[1] = 150;
	WxStatusBar1_Widths[2] = 150;
	WxStatusBar1_Widths[3] = -1;
	WxStatusBar1->SetStatusWidths(4,WxStatusBar1_Widths);

	WxButton2 = new wxButton(this, ID_WXBUTTON2, wxT("E&xit"), wxPoint(690, 43), wxSize(75, 25), 0, wxDefaultValidator, wxT("WxButton2"));

	WxTimer1 = new wxTimer();
	WxTimer1->SetOwner(this, ID_WXTIMER1);
	WxTimer1->Start(1000);

	WxMenuBar1 = new wxMenuBar();
	wxMenu *ID_MNU_MENUITEM1_1006_Mnu_Obj = new wxMenu(0);
	ID_MNU_MENUITEM1_1006_Mnu_Obj->Append(wxID_OPEN, wxT("&Start Server"), wxT(""), wxITEM_NORMAL);
	ID_MNU_MENUITEM1_1006_Mnu_Obj->AppendSeparator();
	ID_MNU_MENUITEM1_1006_Mnu_Obj->Append(wxID_CLOSE, wxT("E&xit"), wxT(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU_MENUITEM1_1006_Mnu_Obj, wxT("&File"));
	
	wxMenu *ID_MNU_ACTION_1012_Mnu_Obj = new wxMenu(0);
	ID_MNU_ACTION_1012_Mnu_Obj->Append(ID_MNU_SUBMENUITEM11_1017, wxT("Line &Select"), wxT(""), wxITEM_NORMAL);
	ID_MNU_ACTION_1012_Mnu_Obj->AppendSeparator();
	ID_MNU_ACTION_1012_Mnu_Obj->Append(wxID_CLEAR, wxT("&Clear Data"), wxT(""), wxITEM_NORMAL);
	ID_MNU_ACTION_1012_Mnu_Obj->AppendSeparator();
	ID_MNU_ACTION_1012_Mnu_Obj->Append(ID_MNU_SAVEDATA_1016, wxT("&Save Data"), wxT(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU_ACTION_1012_Mnu_Obj, wxT("&Action"));
	
	wxMenu *wxID_HELP_Mnu_Obj = new wxMenu(0);
	wxID_HELP_Mnu_Obj->Append(wxID_ABOUT, wxT("&About"), wxT(""), wxITEM_NORMAL);
	WxMenuBar1->Append(wxID_HELP_Mnu_Obj, wxT("&Help"));
	SetMenuBar(WxMenuBar1);

	SetStatusBar(WxStatusBar1);
	SetTitle(wxT("MAC Reciever 1.4"));
	SetIcon(wxNullIcon);
	SetSize(8,8,665,394);
	Center();
	
	////GUI Items Creation End
	
	isRunning = 0;
	isLoaded = 0;
	lockIncome = 0;
	rejectConn = 0 ;
	TotalConn = 0;
}

void MACSvrFrm::OnClose(wxCloseEvent& event)
{
	Destroy();
}

/*
 * WxButton1Click
 */
void MACSvrFrm::WxButton1Click(wxCommandEvent& event)
{
	// insert your code here
	wxIPV4address addr;
    addr.Service(8086);
    
    if (isRunning)
    {
        wxMessageBox("Server is already running...", "Warning", wxICON_EXCLAMATION);
        return ; // if server is running, then cancel action...
    }
    
    if (nowLine.IsEmpty())
    {
        wxMessageBox("Please Select your Line first", "Warning", wxICON_EXCLAMATION);
        return ; 
    }
    
    m_server = new wxSocketServer(addr);
    if (! m_server->Ok() )
    {
	    WxStatusBar1->SetStatusText(wxT("Listening Failed!"),0);
        wxMessageBox("Server can't run now...", "Error", wxICON_ERROR);
        return;
    }else
    {
	    WxStatusBar1->SetStatusText(wxT("Server is Running..."),0);
	    WxButton1->Enable(false);
    }
      // Setup the event handler and subscribe to connection events
    m_server->SetEventHandler(*this, SERVER_ID);
    m_server->SetNotify(wxSOCKET_CONNECTION_FLAG);
    m_server->Notify(true);	
    isRunning = 1;  // Server is running...
}

void MACSvrFrm::OnServerEvent(wxSocketEvent& event)
{
    wxSocketBase *sock;
    switch(event.GetSocketEvent())
    {
        case wxSOCKET_CONNECTION : WxStatusBar1->SetStatusText("Says: wxSOCKET_CONNECTION",2); break;
        default                  : WxStatusBar1->SetStatusText("Says: Unexpected event!",2); break;
    }
    
    sock = m_server->Accept(false);

    if (sock)
    {
        WxStatusBar1->SetStatusText("Says: New connection in.",2);
    }
    else
    {
        WxStatusBar1->SetStatusText("Says: Accept new Connetcion failed",2);
        return;
    }

    sock->SetEventHandler(*this, SOCKET_ID);
    sock->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
    sock->Notify(true);    
}

void MACSvrFrm::OnSocketEvent(wxSocketEvent& event)
{
    wxSocketBase *sock = event.GetSocket();
   
    switch(event.GetSocketEvent())
    {
        case wxSOCKET_INPUT : WxStatusBar1->SetStatusText("Says: wxSOCKET_INPUT",2);break;
        case wxSOCKET_LOST  : WxStatusBar1->SetStatusText("Says: wxSOCKET_LOST",2);break;
        default             : WxStatusBar1->SetStatusText("Says: Unexpected event!",2);break;
    }

  // Now we process the event
  switch(event.GetSocketEvent())
  {
    case wxSOCKET_INPUT:
    {
      sock->SetNotify(wxSOCKET_LOST_FLAG);
      if (!lockIncome)
      {
        lockIncome = 1;  // reject 
        getMsg(sock); // Here massage
        lockIncome = 0; // release lock

        TotalConn++;
        wxString s1 ;
        s1.Printf("%ld", TotalConn);
	    WxStatusBar1->SetStatusText("Passed: " + s1, 1);
      }
      else
      {
        sock->Write("MAC_REJECT", 10);
        rejectConn ++;
        wxString s2;
        s2.Printf("%ld", rejectConn);
        WxStatusBar1->SetStatusText("Reject: " + s2, 3);
      }
      sock->SetNotify(wxSOCKET_LOST_FLAG | wxSOCKET_INPUT_FLAG);
      break;
    }
    case wxSOCKET_LOST:
    {
      sock->Destroy();
      break;
    }
    default: ;
  }
}

/*
 * WxButton2Click
 */
void MACSvrFrm::WxButton2Click(wxCommandEvent& event)
{
	// insert your code here
    WxMemo1->SaveFile("c:/macLogs/"+ nowLine+dateFile +".txt");
	Close(true);
}

void MACSvrFrm::getMsg(wxSocketBase *sock)
{    
    wxString s, s1;
    char buf[512];
    int len = 0;
    wxDateTime now;
    
    memset(buf, 0 , sizeof(buf));
    
    len = sock->Read(buf, 512).LastCount();
    s.Printf("%s", buf);
    
    now = wxDateTime::Now();
    
    if (s.Find("00:00:00:00:00:00") == wxNOT_FOUND &&
        s.Find("FF:FF:FF:FF:FF:FF") == wxNOT_FOUND &&
        s.Find("43:29:B1:55:00:00")== wxNOT_FOUND )
    {
        sock->Write("MAC_OK", 6);
        
        s1 = s;
        if ( s.Find("NOSN") != wxNOT_FOUND || s.Len() == 17 )  // s.len=17 is Compatible for MACUP_1.2.apk
        {
            if (s.Len() != 17 ) s = s.Remove(0,4); // for MACUP_1.2.apk
            wxString sn = wxGetTextFromUser("Please Scan SN:", "Scan");
            while (sn.IsEmpty() || sn.Len() <= 10)
            {
                sn = wxGetTextFromUser("Please Scan SN:", "Scan");
            }
            if (s.Len() == 17 )  // for MACUP_1.2.apk
                s1 = sn + "|" + s;
            else
                s1 = sn + s;
        }
        
        WxMemo1->AppendText(nowLine + "|"+ s1 + "|" + 
                            "NET-MAC001-0002"+"|"+ now.Format("%Y-%m-%d %H:%M:%S\n")); 
        
        WxMemo1->SaveFile("c:/macLogs/"+ nowLine+ dateFile +".txt");
    }
    else
    {
        if (s.Contains("TIME"))
        {
            sock->Write(now.Format("%Y-%m-%d %H:%M:%S"), 19);
        }else{
            sock->Write("MAC_ERR", 7);
        }
    }
}

void MACSvrFrm::WxaboutClick(wxCommandEvent& event)
{
        wxMessageBox("WiFi MAC Reciever 1.4\n Written by Tody Kwok\n(c) Tody 2012, T-ware Inc.",
             "About");
}

/*
 * WxclearClick
 */
void MACSvrFrm::WxclearClick(wxCommandEvent& event)
{
	// insert your code here
	int answer = wxMessageBox("Sure to clear all data?", "Confirm",
                            wxYES_NO | wxICON_QUESTION );
	if (answer == wxYES)
	{
        WxMemo1->Clear();
    }
}

/*
 * WxTimer1Timer
 */
void MACSvrFrm::WxTimer1Timer(wxTimerEvent& event)
{
	// insert your code here
    wxDateTime now = wxDateTime::Now();
    dateFile = now.Format("%Y%m%d%H");
    wxFile file;

	if (!wxDirExists("c:/macLogs"))
	{
        wxMkdir("c:/macLogs");
    }
    if (nowLine.IsEmpty())
    {
        return ; 
    }

    if (!file.Exists("c:/macLogs/"+ nowLine+ dateFile +".txt"))
    {
        if( file.Create("c:/macLogs/"+ nowLine+ dateFile +".txt"))
        {
            WxMemo1->LoadFile("c:/macLogs/"+ nowLine+ dateFile +".txt");
        }
    }

    if (!isLoaded)
    {
        WxMemo1->LoadFile("c:/macLogs/"+ nowLine+ dateFile +".txt");
        isLoaded = 1;
    }
    
    if (isRunning)
    {
        WxStatusBar1->SetStatusText(wxT("Server is Running..."),0);
    }
//    WxStatusBar1->SetStatusText("Says: " + nowLine+ dateFile, 2);
}

/*
 * Mnusavedata1016Click
 */
void MACSvrFrm::Mnusavedata1016Click(wxCommandEvent& event)
{
	// insert your code here
    WxMemo1->SaveFile("c:/macLogs/"+ nowLine+ dateFile +".txt");
    wxMessageBox("All data saved",
             "Info", wxICON_INFORMATION );
}

/*
 * LineSelectClick
 */
void MACSvrFrm::LineSelectClick(wxCommandEvent& event)
{
	// insert your code here
	wxString testLine[] = { "T1", "T2", "T3", "T4", "T5" };

	wxSingleChoiceDialog dlg(this, "Select Your Line",
                              "Line Select",
                              5,
                              testLine);
    if ( dlg.ShowModal() == wxID_OK )
    {
        wxMessageBox("You line is " + dlg.GetStringSelection());
        nowLine = dlg.GetStringSelection();
    }
    dlg.Destroy();
}
