#pragma once

#include "Settings/Settings.h"
#include "Containers/Scoreboard.h"
#include "Containers/ghost.h"
#include "Containers/pacman.h"
#include "Math/MathUtils.h"
#include "Containers/MovableObject.h"
#include "Models/BasicDrawableObject.h"

class Ghost;

class Playground{
public:

	static Playground& getInstance();

	bool play();

	void draw();

	void Won();

	void Lost();

	void resetPositions();

	const bool findTile(const glm::vec3&) const;

	const MovableObject* getPlayer() const;

	Scoreboard* getScoreboard();

	bool detectCollision(MovableObject*);

	~Playground();

private:

	Playground();

	unsigned short _totalTimePlayed;

	bool _won;

	bool _lost;

	bool _pacmanMoved;

	SDL_Event e;

	Pacman* pacman;

	Scoreboard* scoreboard;

	std::vector<Ghost> _ghosts;

	std::vector<BasicDrawableObject> _walls;

	std::vector<BasicDrawableObject> _points;

	std::vector<BasicDrawableObject> _pills;

	std::set<glm::vec3, SetOperators> _tiles;

};