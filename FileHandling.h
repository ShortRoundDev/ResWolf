#pragma once

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#define FILE_SUCCESS	0
#define FILE_FAILED		1
#define FILE_NOT_FOUND	2
#define FILE_SIZE_ERROR 4

int ReadTextFile(LPWSTR path, char* file);
int ReadBinaryFile(LPWSTR path, char* file);