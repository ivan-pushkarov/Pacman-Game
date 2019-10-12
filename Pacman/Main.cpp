#include <windows.h>
#include "Application/Application.h"

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)
{
	Application game;

	game.run();

	return 0;
}
