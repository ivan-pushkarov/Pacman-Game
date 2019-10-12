#include "ghost.h"

Ghost::Ghost(std::string name) : _name(name), _timer(0), _eaten(false), _frightened(false)
{
	_bodyFrightened.push_back(BasicDrawableObject(Settings::GhostFrightened1));
	_bodyFrightened.back().setType(Settings::TypeGhost);
	_bodyFrightened.push_back(BasicDrawableObject(Settings::GhostFrightened2));
	_bodyFrightened.back().setType(Settings::TypeGhost);

	_eyes.push_back(BasicDrawableObject(Settings::GhostEyesLeft));
	_eyes.back().setType(Settings::TypeGhost);
	_eyes.push_back(BasicDrawableObject(Settings::GhostEyesRight));
	_eyes.back().setType(Settings::TypeGhost);

	_mode = Settings::GhostModeScatter;
	
	if (_name == Settings::GhostBlinky)
	{ 
		_body.push_back(BasicDrawableObject(Settings::BlinkyState1));
		_body.back().setType(Settings::TypeGhost);
		_body.push_back(BasicDrawableObject(Settings::BlinkyState2));
		_body.back().setType(Settings::TypeGhost);

		_targetPosition = Settings::PlaygroundTopRightCorner; 
		_moveStep = Settings::BlinkyStep;
	}
	else if (_name == Settings::GhostPinky) 
	{ 
		_body.push_back(BasicDrawableObject(Settings::PinkyState1));
		_body.back().setType(Settings::TypeGhost);
		_body.push_back(BasicDrawableObject(Settings::PinkyState2));
		_body.back().setType(Settings::TypeGhost);

		_targetPosition = Settings::PlaygroundTopLeftCorner; 
		_moveStep = Settings::PinkyStep;
	}
	else if (_name == Settings::GhostInky) 
	{ 
		_body.push_back(BasicDrawableObject(Settings::InkyState1));
		_body.back().setType(Settings::TypeGhost);
		_body.push_back(BasicDrawableObject(Settings::InkyState2));
		_body.back().setType(Settings::TypeGhost);

		_targetPosition = Settings::PlaygroundBottomRightCorner; 
		_moveStep = Settings::InkyStep;
	}
	else if (_name == Settings::GhostClyde) 
	{ 
		_body.push_back(BasicDrawableObject(Settings::ClydeState1));
		_body.back().setType(Settings::TypeGhost);
		_body.push_back(BasicDrawableObject(Settings::ClydeState2));
		_body.back().setType(Settings::TypeGhost);

		_targetPosition = Settings::PlaygroundBottomLeftCorner; 
		_moveStep = Settings::ClydeStep;
	}
}

void Ghost::move()
{
	for (std::vector<BasicDrawableObject>::iterator it = _bodyFrightened.begin(); it != _bodyFrightened.end(); it++)
	{
		it->setPosition(it->getPosition() + _moveDirection * glm::length(_moveStep));
	}

	for (std::vector<BasicDrawableObject>::iterator it = _eyes.begin(); it != _eyes.end(); it++)
	{
		it->setPosition(it->getPosition() + _moveDirection * glm::length(_moveStep));
	}

	MovableObject::move();
}

void Ghost::setRotation(const glm::vec3& rotation)
{
	for (std::vector<BasicDrawableObject>::iterator it = _bodyFrightened.begin(); it != _bodyFrightened.end(); it++)
	{
		it->setRotation(rotation);
	}

	for (std::vector<BasicDrawableObject>::iterator it = _eyes.begin(); it != _eyes.end(); it++)
	{
		it->setRotation(rotation);
	}

	MovableObject::setRotation(rotation);
}

void Ghost::setPosition(const glm::vec3& position)
{
	for (std::vector<BasicDrawableObject>::iterator it = _bodyFrightened.begin(); it != _bodyFrightened.end(); it++)
	{
		it->setPosition(position);
	}

	for (std::vector<BasicDrawableObject>::iterator it = _eyes.begin(); it != _eyes.end(); it++)
	{
		it->setPosition(position);
	}

	MovableObject::setPosition(position);
}

