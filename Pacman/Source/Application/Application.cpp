#include "Application.h"

Application::Application() :
	_width(Settings::ApplicationWidth),
	_height(Settings::ApplicationHeight),
	_name(Settings::ApplicationName)
{
	_mainWindow = NULL;
}

bool Application::initialize()
{
	bool init = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf_s("Could not initialize SDL! SDL error: %s!\n", SDL_GetError());
		init = false;
	}
	else
	{
		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		_mainWindow = SDL_CreateWindow(_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (_mainWindow == NULL)
		{
			printf_s("Could not initialize the main SDL window! SDL error: %s!\n", SDL_GetError());
			init = false;
		}
		else
		{
			//Create context
			if (SDL_GL_CreateContext(_mainWindow) == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				init = false;
			}
			else
			{
				GLenum err = glewInit();
				if (GLEW_OK != err)
				{
					// glew failed to initialize
					fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
				}
			}
		}
	}

	return init;
}

void Application::run()
{
	//Start up SDL and create window
	if (!initialize())
	{
		printf("Failed to initialize SDL or OpenGL!\n");
	}
	else
	{
		bool quit = false;

		// Main game loop
		while (Playground::getInstance().play())
		{
			render();
		}
	}
}

void Application::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(Settings::BackgroundColor.x, Settings::BackgroundColor.y, Settings::BackgroundColor.z, Settings::BackgroundColor.w);

	Playground::getInstance().draw();

	SDL_GL_SwapWindow(_mainWindow);
}

Application::~Application()
{
	SDL_DestroyWindow(_mainWindow);
	_mainWindow = NULL;

	SDL_Quit();
}
