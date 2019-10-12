#pragma once

#include "Settings/Settings.h"
#include <unordered_map>

class ModelsManager {
public:

	static ModelsManager& getInstance();

	const GLuint getVBO(const std::string& model);

	~ModelsManager();

private:

	const bool findVBO(const std::string& model) const;

	const GLuint genVBO(const std::string& model);

	std::unordered_map<std::string, GLuint> _vbos;

	ModelsManager();
};