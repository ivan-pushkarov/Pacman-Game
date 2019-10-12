#pragma once

#include "Models/model.h"
#include "Settings/settings.h"
#include "Managers/fontsmanager.h"
#include "Managers/modelsmanager.h"
#include "Managers/shadersmanager.h"
#include "Models/texturedrawableobject.h"

class Letter : public TextureDrawableObject {
public:

	explicit Letter(char);

	const float getWidth() const;

	const float getHeight() const;

	virtual void InitializeVertices();

	void draw();

private:

	char _letter;

	float _width;

	float _height;

	unsigned short _size;

	std::string _font;
};