#pragma once

#include "Models/model.h"
#include <string.h>

class TextureDrawableObject : public Model{

public:

	TextureDrawableObject();

	virtual void loadModelToVRAM();

	virtual void InitializeVertices() = 0;
	
	void draw();

	~TextureDrawableObject();

protected:

	GLuint _texture;

	std::vector<GLfloat> _textures;

	std::vector<GLfloat> _positions;

private:

};