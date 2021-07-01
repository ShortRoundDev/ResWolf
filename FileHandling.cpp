#include "FileHandling.h"

#include "Logging.h"

#include <cstdlib>
#include <cstdio>
#include <string>

_Success_(return == 0)
int ReadTextFile(_In_ std::string path, _Out_ char** file, _In_opt_ size_t* size)
{
	if (file == NULL)
	{
		return FILE_FAILED | FILE_NULL_BUFFER;
	}
	FILE* fp = NULL;
	int err = fopen_s(&fp, path.c_str(), "r");
	if (!fp)
	{
		char errMsg[1024];
		strerror_s(errMsg, 1024, errno);
		int status = FILE_FAILED;
		if (err == ENOENT)
		{
			status |= FILE_NOT_FOUND;
		}
		SimpleError("Got File Error " + std::string(errMsg) + " at\n" + path);
		return status;
	}

	fseek(fp, SEEK_END, 0);
	size_t _size = ftell(fp);
	if (_size == 0)
	{
		SimpleError("File size was 0 at\n" + path);
		fclose(fp);
		return FILE_FAILED | FILE_SIZE_ERROR;
	}
	fseek(fp, SEEK_SET, 0);
	*file = (char*)calloc(_size, sizeof(char));
	if (*file == NULL)
	{
		SimpleError("Failed to calloc buffer for file read at\n" + path);
		fclose(fp);
		return FILE_FAILED | FILE_ALLOC_FAILURE;
	}
	fread_s(*file, _size, sizeof(char), _size, fp);
	fclose(fp);

	if (size != NULL)
		*size = _size;

	return FILE_SUCCESS;
}

_Success_(return == 0)
int ReadBinaryFile(_In_ std::string path, _Out_ char** file, _In_opt_ size_t* size)
{
	if (file == NULL)
	{
		return FILE_FAILED | FILE_NULL_BUFFER;
	}
	FILE* fp = NULL;
	int err = fopen_s(&fp, path.c_str(), "rb");
	if (!fp)
	{
		char errMsg[1024];
		strerror_s(errMsg, 1024, errno);
		int status = FILE_FAILED;
		if (err == ENOENT)
		{
			status |= FILE_NOT_FOUND;
		}
		SimpleError("Got File Error " + std::string(errMsg) + " at\n" + path);
		return status;
	}

	fseek(fp, SEEK_END, 0);
	size_t _size = ftell(fp);
	if (_size == 0)
	{
		SimpleError("File size was 0 at\n" + path);
		fclose(fp);
		return FILE_FAILED | FILE_SIZE_ERROR;
	}
	fseek(fp, SEEK_SET, 0);
	*file = (char*)calloc(_size, sizeof(char));
	if (*file == NULL)
	{
		SimpleError("Failed to calloc buffer for file read at\n" + path);
		fclose(fp);
		return FILE_FAILED | FILE_ALLOC_FAILURE;
	}
	fread_s(*file, _size, sizeof(char), _size, fp);
	fclose(fp);

	if (size != NULL)
		*size = _size;

	return FILE_SUCCESS;
}