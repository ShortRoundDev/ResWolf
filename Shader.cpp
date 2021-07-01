#include "Shader.h"

#include "FileHandling.h"
#include "Logging.h"

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

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

	int error = checkShaderCompilationError(shader);
	if (error)
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
	return ;
}

bool Shader::checkShaderCompilationError(GLuint shader)
{
	GLint success = 0;
	GLchar log[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 1024, NULL, log);
		SimpleError(std::string(log));
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