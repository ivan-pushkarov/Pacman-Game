#pragma once

#include "Containers/MovableObject.h"
#include "Models/BasicDrawableObject.h"

class Pacman : public MovableObject {

public:

	Pacman();

	void clearNextMoveDirection();

	void setNextMoveDirection(const glm::vec3&);

	const glm::vec3 getNextMoveDirection() const;

private:

	glm::vec3 _nextMoveDirection;

};