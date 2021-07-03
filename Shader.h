#pragma once

#include <string>

#include "windows.h"
#include "glad/glad.h"

namespace ResWolf
{
	enum class ShaderStatus
	{
		OK,
		FILE_OPEN_FAILED,
		VS_COMPILATION_FAILED,
		FS_COMPILATION_FAILED,
		PROGRAM_LINK_FAILED
	};

	class Shader
	{
	public:
		Shader(std::string vsPath, std::string fsPath);
		~Shader();

		ShaderStatus status;

	private:
		GLuint program;
		GLuint buildShader(std::string path, GLenum type);
		void buildProgram(GLuint vertex, GLuint fragment);
		bool checkShaderCompilationError(GLuint shader);
		bool checkProgramLinkError(GLuint program);
	};
}