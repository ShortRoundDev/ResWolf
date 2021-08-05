#pragma once

#include <string>
#include <glm/glm.hpp>

/**
* Thread local variable for the last line an error appeared on.
* By calling the GameErr macro, this is set to the calling line
*/
extern thread_local int errLine;
/**
* Thread local variable for the last file an error appeared in.
* By calling the GameErr macro, this is set to the calling file
*/
extern thread_local std::string errFile;

/** Shows an error with an associated code. Code should ideally be an enum class member. Also prints errLine and errFile */
void ShowError(std::string error, std::string errorCode);
/** Shows a simple error dialog box */
void SimpleError(std::string error);

/** Shows a simple warning */
void Warn(std::string warning);

/** Used to set the errLine and errFile while also printing the error string for ShowError */
template <typename T>
T _GameErr(T err, const char* file, int line)
{
	errLine = line;
	errFile = std::string(file);
	return err;
}
#define GameErr(x) (_GameErr((x), __FILE__, __LINE__))

/** returns a string representing the given vec3 in the format "x, y, z" */
std::string vec3ToString(_In_ glm::vec3 in);