#pragma once

#include <set>
#include <queue>
#include <stack>
#include <unordered_map>
#include "Math/MathUtils.h"
#include "Containers/Playground.h"
#include "Containers/MovableObject.h"
#include "Models/BasicDrawableObject.h"

class Ghost : public MovableObject {

public:

	Ghost(std::string);

	void draw();

	void move();

	void setRotation(const glm::vec3&);

	void setPosition(const glm::vec3&);

	void resetPosition();

	void setModeEaten();

	void setModeChase();

	static Uint32 setModeChaseTimer(Uint32 timer, void* p);

	void caughtPlayer();

	void setModeScatter();

	void setModeFrightened();

	void chooseMoveDirection();

private:

	bool _eaten;

	bool _frightened;

	std::string _name;

	std::string _mode;

	SDL_TimerID _timerID;

	unsigned short _timer;

	glm::vec3 _targetPosition;

	void reverseMoveDirection();

	std::vector<BasicDrawableObject> _eyes;

	std::vector<BasicDrawableObject> _bodyFrightened;

};