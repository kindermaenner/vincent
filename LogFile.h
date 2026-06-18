// LogFile.h: interface for the CLogFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGFILE_H__1A7D30B0_F075_11D4_B0BD_00609732212B__INCLUDED_)
#define AFX_LOGFILE_H__1A7D30B0_F075_11D4_B0BD_00609732212B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLogFile;


class CLogFile  
{
public:
	void LogString (LPCTSTR szText);
	static CLogFile * GetInstance (void);
	static void SetFileName (LPCTSTR szFileName);
	static LPCTSTR GetFileName (void);
	static void SetMaxFileSize (unsigned long l);
	CLogFile();
	virtual ~CLogFile();

protected:
	void RenewFile (void);

protected:
	CStdioFile m_hFile;
	static CLogFile * m_pInstance;
	static CString m_szFileName;
	static unsigned long m_nMaxFileSize;
};

#endif // !defined(AFX_LOGFILE_H__1A7D30B0_F075_11D4_B0BD_00609732212B__INCLUDED_)
