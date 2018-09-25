
#include <Windows.h>
#include <gl/GL.h>

#include "Shader.h"
#include "../../FileSystem.h"

/*
#include<fstream>
#include<iostream>
#include<string.h>
*/

unsigned int Shader::getShaderProgram(const char* vertexLink, const char* fragmentLink)
{
	unsigned int program = 0;

	if (!vertexLink || !fragmentLink) {
		return program;
	}

    std::string fragmentShaderSource = FileSystem::readTextFile(fragmentLink);
	if (fragmentShaderSource.empty())
	{
		return program;
	}
	/*
    #if defined BUILD_WIN_GLES || defined BUILD_WIN_GLFW
        fragmentShaderSource = "#define BUILD_WIN_GLES\n#define BUILD_WIN_GLES\n" + fragmentShaderSource;
    #endif
    
	GLuint _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* shaderSource = fragmentShaderSource.c_str();
    glShaderSource(_fragmentShader, 1, &shaderSource, 0);
	glCompileShader(_fragmentShader);

	GLint isShaderCompiled;
	glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &isShaderCompiled);
	if (!isShaderCompiled)
	{
		// If an error happened, first retrieve the length of the log message
		int infoLogLength, charactersWritten;
		glGetShaderiv(_fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		char* infoLog = new char[infoLogLength];
		glGetShaderInfoLog(_fragmentShader, infoLogLength, &charactersWritten, infoLog);
        
        #ifdef BUILD_OSX
                printf("Shader compiled fragment ERROR: %s", infoLog);
		#elif BUILD_WIN_GLES
			_CrtDbgReport(_CRT_WARN, NULL, 0, NULL, "Shader compiled fragment ERROR: %s\n", infoLog);
        #endif
        
		delete[] infoLog;
		return false;
	}

	std::string vertexShaderSource = FileSystem::readTextFile(vertexLink);
	if (vertexShaderSource.empty())
	{
		return false;
	}

	GLuint _vertexShader = glCreateShader(GL_VERTEX_SHADER);

    shaderSource = vertexShaderSource.c_str();
    glShaderSource(_vertexShader, 1, &shaderSource, 0);
	glCompileShader(_vertexShader);

	glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &isShaderCompiled);
	if (!isShaderCompiled)
	{
		// If an error happened, first retrieve the length of the log message
		int infoLogLength, charactersWritten;
		glGetShaderiv(_vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		char* infoLog = new char[infoLogLength];
		glGetShaderInfoLog(_vertexShader, infoLogLength, &charactersWritten, infoLog);

        #ifdef BUILD_OSX
               printf("Shader compiled vertex ERROR: %s", infoLog);
		#elif BUILD_WIN_GLES
			_CrtDbgReport(_CRT_WARN, NULL, 0, NULL, "Shader compiled vertex ERROR: %s\n", infoLog);
        #endif

		delete[] infoLog;
		return false;
	}

	GLuint _shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, _fragmentShader);
	glAttachShader(_shaderProgram, _vertexShader);

	glLinkProgram(_shaderProgram);

	GLint isLinked;
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &isLinked);
	if (!isLinked)
	{
		// If an error happened, first retrieve the length of the log message
		int infoLogLength, charactersWritten;
		glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		char* infoLog = new char[infoLogLength];
		glGetProgramInfoLog(_shaderProgram, infoLogLength, &charactersWritten, infoLog);

        #ifdef BUILD_OSX
                printf("Shader linked ERROR: %s", infoLog);
		#elif BUILD_WIN_GLES
			_CrtDbgReport(_CRT_WARN, NULL, 0, NULL, "Shader linked ERROR: %s \n", infoLog);
        #endif

		delete[] infoLog;
		return false;
	}

	program = _shaderProgram;
	return true;
	*/
}

void deInitializeGLState(GLuint fragmentShader, GLuint vertexShader, GLuint shaderProgram, GLuint vertexBuffer)
{
	// Frees the OpenGL handles for the program and the 2 shaders
	/*
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteProgram(shaderProgram);

	// Delete the VBO as it is no longer needed
	glDeleteBuffers(1, &vertexBuffer);
	*/
}
