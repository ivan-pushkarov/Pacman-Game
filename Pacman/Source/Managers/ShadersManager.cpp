#include "shadersmanager.h"

ShadersManager::ShadersManager()
{
	_shaders[Settings::BasicShader] = makeShaderProgram(Settings::BasicVertexShader.c_str(), Settings::BasicFragmentShader.c_str());
	_shaders[Settings::TextureShader] = makeShaderProgram(Settings::TextureVertexShader.c_str(), Settings::TextureFragmentShader.c_str());
}

ShadersManager& ShadersManager::getInstance()
{
	static ShadersManager instance;

	return instance;
}

const GLuint ShadersManager::getProgramID(std::string shader)
{
	if (_shaders.find(shader) != _shaders.end())
	{
		return _shaders[shader];
	}
	return 0;
}

void ShadersManager::readFile(const char* filename, char* &contents)
{
	FILE* fp;

	fopen_s(&fp, filename, "r");
	if (fp)
	{
		fseek(fp, 0, SEEK_END);

		unsigned int file_length = 0;
		file_length = ftell(fp);

		fseek(fp, 0, SEEK_SET);
		contents = new char[file_length + 1];

		for (unsigned int i = 0; i < file_length + 1; i++)
		{
			contents[i] = 0;
		}

		fread(contents, 1, file_length, fp);

		contents[file_length] = '\0';
		fclose(fp);
	}
}

const GLuint ShadersManager::makeVertexShader(const char* shaderSource)
{
	const GLchar* source = (const GLchar*)shaderSource;

	GLint isCompiled = 0;
	GLuint _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertexShaderID, 1, &source, NULL);
	glCompileShader(_vertexShaderID);
	glGetShaderiv(_vertexShaderID, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(_vertexShaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(_vertexShaderID, maxLength, &maxLength, &errorLog[0]);

		printf_s("The error is: ");
		for (std::vector<GLchar>::iterator it = errorLog.begin(); it != errorLog.end(); ++it)
		{
			printf_s("%c", (*it));
		}
		printf_s("\n");

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(_vertexShaderID);
		return -1;
	}

	return _vertexShaderID;
}

const GLuint ShadersManager::makeFrangmentShader(const char* shaderSource)
{
	const GLchar* source = (const GLchar*)shaderSource;

	GLint isCompiled = 0;
	GLuint _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragmentShaderID, 1, &source, NULL);
	glCompileShader(_fragmentShaderID);

	glGetShaderiv(_fragmentShaderID, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(_fragmentShaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(_fragmentShaderID, maxLength, &maxLength, &errorLog[0]);

		printf_s("The error is: ");
		for (std::vector<GLchar>::iterator it = errorLog.begin(); it != errorLog.end(); ++it)
		{
			printf_s("%c", (*it));
		}
		printf_s("\n");

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(_fragmentShaderID);
		return -1;
	}

	return _fragmentShaderID;
}

const GLuint ShadersManager::makeShaderProgram(const char* vertexShader, const char* fragmentShader)
{
	char* vertexShaderSourceCode = NULL;
	readFile(vertexShader, vertexShaderSourceCode);
	GLuint _vertexShaderID = makeVertexShader(vertexShaderSourceCode);
	delete[] vertexShaderSourceCode;

	char* fragmentShaderSourceCode = NULL;
	readFile(fragmentShader, fragmentShaderSourceCode);
	GLuint _fragmentShaderID = makeFrangmentShader(fragmentShaderSourceCode);
	delete[] fragmentShaderSourceCode;

	GLuint _programID = glCreateProgram();
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	glLinkProgram(_programID);

	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

		//The program is useless now. So delete it.
		glDeleteProgram(_programID);

		//Provide the infolog in whatever manner you deem best.
		//Exit with failure.
		return -1;
	}

	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);

	return _programID;
}

ShadersManager::~ShadersManager()
{
	for (std::unordered_map<std::string, GLuint>::iterator it = _shaders.begin(); it != _shaders.end(); ++it)
	{
		glDeleteProgram(it->second);
	}
}