// Pathfinding algorythm for determining ghost move direction
void Ghost::chooseMoveDirection()
{
	glm::vec3 PacmanPosition = Playground::getInstance().getPlayer()->getPosition();

	if (_mode == Settings::GhostModeChase)
	{
		_targetPosition = PacmanPosition;
		if (glm::length(getPosition() - _targetPosition) < Settings::PositionEpsillionBig)
		{
			caughtPlayer();
			return;
		}
	}

	if (_mode == Settings::GhostModeScatter)
	{
		if (glm::length(getPosition() - _targetPosition) < Settings::PositionEpsillionSmall)
		{
			setModeChase();
		}
		else if (glm::length(getPosition() - Playground::getInstance().getPlayer()->getPosition()) < Settings::PositionEpsillionBig)
		{
			caughtPlayer();
			return;
		}
	}

	if (_mode == Settings::GhostModeEaten && glm::length(getPosition() - _targetPosition) < Settings::PositionEpsillionSmall)
	{
		setModeChase();
	}

	if (_mode == Settings::GhostModeFrightened && glm::length(getPosition() - PacmanPosition) < Settings::PositionEpsillionBig)
	{
		setModeEaten();
	}

	if (Playground::getInstance().findTile(getPosition()))
	{

		glm::vec3 target = _targetPosition;
		glm::vec3 initialPosition = getPosition();
		glm::vec3 initialMoveDirection = getMoveDirection();

		bool movableUP = false;
		bool movableDOWN = false;
		bool movableLEFT = false;
		bool movableRIGHT = false;

		unsigned short gValue = 0;
		double hValue = 0;
		double fValue = 0;
		unsigned short movableDirections = 0;

		pair a;

		std::priority_queue<pair> queue;

		glm::vec3 position = getPosition();

		std::set<glm::vec3, SetOperators> visited;

		std::unordered_map<glm::vec3, glm::vec3, HashOperators, HashOperators> _movePath;

		setMoveDirection(Settings::UP);
		if (!Playground::getInstance().detectCollision(this)) 
		{ 
			movableDirections++; movableUP = true; 
		}
		setMoveDirection(Settings::DOWN);
		if (!Playground::getInstance().detectCollision(this)) 
		{ 
			movableDirections++; movableDOWN = true; 
		}
		setMoveDirection(Settings::RIGHT);
		if (!Playground::getInstance().detectCollision(this)) 
		{ 
			movableDirections++; movableRIGHT = true; 
		}
		setMoveDirection(Settings::LEFT);
		if (!Playground::getInstance().detectCollision(this)) 
		{ 
			movableDirections++; movableLEFT = true; 
		}

		setMoveDirection(initialMoveDirection);

		if (movableDirections > 2)
		{
			if (_mode != Settings::GhostModeFrightened)
			{
				hValue = glm::length(target - getPosition());
				a.fValue = gValue + hValue;
				a.position = getPosition();
				visited.insert(position);
				_movePath[getPosition()] = Settings::DefaultVector;
				queue.push(a);
				float MoveStep = Settings::TilesStep;
				glm::vec3 newPosition;

				while (!queue.empty() && (glm::length(queue.top().position - target) > Settings::PositionEpsillionSmall))
				{
					position = queue.top().position;
					setPosition(position);

					queue.pop();

					setMoveDirection(Settings::UP);
					if (!Playground::getInstance().detectCollision(this))
					{
						newPosition = position + Settings::UP * MoveStep;

						hValue = glm::length(target - newPosition);
						a.fValue = gValue + hValue;
						a.position = newPosition;

						if (visited.find(newPosition) == visited.end())
						{
							visited.insert(newPosition);
							_movePath[newPosition] = Settings::UP;
							queue.push(a);
						}
					}

					setMoveDirection(Settings::DOWN);
					if (!Playground::getInstance().detectCollision(this))
					{
						newPosition = position + Settings::DOWN * MoveStep;

						hValue = glm::length(target - newPosition) * Settings::HeuristicMistakeDown;
						a.fValue = gValue + hValue;
						a.position = newPosition;

						if (visited.find(newPosition) == visited.end())
						{
							visited.insert(newPosition);
							_movePath[newPosition] = Settings::DOWN;
							queue.push(a);
						}
					}

					setMoveDirection(Settings::LEFT);
					if (!Playground::getInstance().detectCollision(this))
					{
						newPosition = position + Settings::LEFT * MoveStep;

						hValue = glm::length(target - newPosition) * Settings::HeuristicMistakeLeft;
						a.fValue = gValue + hValue;
						a.position = newPosition;

						if (visited.find(newPosition) == visited.end())
						{
							visited.insert(newPosition);
							_movePath[newPosition] = Settings::LEFT;
							queue.push(a);
						}
					}

					setMoveDirection(Settings::RIGHT);
					if (!Playground::getInstance().detectCollision(this))
					{
						newPosition = position + Settings::RIGHT * MoveStep;

						hValue = glm::length(target - newPosition) * Settings::HeuristicMistakeRight;
						a.fValue = gValue + hValue;
						a.position = newPosition;

						if (visited.find(newPosition) == visited.end())
						{
							visited.insert(newPosition);
							_movePath[newPosition] = Settings::RIGHT;
							queue.push(a);
						}
					}
				}

				glm::vec3 position;
				setPosition(initialPosition);
				if (!queue.empty())
				{
					position = queue.top().position;
				}
				glm::vec3 moveDirection = _movePath[position];
				
				while (initialPosition != position)
				{
					moveDirection = _movePath[position];
					position -= moveDirection * glm::length(MoveStep);
				}

				setMoveDirection(moveDirection);
			}
			else
			{
				glm::vec3 directionOfPacman = Playground::getInstance().getPlayer()->getPosition() - getPosition();
				glm::vec3 newMoveDirection;

				double cross = 10;

				if (movableUP && initialMoveDirection != Settings::DOWN)
				{
					if (cross > glm::dot(Settings::UP, directionOfPacman))
					{
						cross = glm::dot(Settings::UP, directionOfPacman);
						newMoveDirection = Settings::UP;
					}
				}

				if (movableDOWN && initialMoveDirection != Settings::UP)
				{
					if (cross > glm::dot(Settings::DOWN, directionOfPacman))
					{
						cross = glm::dot(Settings::DOWN, directionOfPacman);
						newMoveDirection = Settings::DOWN;
					}
				}

				if (movableLEFT && initialMoveDirection != Settings::RIGHT)
				{
					if (cross > glm::dot(Settings::LEFT, directionOfPacman))
					{
						cross = glm::dot(Settings::LEFT, directionOfPacman);
						newMoveDirection = Settings::LEFT;
					}
				}

				if (movableRIGHT && initialMoveDirection != Settings::LEFT)
				{
					if (cross > glm::dot(Settings::RIGHT, directionOfPacman))
					{
						cross = glm::dot(Settings::RIGHT, directionOfPacman);
						newMoveDirection = Settings::RIGHT;
					}
				}

				setMoveDirection(newMoveDirection);
			}
		}
		else if (movableDirections == 2 && (movableUP != movableDOWN && movableLEFT != movableRIGHT))
		{
			glm::vec3 newMoveDirection;

			if (movableUP && initialMoveDirection != Settings::DOWN) 
			{
				setMoveDirection(Settings::UP);
			}
			else if (movableDOWN && initialMoveDirection != Settings::UP) 
			{
				setMoveDirection(Settings::DOWN);
			}
			else if (movableLEFT && initialMoveDirection != Settings::RIGHT)
			{
				setMoveDirection(Settings::LEFT);
			}
			else if (movableRIGHT && initialMoveDirection != Settings::LEFT)
			{
				setMoveDirection(Settings::RIGHT);
			}
		}
	}
}

