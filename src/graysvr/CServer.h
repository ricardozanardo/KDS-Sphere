//
// CServer.h
//

#ifndef _INC_CSERVER_H
#define _INC_CSERVER_H
#pragma once

enum SERVMODE_TYPE
{
	SERVMODE_RestockAll,	// Major event
	SERVMODE_Saving,		// Forced save freezes the system
	SERVMODE_Run,			// Game is up and running
	SERVMODE_ResyncPause,	// Paused during resync

	SERVMODE_Loading,		// Initial load
	SERVMODE_ResyncLoad,	// Loading after resync
	SERVMODE_Exiting		// Closing down
};

class CItemShip;

extern class CServer : public CServerDef, public CTextConsole
{
	static LPCTSTR const sm_szVerbKeys[];

public:
	static const char *m_sClassName;
	SERVMODE_TYPE m_iModeCode;			// Just some error code to return to system
	int m_iExitFlag;					// identifies who caused the exit (< 0 = error)
	bool m_fResyncPause;				// Server is temporarily halted so files can be updated
	bool m_fResyncMultiRegions;			// An AREADEF/ROOMDEF resource got changed on server resync, so multi regions on world must be reloaded too
	CTextConsole *m_fResyncRequested;	// A resync pause has been requested by this source

	CGSocket m_SocketMain;				// This is the incoming monitor socket (might be multiple ports?)

	// Admin console
	int m_iAdminClients;				// How many of my clients are admin consoles?
	CGString m_sConsoleText;
	bool m_fConsoleTextReadyFlag;		// Interlocking flag for moving between tasks

	CServTime m_timeShutdown;			// When to perform the shutdowm (g_World.clock)
	CChat m_Chats;						// Keep all the active chats

	std::vector<CItemShip *> m_ShipTimers;
	void ShipTimers_Tick();
	void ShipTimers_Add(CItemShip *pShip);
	void ShipTimers_Delete(CItemShip *pShip);

	char m_PacketFilter[255][32];		// List of inbound packet filtering functions
	char m_OutPacketFilter[255][32];	// List of outbound packet filtering functions

	CFileObj fhFile;		// File script object
	CDataBase m_hdb;		// MySQL database
	CSQLite m_hldb;			// SQLite database

private:
	void ProfileDump(CTextConsole *pSrc, bool bDump = false);

public:
	CServer();
	~CServer();

private:
	CServer(const CServer &copy);
	CServer &operator=(const CServer &other);

public:
	bool IsValidBusy() const;
	void SetServerMode(SERVMODE_TYPE mode);

	void SetExitFlag(int iFlag);
	void Shutdown(INT64 iMinutes);
	bool IsLoading() const
	{
		return ((m_iModeCode > SERVMODE_Run) || m_fResyncPause);
	}
	void SetSignals(bool fMsg = true);

	bool SocketsInit();
	bool SocketsInit(CGSocket &socket);
	void SocketsClose();

	bool Load();

	void SysMessage(LPCTSTR pszMsg) const;
	void PrintTelnet(LPCTSTR pszMsg) const;
	void PrintStr(LPCTSTR pszMsg) const;
	int PrintPercent(long iCount, long iTotal);

	virtual bool r_GetRef(LPCTSTR &pszKey, CScriptObj *&pRef);
	virtual bool r_WriteVal(LPCTSTR pszKey, CGString &sVal, CTextConsole *pSrc = NULL);
	virtual bool r_LoadVal(CScript &s);
	virtual bool r_Verb(CScript &s, CTextConsole *pSrc);

	LPCTSTR GetStatusString(BYTE iIndex = 0) const;

	bool OnConsoleCmd(CGString &sText, CTextConsole *pSrc);

	void OnTick();

public:
	void ListClients(CTextConsole *pConsole) const;
	void SetResyncPause(bool fPause, CTextConsole *pSrc, bool bMessage = false);
	bool CommandLine(int argc, TCHAR *argv[]);

	LPCTSTR GetName() const { return CServerDef::GetName(); }
	PLEVEL_TYPE GetPrivLevel() const;
} g_Serv;	// current state stuff not saved

#endif	// _INC_CSERVER_H
