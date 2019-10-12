#include "pacman.h"

Pacman::Pacman()
{
	_body.push_back(BasicDrawableObject(Settings::PacmanState1));
	_body.back().setType(Settings::TypePacman);
	_body.push_back(BasicDrawableObject(Settings::PacmanState2));
	_body.back().setType(Settings::TypePacman);
	_body.push_back(BasicDrawableObject(Settings::PacmanState3));
	_body.back().setType(Settings::TypePacman);
	_body.push_back(BasicDrawableObject(Settings::PacmanState4));
	_body.back().setType(Settings::TypePacman);
	_body.push_back(BasicDrawableObject(Settings::PacmanState3));
	_body.back().setType(Settings::TypePacman);
	_body.push_back(BasicDrawableObject(Settings::PacmanState2));
	_body.back().setType(Settings::TypePacman);

	_moveStep = Settings::PacmanStep;
}

void Pacman::clearNextMoveDirection()
{
	_nextMoveDirection = Settings::DefaultVector;
}

const glm::vec3 Pacman::getNextMoveDirection() const
{
	return _nextMoveDirection;
}

void Pacman::setNextMoveDirection(const glm::vec3& direction)
{
	_nextMoveDirection = direction;
}