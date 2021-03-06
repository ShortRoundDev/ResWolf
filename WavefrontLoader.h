#pragma once

#include <memory>
#include <string>

#include "glm/glm.hpp"

#define WAVE (WavefrontLoader::instance)

namespace ResWolf
{
	typedef struct _IndexedWaveFace
	{
		int vertex[4];
		int textureCoordinate[4];
		int normal[4];
	} IndexedWaveFace;

	typedef struct _IndexedWaveModel
	{
		size_t vertexSize;
		size_t textureCoordinateSize;
		size_t normalSize;
		size_t waveVertexSize;
		glm::vec3* vertices;
		glm::vec3* textureCoordinates;
		glm::vec3* normals;
		IndexedWaveFace* waveVertices;
	} IndexedWaveModel;

	typedef struct _RawWaveFace
	{
		glm::vec3 vertex[4];
		glm::vec3 textureCoordinate[4];
		glm::vec3 normal[4];
	} RawWaveFace;

	typedef struct _RawWaveModel
	{
		size_t vertexSize;
		RawWaveFace* waveVertices;
	} RawWaveModel;

	enum class WavefrontStatus
	{
		OK,
		ERROR_FNF,
		ERROR_PARSE,
		ERROR_MEM,
		ERROR_UNKOWN
	};

	class WavefrontLoader
	{
	public:
		static std::unique_ptr<WavefrontLoader> instance;
		static void init();

		WavefrontLoader();
		~WavefrontLoader();

		/** Loads a wavefront .obj file using indexed vertex data
		  * Returns WavefrontStatus::OK on success, other statuses on failure */
		_Success_(return == WavefrontStatus::OK)
		WavefrontStatus loadIndexed(_In_ std::string path, _Out_ IndexedWaveModel* waveModel);

		/** Loads a wavefront .obj file using raw vertex data
		  * Returns WavefrontStatus::OK on success, other statuses on failure */
		_Success_(return == WavefrontStatus::OK)
		WavefrontStatus loadRaw(_In_ std::string path, _Out_ RawWaveModel* waveModel);

	private:
		void parseItemCount(_In_ char* data, _Out_ size_t* vertexCount, _Out_ size_t* texelCount, _Out_ size_t* normalCount, _Out_ size_t* faceCount);

		_Success_(return == WavefrontStatus::OK)
		WavefrontStatus parseVertexData(_In_ char* data, _Out_ glm::vec3 *vertices, _Out_ size_t* verticesCount);

		_Success_(return == WavefrontStatus::OK)
		WavefrontStatus parseTextureCoordData(_In_ char* data, _Out_ glm::vec3 *textureCoords, _Out_ size_t* textureCoordsCount);

		_Success_(return == WavefrontStatus::OK)
		WavefrontStatus parseTextureNormalData(_In_ char* data, _Out_ glm::vec3 *normals, _Out_ size_t* normalCount);
	};
}