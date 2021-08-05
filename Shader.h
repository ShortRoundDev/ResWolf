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

	/** Utility class for GLSL shader */
	class Shader
	{
	public:
		/** Compiles the provided vertex and fragment shaders. Sets the `status` flag on failure. */
		Shader(std::string vsPath, std::string fsPath);
		~Shader();

		/** Set the current OpenGL context to use this shader */
		void use();

		/** Binds a texture */
		void setTex(_In_ GLuint texture);
		/** Binds the VAO from the provided model */
		void setModel(_In_ const Model* model);
		/** Sets the integer uniform specified by the name string to the provided value */
		void setInt(_In_ const std::string& name, _In_ int value);
		/** Sets the float uniform specified by the name string to the provided value */
		void setFloat(_In_ const std::string& name, _In_ float value);
		/** Sets the Vec2 uniform specified by the name string to the provided value */
		void setVec2(_In_ const std::string& name, _In_ const glm::vec2& vec);
		/** Sets the Vec3 uniform specified by the name string to the provided value */
		void setVec3(_In_ const std::string& name, _In_ const glm::vec3& vec);
		/** Sets the Vec4 uniform specified by the name string to the provided value */
		void setVec4(_In_ const std::string& name, _In_ const glm::vec4& vec);
		/** Sets the Mat4 uniform specified by the name string to the provided value */
		void setMat4(_In_ const std::string& name, _In_ const glm::mat4& matrix);

		/** Represents the current status of the shader. OK means no problems. Anything else is a failure state */
		ShaderStatus status;

	private:
		/** The compiled OpenGL Shader progra */
		GLuint program;
		// Initialization
		/** Reads and builds the shader from the path for the given Shader type `type` */
		GLuint buildShader(std::string path, GLenum type);
		/** Builds the shader program from the two provided vertex and fragment shaders */
		void buildProgram(GLuint vertex, GLuint fragment);

		// Error checking
		/** Checks the shader for errors. Uses path to specify the glsl file in any error messages */
		bool checkShaderCompilationError(std::string path, GLuint shader);
		/** Checks the shader program for errors */
		bool checkProgramLinkError(GLuint program);

		//Helpers
		/** Gets the uniform location for the given uniform name */
		GLint getUniformLocation(_In_ const GLchar* name);
	};
}