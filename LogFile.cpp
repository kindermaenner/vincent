// LogFile.cpp: implementation of the CLogFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "Vincent.h"
#include "LogFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CLogFile * CLogFile::m_pInstance = NULL;
CString CLogFile::m_szFileName = "Vincent.log";
unsigned long CLogFile::m_nMaxFileSize = 1024000L;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogFile::CLogFile()
{
	m_hFile.Open (m_szFileName, CFile::modeWrite|CFile::modeCreate|CFile::modeNoTruncate|CFile::shareDenyWrite);
	m_hFile.SeekToEnd ();
}

CLogFile::~CLogFile()
{
	m_szFileName.Empty ();
}

CLogFile * CLogFile::GetInstance()
{
	if (m_pInstance == NULL)
		m_pInstance = new CLogFile;
	return m_pInstance;
}


void CLogFile::SetFileName (LPCTSTR szFileName)
{
	m_szFileName.Empty ();
	m_szFileName = szFileName;
}

LPCTSTR CLogFile::GetFileName (void)
{
	return m_szFileName;
}

void CLogFile::LogString(LPCTSTR szText)
{
	m_hFile.WriteString (szText);
	if (m_hFile.GetLength () > m_nMaxFileSize)
	{
		RenewFile ();
	}
}

void CLogFile::RenewFile (void)
{
	char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	m_hFile.Close ();
	_splitpath(m_szFileName, drive, dir, fname, ext);
	_makepath (path_buffer, drive, dir, strcat (fname, "_bak"), ext);
	::CopyFile (m_szFileName, path_buffer, FALSE);
	::DeleteFile (m_szFileName);
	m_hFile.Open (m_szFileName, CFile::modeWrite);	
}

void CLogFile::SetMaxFileSize (unsigned long l)
{
	m_nMaxFileSize = l;
}
