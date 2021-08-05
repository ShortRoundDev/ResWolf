#pragma once
#include "windows.h"

extern HMODULE NTHand;

// Seg fault handler
/** Handles segmentation faults. Creates a memdump and allows the user to send it to a server */
LONG WINAPI ResWolfUnhandledExceptionFilter(_In_ PEXCEPTION_POINTERS ExceptionInfo);

void SetHandlers();