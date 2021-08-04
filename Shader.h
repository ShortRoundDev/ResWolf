#pragma once

#include <string>

#include "windows.h"
#include "glad/glad.h"
#include "glm/glm.hpp"

namespace ResWolf
{

	//Forward declaration
	class Model;

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

		void use();

		void setTex(_In_ GLuint texture);
		void setModel(_In_ const Model* model);
		void setInt(_In_ const std::string& name, _In_ int value);
		void setFloat(_In_ const std::string& name, _In_ float value);
		void setVec2(_In_ const std::string& name, _In_ const glm::vec2& vec);
		void setVec3(_In_ const std::string& name, _In_ const glm::vec3& vec);
		void setVec4(_In_ const std::string& name, _In_ const glm::vec4& vec);
		void setMat4(_In_ const std::string& name, _In_ const glm::mat4& matrix);
		

		ShaderStatus status;

	private:
		GLuint program;
		// Initialization
		GLuint buildShader(std::string path, GLenum type);
		void buildProgram(GLuint vertex, GLuint fragment);

		// Error checking
		bool checkShaderCompilationError(std::string path, GLuint shader);
		bool checkProgramLinkError(GLuint program);

		//Helpers
		GLint getUniformLocation(_In_ const GLchar* name);
	};
}