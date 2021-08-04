#include "Shader.h"

#include "FileHandling.h"
#include "Logging.h"

#include "Model.h"

#define WIN32_LEAN_AND_MEAN

using namespace ResWolf;

Shader::Shader(std::string vsPath, std::string fsPath)
{
	status = ShaderStatus::OK;
	GLuint vertex = buildShader(vsPath, GL_VERTEX_SHADER);
	if (status != ShaderStatus::OK)
	{
		return;
	}
	GLuint fragment = buildShader(fsPath, GL_FRAGMENT_SHADER);
	if (status != ShaderStatus::OK)
	{
		return;
	}
	buildProgram(vertex, fragment);
}

Shader::~Shader()
{

}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::setTex(_In_ GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Shader::setModel(_In_ const Model* model)
{
	glBindVertexArray(model->vao);
}

void Shader::setInt(_In_ const std::string& name, _In_ int value)
{
	glUniform1i(getUniformLocation(name.c_str()), value);
}

void Shader::setFloat(_In_ const std::string& name, _In_ float value)
{
	glUniform1f(getUniformLocation(name.c_str()), value);
}

void Shader::setVec2(_In_ const std::string& name, _In_ const glm::vec2& vec)
{
	glUniform2f(getUniformLocation(name.c_str()), vec.x, vec.y);
}

void Shader::setVec3(_In_ const std::string& name, _In_ const glm::vec3& vec)
{
	auto location = getUniformLocation(name.c_str());
	glUniform3f(location, vec.x, vec.y, vec.z);
}

void Shader::setVec4(_In_ const std::string& name, _In_ const glm::vec4& vec)
{
	glUniform4f(getUniformLocation(name.c_str()), vec.x, vec.y, vec.z, vec.w);
}

void Shader::setMat4(_In_ const std::string& name, _In_ const glm::mat4& matrix)
{
	glUniformMatrix4fv(getUniformLocation(name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

GLuint Shader::buildShader(std::string path, GLenum type)
{
	char* text = NULL;
	int err = ReadTextFile(path, &text, NULL);
	if (err)
	{
		status = ShaderStatus::FILE_OPEN_FAILED;
		return 0;
	}
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &text, NULL);
	glCompileShader(shader);

	int success = checkShaderCompilationError(path, shader);
	if (!success)
	{
		free(text);
		status = (type == GL_VERTEX_SHADER
			? ShaderStatus::VS_COMPILATION_FAILED
			: ShaderStatus::FS_COMPILATION_FAILED);
		return 0;
	}
	free(text);
	return shader;
}

void Shader::buildProgram(GLuint vertex, GLuint fragment)
{
	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	
	glLinkProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (!checkProgramLinkError(program))
	{
		status = ShaderStatus::PROGRAM_LINK_FAILED;
	}
	return;
}

bool Shader::checkShaderCompilationError(std::string path, GLuint shader)
{
	GLint success = 0;
	GLchar log[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 1024, NULL, log);
		SimpleError(std::string(log) + "\nat " + path);
		return false;
	}
	return true;
}

bool Shader::checkProgramLinkError(GLuint program)
{
	GLint success;
	GLchar log[1024];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 1024, NULL, log);
		SimpleError(std::string(log));
		return false;
	}
	return true;
}

GLint Shader::getUniformLocation(_In_ const GLchar* name)
{
	return glGetUniformLocation(program, name);
}