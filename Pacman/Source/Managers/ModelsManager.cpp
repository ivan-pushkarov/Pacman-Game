#include "ModelsManager.h"

ModelsManager::ModelsManager() {}

ModelsManager& ModelsManager::getInstance()
{
	static ModelsManager instance;

	return instance;
}

const bool ModelsManager::findVBO(const std::string& model) const
{
	if (_vbos.find(model) == _vbos.end())
	{
		return false;
	}
	return true;
}

const GLuint ModelsManager::getVBO(const std::string& model)
{
	if (findVBO(model))
	{
		return _vbos[model];
	}
	return genVBO(model);
}

const GLuint ModelsManager::genVBO(const std::string& model)
{
	GLuint _vbo;
	glGenBuffers(1, &_vbo);

	_vbos[model] = _vbo;

	return _vbos[model];
}

ModelsManager::~ModelsManager()
{
	for (std::unordered_map<std::string, GLuint>::iterator it = _vbos.begin(); it != _vbos.end(); ++it)
	{
		glDeleteBuffers(1, &it->second);
	}
}