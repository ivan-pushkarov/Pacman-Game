#pragma once

#include "Settings/Settings.h"
#include <string>
#include <unordered_map>

class ShadersManager
{
public:

	static ShadersManager& getInstance();

	const GLuint getProgramID(std::string);

	const GLuint makeShaderProgram(const char*, const char*);

	~ShadersManager();

private:

	ShadersManager();

	const GLuint makeVertexShader(const char* shaderSource);

	void readFile(const char* filename, char* &contents);

	const GLuint makeFrangmentShader(const char* shaderSource);

	std::unordered_map<std::string, GLuint> _shaders;

};