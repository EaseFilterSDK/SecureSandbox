///////////////////////////////////////////////////////////////////////////////
//
//    (C) Copyright 2011 EaseFilter Technologies
//    All Rights Reserved
//
//    This software is part of a licensed software product and may
//    only be used or copied in accordance with the terms of that license.
//
//    NOTE:  THIS MODULE IS UNSUPPORTED SAMPLE CODE
//
//    This module contains sample code provided for convenience and
//    demonstration purposes only,this software is provided on an 
//    "AS-IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, 
//     either express or implied.  
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Tools.h"

#pragma pack(push,8) 
#include <tlhelp32.h>
#pragma pack(pop)

#include <Psapi.h>
#pragma comment(lib,"Psapi.lib")


#define	MAX_ERROR_MESSAGE_SIZE	1024

using namespace std;

#pragma comment(lib, "crypt32.lib")

#define ENCODING (X509_ASN_ENCODING | PKCS_7_ASN_ENCODING)

typedef struct {
	LPWSTR lpszProgramName;
	LPWSTR lpszPublisherLink;
	LPWSTR lpszMoreInfoLink;
} SPROG_PUBLISHERINFO, * PSPROG_PUBLISHERINFO;


//the user need to allocate the enough buffer to receive the subject name.
BOOL
GetSignerInfo(
	WCHAR* processName,
	WCHAR* subjectName,
	PULONG sizeofSubjectName)
{
	HCERTSTORE hStore = NULL;
	HCRYPTMSG hMsg = NULL;
	PCCERT_CONTEXT pCertContext = NULL;
	BOOL fResult;
	DWORD dwEncoding, dwContentType, dwFormatType;
	PCMSG_SIGNER_INFO pSignerInfo = NULL;
	PCMSG_SIGNER_INFO pCounterSignerInfo = NULL;
	DWORD dwSignerInfo;
	CERT_INFO CertInfo;
	SPROG_PUBLISHERINFO ProgPubInfo;

	BOOL retVal = FALSE;

	ZeroMemory(&ProgPubInfo, sizeof(ProgPubInfo));
	__try
	{

		if (NULL == processName || NULL == subjectName)
		{
			ToDebugger(L"processName or subjectName is NULL.");
			__leave;
		}

		// Get message handle and store handle from the signed file.
		fResult = CryptQueryObject(CERT_QUERY_OBJECT_FILE,
			processName,
			CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED,
			CERT_QUERY_FORMAT_FLAG_BINARY,
			0,
			&dwEncoding,
			&dwContentType,
			&dwFormatType,
			&hStore,
			&hMsg,
			NULL);
		if (!fResult)
		{
			ToDebugger(L"CryptQueryObject processName:%ws failed.", processName);

			__leave;
		}

		// Get signer information size.
		fResult = CryptMsgGetParam(hMsg,
			CMSG_SIGNER_INFO_PARAM,
			0,
			NULL,
			&dwSignerInfo);
		if (!fResult)
		{
			PrintErrorMessage(L"GetSignerInfo CryptMsgGetParam failed.", GetLastError());
			__leave;
		}

		// Allocate memory for signer information.
		pSignerInfo = (PCMSG_SIGNER_INFO)LocalAlloc(LPTR, dwSignerInfo);
		if (!pSignerInfo)
		{
			PrintErrorMessage(L"GetSignerInfo Unable to allocate memory for Signer Info.", GetLastError());
			__leave;
		}

		// Get Signer Information.
		fResult = CryptMsgGetParam(hMsg,
			CMSG_SIGNER_INFO_PARAM,
			0,
			(PVOID)pSignerInfo,
			&dwSignerInfo);
		if (!fResult)
		{
			PrintErrorMessage(L"GetSignerInfo CryptMsgGetParam failed.", GetLastError());
			__leave;
		}


		// Search for the signer certificate in the temporary 
		// certificate store.
		CertInfo.Issuer = pSignerInfo->Issuer;
		CertInfo.SerialNumber = pSignerInfo->SerialNumber;

		pCertContext = CertFindCertificateInStore(hStore,
			ENCODING,
			0,
			CERT_FIND_SUBJECT_CERT,
			(PVOID)&CertInfo,
			NULL);
		if (!pCertContext)
		{
			PrintErrorMessage(L"GetSignerInfo CertFindCertificateInStore failed.", GetLastError());
			__leave;
		}


		// Get Subject name size.
		DWORD dwData = 0;
		if (!(dwData = CertGetNameString(pCertContext,
			CERT_NAME_SIMPLE_DISPLAY_TYPE,
			0,
			NULL,
			NULL,
			0)))
		{
			PrintErrorMessage(L"VerifySignerInfo CertGetNameString failed.", GetLastError());
			__leave;
		}


		if (*sizeofSubjectName < dwData * sizeof(WCHAR))
		{
			PrintErrorMessage(L"VerifySignerInfo CertGetNameString failed, the input buffer is too small.", 0);
			__leave;
		}

		// Get subject name.
		if (!(CertGetNameString(pCertContext,
			CERT_NAME_SIMPLE_DISPLAY_TYPE,
			0,
			NULL,
			subjectName,
			dwData)))
		{
			PrintErrorMessage(L"VerifySignerInfo CertGetNameString failed.", GetLastError());
			__leave;
		}

		*sizeofSubjectName = (dwData - 1) * sizeof(WCHAR);

		retVal = TRUE;

	}
	__finally
	{
		// Clean up.
		if (ProgPubInfo.lpszProgramName != NULL)
			LocalFree(ProgPubInfo.lpszProgramName);
		if (ProgPubInfo.lpszPublisherLink != NULL)
			LocalFree(ProgPubInfo.lpszPublisherLink);
		if (ProgPubInfo.lpszMoreInfoLink != NULL)
			LocalFree(ProgPubInfo.lpszMoreInfoLink);

		if (pSignerInfo != NULL) LocalFree(pSignerInfo);
		if (pCounterSignerInfo != NULL) LocalFree(pCounterSignerInfo);
		if (pCertContext != NULL) CertFreeCertificateContext(pCertContext);
		if (hStore != NULL) CertCloseStore(hStore, 0);
		if (hMsg != NULL) CryptMsgClose(hMsg);

	}

	return retVal;
}


