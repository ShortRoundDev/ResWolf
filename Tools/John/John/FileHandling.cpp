#include "FileHandling.h"

#include <windows.h>
#include <shobjidl.h> 
#include <iostream>

std::wstring getFilePath()
{
	std::wstring path = L"";
	IFileOpenDialog* fileOpen;

	HRESULT hr = CoCreateInstance(
		CLSID_FileSaveDialog,
		NULL,
		CLSCTX_ALL,
		IID_IFileSaveDialog,
		reinterpret_cast<void**>(&fileOpen)
	);

	if (SUCCEEDED(hr))
	{
		hr = fileOpen->Show(NULL);
		if (SUCCEEDED(hr))
		{
			IShellItem* item;
			hr = fileOpen->GetResult(&item);
			if (SUCCEEDED(hr))
			{
				PWSTR filePath;
				hr = item->GetDisplayName(SIGDN_FILESYSPATH, &filePath);
				if (SUCCEEDED(hr))
				{
					path = std::wstring(filePath);
				}
				item->Release();
			}
		}
		fileOpen->Release();

	}
	return path;
}