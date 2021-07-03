#include "Win32Application.h"

#include <Minidumpapiset.h>
#include "Logging.h"

#include <cstdlib>
#include <string>
#include <iostream>

HMODULE NTHand = LoadLibrary(L"NTDDLL.DLL");

LONG ResWolfUnhandledExceptionFilter(_In_ PEXCEPTION_POINTERS ExceptionInfo)
{
	char errHex[128];
	ZeroMemory(errHex, 128);
	sprintf_s(errHex, 128, "%X", ExceptionInfo->ExceptionRecord->ExceptionCode);

	char errAddressHex[128];
	ZeroMemory(errAddressHex, 128);
	sprintf_s(errAddressHex, 128, "%I64x", (UINT64)ExceptionInfo->ExceptionRecord->ExceptionAddress);

	errFile = "Main.cpp";
	errLine = -1;
	ShowError(
		"Unhandled Exception: " + std::string(errHex),
		"At Address: " + std::string(errAddressHex)
	);

	MINIDUMP_EXCEPTION_INFORMATION dumpExceptionInfo{
		GetCurrentThreadId(),
		ExceptionInfo,
		false
	};

	MiniDumpWriteDump(
		GetCurrentProcess(),
		GetCurrentProcessId(),
		CreateFile(
			L"memdump.dmp",
			GENERIC_WRITE,
			FILE_SHARE_DELETE |
			FILE_SHARE_READ |
			FILE_SHARE_WRITE,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		),
		MiniDumpNormal,
		&dumpExceptionInfo,
		NULL,
		NULL
	);

	return EXCEPTION_EXECUTE_HANDLER;
}

void SetHandlers()
{
	SetUnhandledExceptionFilter(ResWolfUnhandledExceptionFilter);
}