void ChangeColour(WORD theColour)
{
	    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // Get handle to standard output
	    SetConsoleTextAttribute(hConsole,theColour);		// set the text attribute of the previous handle
}

void
PrintMessage(WCHAR* message,WORD theColour)
{
	ChangeColour(theColour);
	wprintf(message);
	ChangeColour(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
}

void
PrintPassedMessage(WCHAR* message)
{
	PrintMessage(message,FOREGROUND_GREEN);
}

void
PrintFailedMessage(WCHAR* message)
{
	PrintMessage(message,FOREGROUND_RED);
}


//
//Get the last error message returned from FilterAPI, and print it.
//
void
PrintLastErrorMessage(WCHAR* message)
{
	ULONG messageLength = 0;
	WCHAR* buffer = NULL;

	if( !GetLastErrorMessage(buffer,&messageLength ))
	{
		buffer = (WCHAR*)malloc(messageLength);

		GetLastErrorMessage(buffer,&messageLength );

	}

	PrintFailedMessage(message);
	PrintFailedMessage(buffer);
	printf("\n");

	free(buffer);
}

//
//To display message in WinDbg or DbgView application.
//
void
ToDebugger(
    const WCHAR*	pszFormat, 
    ...)
{
	
	va_list					arglist;
	WCHAR					pBuffer[MAX_ERROR_MESSAGE_SIZE];
	
	memset( pBuffer, 0,MAX_ERROR_MESSAGE_SIZE*sizeof(WCHAR) );

	va_start(arglist, pszFormat);
	vswprintf(pBuffer,MAX_ERROR_MESSAGE_SIZE, pszFormat, arglist);
	va_end(arglist);

	OutputDebugStringW(pBuffer);
	OutputDebugStringW(L"\n");

}

void 
PrintErrorMessage( 
	LPWSTR	message,
    DWORD   errorCode )
{
   LPVOID lpMsgBuf = NULL;   	
   WCHAR   errorMessage[MAX_ERROR_MESSAGE_SIZE];

   __try
   {
	
	   if( errorCode != 0 )
	   {
	    FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
					    NULL, errorCode, 
					    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					    (LPTSTR) &lpMsgBuf, 0, NULL );

		swprintf_s( errorMessage, MAX_ERROR_MESSAGE_SIZE, L"%ws,errorCode:0x%0x,%ws\n", message,errorCode,lpMsgBuf);        

	   }
	   else
	   {
			swprintf_s( errorMessage, MAX_ERROR_MESSAGE_SIZE, L"%ws\n", message);        
	   }

	   ChangeColour(FOREGROUND_RED);
	   wprintf(errorMessage);
	   OutputDebugStringW (errorMessage);	   
	   ChangeColour(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

   }
   __except( EXCEPTION_EXECUTE_HANDLER  )
	{         
		OutputDebugStringW(L"PrintErrorMessage exception.");      
	}

    if( lpMsgBuf )
	{
		LocalFree( lpMsgBuf );
	}
}

std::wstring
GetFileTimeStr(LONGLONG fileTime )
{
    SYSTEMTIME stUTC, stLocal;
    DWORD dwRet;

	WCHAR buffer[100];
	std::wstring timeStr;

    // Convert the last-write time to local time.
    FileTimeToSystemTime((FILETIME*)&fileTime, &stUTC);
    SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

    // Build a string showing the date and time.
    dwRet = StringCchPrintfW(buffer, sizeof(buffer)*2, 
        L"%02d/%02d/%d  %02d:%02d",
        stLocal.wMonth, stLocal.wDay, stLocal.wYear,
        stLocal.wHour, stLocal.wMinute);

    if( S_OK == dwRet )
	{
		timeStr.assign(buffer);
	}

	return timeStr;
}

BOOLEAN
EnableDebugPrivileges()
{
    HANDLE Token;
    HRESULT hResult = S_OK;
    HANDLE procHandle = GetCurrentProcess();
    BOOL result = OpenProcessToken(procHandle,
        TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES,
        &Token);

	//wprintf(L"OpenProcessToken pid:%p result:%d .\n", procHandle,result);

    if (result)
    {
        PRIVILEGE_SET privilegeSet;
        privilegeSet.PrivilegeCount = 1;
        privilegeSet.Control = PRIVILEGE_SET_ALL_NECESSARY;

        result = LookupPrivilegeValue(NULL, SE_DEBUG_NAME,
            &privilegeSet.Privilege[0].Luid);

	//	wprintf(L"LookupPrivilegeValue result:%d .\n", result);

        if (result)
        {
            TOKEN_PRIVILEGES tokenPrivileges;
            tokenPrivileges.PrivilegeCount = 1;
            tokenPrivileges.Privileges[0].Luid = privilegeSet.Privilege[0].Luid;
            tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

            result = AdjustTokenPrivileges(Token, FALSE,
                &tokenPrivileges, 0, NULL, NULL);

            if (result)
            {
                result = PrivilegeCheck(Token, &privilegeSet, &result);
              
                if (!result)
                {
				//	wprintf(L"ERROR_PRIVILEGE_NOT_HELD SE_DEBUG_NAME result:%d .\n", result);
                    SetLastError(ERROR_PRIVILEGE_NOT_HELD);
                }

				//wprintf(L"got SE_DEBUG_NAME result:%d .\n", result);
            }
        }

        CloseHandle(Token);
    }

    if (!result)
    {
    }

    return result;
}


BOOL
GetProcessNameByPid(ULONG pid, WCHAR* processName, ULONG processNameLength )
{
	BOOL retVal = FALSE;
	HANDLE h = NULL;

__try
{
    h = OpenProcess
    (
        PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
        FALSE,
        pid
    );

    if (h) 
    {
	  	memset(processName,0,processNameLength);
        if (GetModuleFileNameEx(h,NULL,processName, processNameLength) != 0)
		{
			retVal = TRUE;
		}
		else
		{
			//PrintErrorMessage(L"GetProcessImageFileNameW failed.", GetLastError());
		}

        CloseHandle(h);

    }
}
__except( EXCEPTION_EXECUTE_HANDLER  )
{
	printf("\n\nGet processName for process Id:%d exception.\n\n", pid );
}
 
return retVal;

}
