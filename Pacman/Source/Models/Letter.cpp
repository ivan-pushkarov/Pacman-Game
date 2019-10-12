#include "letter.h"
#include <string>

Letter::Letter(char letter) :
	_size(Settings::FontSize),
	_letter(letter),
	_font(Settings::BoldFont)
{
	InitializeVertices();

	_vbo = ModelsManager::getInstance().getVBO(std::string(&_letter) + _font + std::to_string(_size));

	loadModelToVRAM();
}

const float Letter::getWidth() const
{
	return _width;
}

const float Letter::getHeight() const
{
	return _height;
}

void Letter::draw()
{
	/* Enable blending, necessary for our alpha texture */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, _texture);

	/* We require 1 byte alignment when uploading texture data */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	/* Clamping to edges is important to prevent artifacts when scaling */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	/* Linear filtering usually looks best for text */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* Try to load and render the character */
	if (!FT_Load_Char(Fontsmanager::getInstance().getFace(_font), _letter, FT_LOAD_RENDER)) 
	{
		//continue;

		/* Upload the "bitmap", which contains an 8-bit grayscale image, as an alpha texture */
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, Fontsmanager::getInstance().getFace(_font)->glyph->bitmap.width, Fontsmanager::getInstance().getFace(_font)->glyph->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, Fontsmanager::getInstance().getFace(_font)->glyph->bitmap.buffer);

		TextureDrawableObject::draw();
	}
}

void Letter::InitializeVertices()
{
	FT_Set_Pixel_Sizes(Fontsmanager::getInstance().getFace(_font), 0, _size);

	_textures.clear();

	_positions.clear();

	/* Try to load and render the character */
	if (!FT_Load_Char(Fontsmanager::getInstance().getFace(_font), _letter, FT_LOAD_RENDER)) 
	{
		//continue;

		/* Calculate the vertex and texture coordinates */
		float x = Fontsmanager::getInstance().getFace(_font)->glyph->bitmap_left * float(2.0 / Settings::ApplicationWidth);
		float y = -Fontsmanager::getInstance().getFace(_font)->glyph->bitmap_top * float(2.0 / Settings::ApplicationHeight);
		_width = Fontsmanager::getInstance().getFace(_font)->glyph->bitmap.width * float(2.0 / Settings::ApplicationWidth);
		_height = Fontsmanager::getInstance().getFace(_font)->glyph->bitmap.rows * float(2.0 / Settings::ApplicationHeight);

		_positions.push_back(x);
		_positions.push_back(-y);
		_positions.push_back(0);

		_textures.push_back(0);
		_textures.push_back(0);

		_numVertices++;

		_positions.push_back(x + _width);
		_positions.push_back(-y);
		_positions.push_back(0);

		_textures.push_back(1);
		_textures.push_back(0);

		_numVertices++;

		_positions.push_back(x);
		_positions.push_back(-y - _height);
		_positions.push_back(0);

		_textures.push_back(0);
		_textures.push_back(1);

		_numVertices++;

		_positions.push_back(x + _width);
		_positions.push_back(-y - _height);
		_positions.push_back(0);

		_textures.push_back(1);
		_textures.push_back(1);
		
		_numVertices++;

	}
}