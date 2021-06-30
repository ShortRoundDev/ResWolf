#pragma once

#include <string>

namespace ResWolf
{
	enum class ShaderStatus
	{
		OK,
		FILE_OPEN_FAILED,
		VS_COMPILATION_FAILED,
		FS_COMPILATION_FAILED
	};
	class Shader
	{
	public:
		Shader(std::string vsPath, std::string fsPath);
		~Shader();

		ShaderStatus status;
	};
}