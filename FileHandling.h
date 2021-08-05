#pragma once

#include <string>

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#define FILE_SUCCESS		0
#define FILE_FAILED			1
#define FILE_NOT_FOUND		2
#define FILE_SIZE_ERROR		4
#define FILE_NULL_BUFFER	8
#define FILE_ALLOC_FAILURE	16

/** Reads a text file in its entirety and changes the given pointer `file` to point at the buffer containing the data,
  * and sets the provided `size` pointer to the file size. Returns nonzero on failure. See #defined error codes above.
  * This function calls calloc */
_Success_(return == 0)
int ReadTextFile(_In_ std::string path, _Out_ char** file, _In_opt_ size_t* size);

/** Reads a binary file in its entirety and changes the given pointer `file` to point at the buffer containing the data,
  * and sets the provided `size` pointer to the file size. Returns nonzero on failure. See #defined error codes above.
  * This function calls calloc */
_Success_(return == 0)
int ReadBinaryFile(_In_ std::string path, _Out_ char** file, _In_opt_ size_t* size);