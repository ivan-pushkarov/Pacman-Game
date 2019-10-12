#include "MovableObject.h"

MovableObject::MovableObject() : iterator(0)
{}

void MovableObject::move()
{
	for (std::vector<BasicDrawableObject>::iterator it = _body.begin(); it != _body.end(); it++)
	{
		it->setPosition(it->getPosition() + _moveDirection * glm::length(_moveStep));
	}

	iterator++;
	if (iterator == _body.size())
	{
		iterator = 0;
	}
}

void MovableObject::setMoveDirection(const glm::vec3& direction)
{
	if (_moveDirection != direction)
	{
		_moveDirection = direction;

		if (_moveDirection == Settings::UP)
		{
			setRotation(glm::vec3(0, 0, Settings::Rotation));
		}

		if (_moveDirection == Settings::DOWN)
		{
			setRotation(glm::vec3(0, 0, -Settings::Rotation));
		}

		if (_moveDirection == Settings::RIGHT)
		{
			setRotation(glm::vec3(0, 0, 0));
		}

		if (_moveDirection == Settings::LEFT)
		{
			setRotation(glm::vec3(0, 0, 2 * Settings::Rotation));
		}
	}
}

void MovableObject::setRotation(const glm::vec3& rotation)
{
	for (std::vector<BasicDrawableObject>::iterator it = _body.begin(); it != _body.end(); it++)
	{
		it->setRotation(rotation);
	}
}

void MovableObject::setPosition(const glm::vec3& position)
{
	for (std::vector<BasicDrawableObject>::iterator it = _body.begin(); it != _body.end(); it++)
	{
		it->setPosition(position);
	}
}

void MovableObject::setDefaultPosition(const glm::vec3& position)
{
	_defaultPosition = position;
}

void MovableObject::resetPosition()
{
	setPosition(_defaultPosition);
}

void MovableObject::setInitialFace()
{
	iterator = 0;
}

const std::string MovableObject::getType() const
{
	return (_body.begin() + iterator)->getType();
}

const glm::vec3 MovableObject::getMoveStep() const
{
	return _moveStep;
}

const glm::vec3 MovableObject::getPosition() const
{
	return (_body.begin() + iterator)->getPosition();
}

const glm::vec3 MovableObject::getMoveDirection() const
{
	return _moveDirection;
}

void MovableObject::draw()
{
	(_body.begin() + iterator)->draw();
}