void Ghost::caughtPlayer()
{
	Playground::getInstance().getScoreboard()->removeLive();
	if (!Playground::getInstance().getScoreboard()->getLives())
	{
		Playground::getInstance().Lost();
	}
	else
	{
		Playground::getInstance().resetPositions();
	}
}

void Ghost::setModeChase()
{
	if (_timerID) 
	{
		SDL_RemoveTimer(_timerID);
		_timerID = 0;
	}
	_mode = Settings::GhostModeChase;
	_eaten = false;
	_frightened = false;
	_targetPosition = Playground::getInstance().getPlayer()->getPosition();
}

Uint32 Ghost::setModeChaseTimer(Uint32 timer, void* p)
{
	Ghost* self = reinterpret_cast<Ghost*>(p);
	self->setModeChase();
	return 0;
}

void Ghost::setModeScatter()
{
	_mode = Settings::GhostModeScatter;

	_eaten = false;
	_frightened = false;

	if (_name == Settings::GhostBlinky) 
	{ 
		_targetPosition = Settings::PlaygroundTopRightCorner; 
	}
	else if (_name == Settings::GhostPinky) 
	{ 
		_targetPosition = Settings::PlaygroundTopLeftCorner; 
	}
	else if (_name == Settings::GhostInky) 
	{ 
		_targetPosition = Settings::PlaygroundBottomRightCorner; 
	}
	else if (_name == Settings::GhostClyde) 
	{ 
		_targetPosition = Settings::PlaygroundBottomLeftCorner; 
	}
}

void Ghost::setModeFrightened()
{
	if (_mode != Settings::GhostModeEaten)
	{
		if (_mode != Settings::GhostModeFrightened)
		{
			reverseMoveDirection();
		}
		_mode = Settings::GhostModeFrightened;
		_frightened = true;
		if (_timerID)
		{
			SDL_RemoveTimer(_timerID);
			_timerID = 0;
		}
		_timerID = SDL_AddTimer(Settings::FrightenedTimer, setModeChaseTimer, this);
	}
}


void Ghost::setModeEaten()
{
	if (_timerID) 
	{
		SDL_RemoveTimer(_timerID);
		_timerID = 0;
	}
	
	Playground::getInstance().getScoreboard()->updateScore(Settings::GhostEatenPoints);

	_mode = Settings::GhostModeEaten;
	_eaten = true;
	_targetPosition = Settings::DefaultVector;
}

void Ghost::resetPosition()
{
	setPosition(_defaultPosition);
}

void Ghost::reverseMoveDirection()
{
	setMoveDirection(-getMoveDirection());
}

void Ghost::draw()
{
	if (!_eaten && _frightened) 
	{
		(_bodyFrightened.begin() + iterator)->draw();
	}

	if (!_eaten && !_frightened)
	{
		MovableObject::draw();
	}

	_timer++;
	if (_timer >= Settings::MoveGhostEyesDelay) 
	{
		_eyes.begin()->draw();
		if (_timer == 2 * Settings::MoveGhostEyesDelay)
		{
			_timer = 0;
		}
	}
	else _eyes.back().draw();
}