#pragma once

#include "Settings/Settings.h"
#include "Containers/Playground.h"

class Application {
public:

	Application();

	void run();

	void render();

	bool initialize();

	~Application();

private:

	std::string _name;

	unsigned short _width;

	unsigned short _height;

	SDL_Window* _mainWindow;

};