#pragma once

#include <SDL.h>
#include <glew.h>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <SDL_types.h>
#include <SDL_opengl.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <freetype\ftglyph.h>
#include <freetype\freetype.h>
#include <freetype\freetype.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Settings {

	static const double Epsillion = 0.0001;

	static unsigned short Delay = 30;

	static unsigned short FrightenedTimer = 10000;

	static const unsigned short Unit = 1;

	static unsigned short ApplicationWidth = 600;
	static unsigned short ApplicationHeight = 600;

	static const glm::vec3 PlaygroundTopLeftCorner(-0.72, 0.72, 0.0);
	static const glm::vec3 PlaygroundTopRightCorner(0.72, 0.72, 0.0);
	static const glm::vec3 PlaygroundBottomRightCorner(0.72, -0.72, 0.0);
	static const glm::vec3 PlaygroundBottomLeftCorner(-0.72,-0.72, 0.0);

	static glm::vec3 DefaultScale(0.085, 0.085, 0.085);
	static glm::vec3 PointsScale(0.02, 0.02, 0.02);
	static glm::vec3 PillsScale(0.06, 0.06, 0.06);
	static glm::vec3 NormalScale(1.0, 1.0, 1.0);

	static glm::vec3 WonMessagePosition(-0.315, 0.0, 0.0);
	static glm::vec3 LostMessagePosition(-0.405, 0.0, 0.0);
	static glm::vec3 ScoreBoardLivesPosition(0.135, -0.91, 0.0);
	static glm::vec3 ScoreBoardScorePosition(-0.855, -0.91, 0.0);

	static const glm::vec3 UP = glm::vec3(0.0, Unit, 0.0);
	static const glm::vec3 RIGHT = glm::vec3(Unit, 0.0, 0.0);
	static const glm::vec3 DOWN = glm::vec3(0.0, -Unit, 0.0);
	static const glm::vec3 LEFT = glm::vec3(-Unit, 0.0, 0.0);

	static const glm::vec3 TopLeft = glm::vec3(-0.5, 0.5, 0.0);
	static const glm::vec3 TopRight = glm::vec3(0.5, 0.5, 0.0);
	static const glm::vec3 BottomLeft = glm::vec3(-0.5, -0.5, 0.0);
	static const glm::vec3 BottomRight = glm::vec3(0.5, -0.5, 0.0);

	static const glm::vec4 TextColor = glm::vec4(1.0, 1.0, 1.0, 1.0);

	static const glm::vec4 GhostScatterColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
	static const glm::vec4 GhostChaseColor = glm::vec4(1.0, 0.0, 0.0, 1.0);
	static const glm::vec4 GhostFrightenedColor = glm::vec4(0.0, 0.0, 1.0, 1.0);
	static const glm::vec4 GhostEatenColor = glm::vec4(1.0, 1.0, 1.0, 1.0);

	static const glm::vec3 TopCenter = glm::vec3(0.0, 0.5, 0.0);
	static const glm::vec3 RightCenter = glm::vec3(0.5, 0.0, 0.0);
	static const glm::vec3 LeftCenter = glm::vec3(-0.5, 0.0, 0.0);
	static const glm::vec3 BottomCenter = glm::vec3(0.0, -0.5, 0.0);

	static const glm::vec3 BlinkyStep = glm::vec3(0.015, 0.0, 0.0);
	static const glm::vec3 InkyStep = glm::vec3(0.01125, 0.0, 0.0);
	static const glm::vec3 PinkyStep = glm::vec3(0.01, 0.0, 0.0);
	static const glm::vec3 ClydeStep = glm::vec3(0.009, 0.0, 0.0);

	static const glm::vec3 PacmanStep = glm::vec3(0.018, 0.0, 0.0);
	static const float TilesStep = (float)0.09;

	static const float PositionEpsillionSmall = (float)0.045;
	static const float PositionEpsillionBig = (float)0.06;

	static const unsigned short PointEatenPoints = 10;
	static const unsigned short PillEatenPoints = 50;
	static const unsigned short GhostEatenPoints = 500;

	static const unsigned short GhostsOutDelay = 50;
	static const unsigned short MoveGhostEyesDelay = 15;

	static const unsigned short FontSize = 28;

	static const std::string ApplicationName = "Pacman";

	static const std::string GhostModeEaten = "Eaten";
	static const std::string GhostModeChase = "Chase";
	static const std::string GhostModeScatter = "Scatter";
	static const std::string GhostModeFrightened = "Frightened";

	static const std::string GhostBlinky = "Blinky";
	static const std::string GhostPinky = "Pinky";
	static const std::string GhostInky = "Inky";
	static const std::string GhostClyde = "Clyde";

	static const std::string TypeGhost = "ghost";
	static const std::string TypePacman = "pacman";
	static const std::string TypeEntranceGhostHouse = "entrance ghost hause";

	static const std::string ModelsFilesPath = "./Models/";
	static const std::string BoldFont = "./Fonts/OpenSans-Bold.ttf";
	static const std::string RegularFont = "./Fonts/OpenSans-Regular.ttf";

	static const glm::vec3 TextPosition = glm::vec3(0.0, 0.0, 0.0);

	// Intentional mistakes, in order to set priorities for UP, DOWN, RIGHT, LEFT 
	// directions with common weights in the algorithm for pathfinding
	static const double HeuristicMistakeRight = 1.000001;
	static const double HeuristicMistakeDown = 1.000002;
	static const double HeuristicMistakeLeft = 1.000003;

	static const float PlaygroundStart = (float)-0.82;
	static const float PlaygroundEnd = (float)0.82;

	static const std::string EyesUp = "./Models/ghost-eyes-up";
	static const std::string EyesDown = "./Models/ghost-eyes-down";
	static const std::string EyesLeft = "./Models/ghost-eyes-left";
	static const std::string EyesRight = "./Models/ghost-eyes-right";

	static const std::string GhostState1 = "./Models/ghost-state-1";
	static const std::string GhostState2 = "./Models/ghost-state-2";

	static const std::string Wall = "wall.txt";
	static const std::string Pill = "pill.txt";
	static const std::string Point = "point.txt";

	static const std::string PacmanState1 = "pacman-state-1.txt";
	static const std::string PacmanState2 = "pacman-state-2.txt";
	static const std::string PacmanState3 = "pacman-state-3.txt";
	static const std::string PacmanState4 = "pacman-state-4.txt";

	static const std::string BlinkyState1 = "Blinky-state-1.txt";
	static const std::string BlinkyState2 = "Blinky-state-2.txt";
	
	static const std::string PinkyState1 = "Pinky-state-1.txt";
	static const std::string PinkyState2 = "Pinky-state-2.txt";

	static const std::string InkyState1 = "Inky-state-1.txt";
	static const std::string InkyState2 = "Inky-state-2.txt";
	
	static const std::string ClydeState1 = "Clyde-state-1.txt";
	static const std::string ClydeState2 = "Clyde-state-2.txt";

	static const std::string GhostFrightened1 = "ghost-frightened-state-1.txt";
	static const std::string GhostFrightened2 = "ghost-frightened-state-2.txt";

	static const std::string GhostEyesLeft = "ghost-eyes-left.txt";
	static const std::string GhostEyesRight = "ghost-eyes-right.txt";

	static const std::string ScoreMessage = "SCORE";
	static const std::string LivesMessage = "LIVES";
	static const std::string WinConditionMessage = "YOU WIN!";
	static const std::string LoseConditionMessage = "YOU LOSE!";

	static const std::string BasicVertexShader = "./Shaders/BasicVertexShader.vs";
	static const std::string BasicFragmentShader = "./Shaders/BasicFragmentShader.fs";
	static const std::string BasicShader = BasicVertexShader + BasicFragmentShader;

	static const std::string TextureVertexShader = "./Shaders/TextureVertexShader.vs";
	static const std::string TextureFragmentShader = "./Shaders/TextureFragmentShader.fs";
	static const std::string TextureShader = TextureVertexShader + TextureFragmentShader;

	static const double Rotation = 1.5707963268; // 90 degrees in Radians

	static glm::vec3 DefaultVector = glm::vec3(0.0, 0.0, 0.0);
	static glm::vec4 BackgroundColor = glm::vec4(0.0, 0.0, 0.0, 0.0);

	static const unsigned short LevelPointValue = 0;
	static const unsigned short LevelWallValue = 1;
	static const unsigned short LevelPillValue = 2;
	static const unsigned short LevelBlinkyValue = 4;
	static const unsigned short LevelPinkyValue = 5;
	static const unsigned short LevelInkyValue = 6;
	static const unsigned short LevelClydeValue = 7;
	static const unsigned short LevelEntranceGhostHauseValue = 8;
	static const unsigned short LevelPacmanValue = 9;

	static const unsigned short Level[19][19] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
												  1, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 2, 1,
												  1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1,
										          1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1,
										          1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1,
										          1, 0, 0, 0, 0, 1, 3, 1, 1, 1, 1, 1, 3, 1, 0, 0, 0, 0, 1,
												  1, 0, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 0, 1,
												  1, 0, 1, 1, 1, 1, 3, 1, 1, 8, 1, 1, 3, 1, 1, 1, 1, 0, 1,
												  1, 0, 0, 0, 0, 0, 3, 1, 3, 3, 3, 1, 3, 0, 0, 0, 0, 0, 1,
												  1, 0, 1, 1, 1, 1, 3, 1, 3, 4, 3, 1, 3, 1, 1, 1, 1, 0, 1,
												  1, 0, 0, 0, 0, 0, 3, 1, 5, 6, 7, 1, 3, 0, 0, 0, 0, 0, 1,
												  1, 0, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 0, 1,
												  1, 0, 1, 1, 1, 1, 3, 3, 3, 9, 3, 3, 3, 1, 1, 1, 1, 0, 1,
												  1, 0, 0, 0, 0, 1, 3, 1, 1, 1, 1, 1, 3, 1, 0, 0, 0, 0, 1,
												  1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1,
												  1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1,
												  1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1,
												  1, 2, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 2, 1,
												  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
};

