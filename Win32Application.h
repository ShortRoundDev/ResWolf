#pragma once
#include "windows.h"

extern HMODULE NTHand;

// Seg fault handler
LONG WINAPI ResWolfUnhandledExceptionFilter(_In_ PEXCEPTION_POINTERS ExceptionInfo);

void SetHandlers();