#include "WavefrontLoader.h"

#include "FileHandling.h"

using namespace ResWolf;

std::unique_ptr<WavefrontLoader> WavefrontLoader::instance;

void WavefrontLoader::init()
{
	instance = std::make_unique<WavefrontLoader>();
}

WavefrontLoader::WavefrontLoader()
{

}

WavefrontLoader::~WavefrontLoader()
{

}

// ----- Loading ----- //
_Success_(return == WavefrontStatus::OK)
WavefrontStatus WavefrontLoader::loadIndexed(_In_ std::string path, _Out_ IndexedWaveModel *waveModel)
{
	char* data = NULL;
	size_t size = 0;
	int err = ReadTextFile(path, &data, &size);
	switch (err)
	{
	case FILE_SUCCESS:			break;
	case FILE_NOT_FOUND:		return WavefrontStatus::ERROR_FNF;
	case FILE_ALLOC_FAILURE:	return WavefrontStatus::ERROR_MEM;
	default:					return WavefrontStatus::ERROR_UNKOWN;
	}

	size_t vertexCount = 0;
	size_t texelCount = 0;
	size_t normalCount = 0;
	size_t faceCount = 0;
	parseItemCount(
		data,
		&vertexCount,
		&texelCount,
		&normalCount,
		&faceCount
	);
	return WavefrontStatus::OK;
}
	
void WavefrontLoader::parseItemCount(
	_In_ char* data,
	_Out_ size_t* vertexCount,
	_Out_ size_t* texelCount,
	_Out_ size_t* normalCount,
	_Out_ size_t* faceCount
)
{
	*vertexCount = 0;
	*texelCount = 0;
	*normalCount = 0;
	*faceCount = 0;
	if (data == NULL)
		return;

	bool newLine = true;
	for (; *data != 0; data++)
	{
		if (newLine)
		{
			if (data[0] == 'v' && data[1] == ' ')
			{
				(*vertexCount)++;
			}
			else if (data[0] == 'v' && data[1] == 't' && data[2] == ' ')
			{
				(*texelCount)++;
			}
			else if (data[0] == 'v' && data[1] == 'n' && data[2] == ' ')
			{
				(*normalCount)++;
			}
			else if (data[0] == 'f' && data[1] == ' ')
			{
				(*faceCount)++;
			}

			newLine = false;
		}
		else
		{
			if (*data == '\n')
				newLine = true;
		}
	}
}

_Success_(return == WavefrontStatus::OK)
WavefrontStatus WavefrontLoader::parseVertexData(
	_In_ char* data,
	_Out_ glm::vec3* vertices,
	_Out_ size_t* verticesCount
)
{
	if (data == NULL || *data == NULL)
	{
		return WavefrontStatus::ERROR_PARSE;
	}
	bool newLine = true;
	for (; *data != NULL; data++)
	{
		// get a newline
		// check if it begins with "v " (with space)
		// strtok_s the newline
		// strtok_s each space
		// atof the dimensions
		// continue
	}
}
