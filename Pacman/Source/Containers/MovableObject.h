#pragma once

#include "Models/BasicDrawableObject.h"

class MovableObject {
public:

	MovableObject();

	void move();

	const std::string getType() const;

	const glm::vec3 getMoveStep() const;

	const glm::vec3 getPosition() const;

	void setMoveDirection(const glm::vec3&);

	const glm::vec3 getMoveDirection() const;

	void setDefaultPosition(const glm::vec3&);

	void resetPosition();

	void setPosition(const glm::vec3&);

	void setRotation(const glm::vec3&);

	void setInitialFace();

	void draw();

protected:

	glm::vec3 _moveStep;

	glm::vec3 _defaultPosition;

	unsigned short iterator;

	std::vector<BasicDrawableObject> _body;

	glm::vec3 _moveDirection;

};