struct pair {

	double fValue;

	glm::vec3 position;

	bool operator<(const pair& other) const
	{
		return (fValue > other.fValue);
	}

};

struct SetOperators {

	bool operator()(const glm::vec3& a, const glm::vec3& b) const
	{
		if (((double)a.x < (double)b.x) && ((double)abs((double)a.x - (double)b.x)) > Settings::Epsillion) return true;
		else if (((double)a.x > (double)b.x) && ((double)abs((double)a.x - (double)b.x)) > Settings::Epsillion) return false;
		else if (((double)a.y < (double)b.y) && ((double)abs((double)a.y - (double)b.y)) > Settings::Epsillion) return true;
		else if (((double)a.y > (double)b.y) && ((double)abs((double)a.y - (double)b.y)) > Settings::Epsillion) return false;
		else if (((double)a.z < (double)b.z) && ((double)abs((double)a.z - (double)b.z)) > Settings::Epsillion) return true;
		else if (((double)a.z > (double)b.z) && ((double)abs((double)a.z - (double)b.z)) > Settings::Epsillion) return false;
		return false;
	}

};

struct HashOperators {

	size_t operator()(const glm::vec3& h) const
	{
		return std::hash<int>()(std::round(1000000 * h.x)) ^ std::hash<int>()(std::round(1000000 * h.y)) ^ std::hash<int>()(std::round(1000000 * h.z));
	}

	bool operator()(const glm::vec3& a, const glm::vec3& b) const
	{
		return ((double)abs((double)a.x - (double)b.x) < Settings::Epsillion &&
			(double)abs((double)a.y - (double)b.y) < Settings::Epsillion &&
			(double)abs((double)a.z - (double)b.z) < Settings::Epsillion);
	}

};

