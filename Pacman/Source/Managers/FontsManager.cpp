#include "FontsManager.h"

Fontsmanager::Fontsmanager() : _fontNumber(-1)
{
	init();

	loadFont(Settings::BoldFont.c_str());
}

Fontsmanager& Fontsmanager::getInstance()
{
	static Fontsmanager instance;

	return instance;
}

const FT_Face Fontsmanager::getFace(const std::string& font)
{
	if (_fonts.find(font) != _fonts.end())
	{
		return _fonts[font];
	}
	return NULL;
}

bool Fontsmanager::init()
{
	/* Initialize the FreeType2 library */
	if (FT_Init_FreeType(&_ft)) {
		printf("Could not init freetype library.\n");
		return false;
	}

	return true;
}

bool Fontsmanager::loadFont(const char* file)
{
	FT_Face _Face;

	/* Load a font */
	if (readFontFile(file))
	{
		_fontNumber++;

		if (_font[_fontNumber].empty()) 
		{
			std::cerr << "Could not load font file " << file << std::endl;
			return false;
		}
		FT_Error fterr = FT_New_Memory_Face(_ft, (FT_Byte*)(_font[_fontNumber].data()), _fontFileSize, 0, &_Face);
		if (fterr != FT_Err_Ok) 
		{
			std::cerr << "Could not init font: error 0x" << std::hex << fterr << std::endl;
			return false;
		}

		_fonts[file] = _Face;

		return true;
	}
	else
	{
		printf_s("Error loading font file %s", file);
		return false;
	}
}

bool Fontsmanager::readFontFile(const char* fontfilename)
{
	FILE* fp = NULL;

	fopen_s(&fp, fontfilename, "r");
	if (fp)
	{
		fseek(fp, 0, SEEK_END);

		unsigned int file_length = 0;
		file_length = ftell(fp);

		fseek(fp, 0, SEEK_SET);

		_fontFileSize = file_length;
		char* font = new char[file_length + 1];

		for (unsigned int i = 0; i < file_length + 1; i++)
		{
			font[i] = 0;
		}

		fread(font, 1, file_length, fp);

		font[file_length] = '\0';
		fclose(fp);

		std::vector<char> currentFont;

		for (unsigned int i = 0; i < file_length + 1; i++)
		{
			currentFont.push_back(font[i]);
		}

		_font.push_back(currentFont);

		delete[] font;

		return true;
	}
	else
	{
		printf_s("Error reading %s font file.", fontfilename);
		return false;
	}
}

Fontsmanager::~Fontsmanager()
{
	for (std::unordered_map<std::string, FT_Face>::iterator it = _fonts.begin(); it != _fonts.end(); ++it)
	{
		FT_Done_Face(it->second);
	}

	FT_Done_FreeType(_ft);
}