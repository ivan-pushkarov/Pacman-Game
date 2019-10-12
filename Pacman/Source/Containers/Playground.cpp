#include "Playground.h"

Playground::Playground() : _won(false), _lost(false), _pacmanMoved(false), _totalTimePlayed(0)
{
	int row = 0;
	int col = 0;

	pacman = new Pacman;

	scoreboard = new Scoreboard;

	for (float j = Settings::PlaygroundEnd; j >= Settings::PlaygroundStart; j -= Settings::TilesStep)
	{
		col = 0;
		for (float i = Settings::PlaygroundStart; i <= Settings::PlaygroundEnd; i += Settings::TilesStep)
		{
			if (Settings::Level[row][col] == Settings::LevelWallValue)
			{
				_walls.push_back(BasicDrawableObject(Settings::Wall));
				_walls.back().setPosition(glm::vec3(i, j, 0.0));
			}
			else if (Settings::Level[row][col] == Settings::LevelPointValue)
			{
				_points.push_back(BasicDrawableObject(Settings::Point));
				_points.back().setPosition(glm::vec3(i, j, 0.0));
				_points.back().setScale(Settings::PointsScale);
			}
			else if (Settings::Level[row][col] == Settings::LevelPillValue)
			{
				_pills.push_back(BasicDrawableObject(Settings::Pill));
				_pills.back().setPosition(glm::vec3(i, j, 0.0));
				_pills.back().setScale(Settings::PillsScale);
			}
			else if (Settings::Level[row][col] == Settings::LevelBlinkyValue ||
					 Settings::Level[row][col] == Settings::LevelPinkyValue ||
				     Settings::Level[row][col] == Settings::LevelInkyValue ||
					 Settings::Level[row][col] == Settings::LevelClydeValue)
			{
				if (Settings::Level[row][col] == Settings::LevelBlinkyValue)
				{
					_ghosts.push_back(Ghost(Settings::GhostBlinky));
				}
				else if (Settings::Level[row][col] == Settings::LevelPinkyValue)
				{
					_ghosts.push_back(Ghost(Settings::GhostPinky));
				}
				else if (Settings::Level[row][col] == Settings::LevelInkyValue)
				{
					_ghosts.push_back(Ghost(Settings::GhostInky));
				}
				else if (Settings::Level[row][col] == Settings::LevelClydeValue)
				{
					_ghosts.push_back(Ghost(Settings::GhostClyde));
				}
				_ghosts.back().setPosition(glm::vec3(i, j, 0.0));
				_ghosts.back().setDefaultPosition(glm::vec3(i, j, 0.0));
			}
			else if (Settings::Level[row][col] == Settings::LevelEntranceGhostHauseValue)
			{
				_walls.push_back(BasicDrawableObject(""));
				_walls.back().setType(Settings::TypeEntranceGhostHouse);
				_walls.back().setPosition(glm::vec3(i, j, 0.0));
			}
			else if (Settings::Level[row][col] == Settings::LevelPacmanValue)
			{
				pacman->setPosition(glm::vec3(i, j, 0.0));
				pacman->setDefaultPosition(glm::vec3(i, j, 0.0));
			}
			_tiles.insert(glm::vec3(i, j, 0.0));
			col++;
		}
		row++;
	}

}

Playground& Playground::getInstance()
{
	static Playground instance;

	return instance;
}

const bool Playground::findTile(const glm::vec3& position) const
{
	if (_tiles.find(position) != _tiles.end())
	{
		return true;
	}
	return false;
}

bool Playground::play()
{
	SDL_Delay(Settings::Delay);
	if (_pacmanMoved)
	{
		_totalTimePlayed += Settings::Delay;
	}

		while (SDL_PollEvent(&e) != 0)
		{	
			if (e.type == SDL_KEYDOWN || e.type == SDL_QUIT)
			{
				if (e.type == SDL_QUIT || e.key.keysym.sym == 'q')
				{
					return false;
				}
				
				if (e.key.keysym.sym == 'w' || e.key.keysym.scancode == SDL_SCANCODE_UP)
				{
					pacman->setNextMoveDirection(Settings::UP);
				}

				if (e.key.keysym.sym == 's' || e.key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
					pacman->setNextMoveDirection(Settings::DOWN);
				}

				if (e.key.keysym.sym == 'a' || e.key.keysym.scancode == SDL_SCANCODE_LEFT)
				{
					pacman->setNextMoveDirection(Settings::LEFT);
				}

				if (e.key.keysym.sym == 'd' || e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
				{
					pacman->setNextMoveDirection(Settings::RIGHT);
				}
			}
		}

		if (!_won && !_lost)
		{
			// Move Pacman logic
			glm::vec3 initialMoveDirection = pacman->getMoveDirection();
			if (initialMoveDirection != Settings::DefaultVector)
			{
				_pacmanMoved = true;
			}
			if (pacman->getNextMoveDirection() != Settings::DefaultVector)
			{
				pacman->setMoveDirection(pacman->getNextMoveDirection());
			}

			if (!detectCollision(pacman))
			{
				pacman->clearNextMoveDirection();
				pacman->move();
			}
			else
			{
				pacman->setMoveDirection(initialMoveDirection);

				if (!detectCollision(pacman))
				{
					pacman->move();
				}
				else
					pacman->setInitialFace();
			}

			//Move ghosts logic
			if (_pacmanMoved && _totalTimePlayed >= Settings::GhostsOutDelay * Settings::Delay)
			{
				Ghost* pointer = NULL;
				int size = _ghosts.size();
				for (int i = 0; i < size; i++)
				{
					pointer = &_ghosts[i];
					pointer->chooseMoveDirection();
					if (!detectCollision(pointer))
					{
						pointer->move();
					}
				}
			}
		}

	return true;
}

const MovableObject* Playground::getPlayer() const
{
	return pacman;
}

Scoreboard* Playground::getScoreboard()
{
	return scoreboard;
}

void Playground::Won()
{
	_won = true;
	scoreboard->displayWon();
}

void Playground::Lost()
{
	_lost = true;
	scoreboard->displayLost();
}

void Playground::resetPositions()
{
	for (std::vector<Ghost>::iterator it = _ghosts.begin(); it != _ghosts.end(); it++)
	{
		it->resetPosition();
		it->setModeScatter();
		it->setMoveDirection(Settings::DefaultVector);
	}

	pacman->resetPosition();
	pacman->setRotation(Settings::DefaultVector);

	pacman->setMoveDirection(Settings::DefaultVector);
	pacman->clearNextMoveDirection();

	_pacmanMoved = false;
	_totalTimePlayed = 0;
}

bool Playground::detectCollision(MovableObject* model)
{
	glm::vec3 modelPosition = model->getPosition() + model->getMoveDirection() * glm::length(model->getMoveStep());

	glm::vec3 modelPositionTopLeft = modelPosition + Settings::TopLeft * Settings::DefaultScale;
	glm::vec3 modelPositionTopRight = modelPosition + Settings::TopRight * Settings::DefaultScale;
	glm::vec3 modelPositionBottomLeft = modelPosition + Settings::BottomLeft * Settings::DefaultScale;
	glm::vec3 modelPositionBottomRight = modelPosition + Settings::BottomRight * Settings::DefaultScale;

	// Walls collision
	for (std::vector<BasicDrawableObject>::iterator it = _walls.begin(); it != _walls.end(); it++)
	{
		glm::vec3 wallPositionTopCenter = it->getPosition() + Settings::TopCenter * Settings::DefaultScale;
		glm::vec3 wallPositionBottomCenter = it->getPosition() + Settings::BottomCenter * Settings::DefaultScale;
		glm::vec3 wallPositionLeftCenter = it->getPosition() + Settings::LeftCenter * Settings::DefaultScale;
		glm::vec3 wallPositionRightCenter = it->getPosition() + Settings::RightCenter * Settings::DefaultScale;

		if (model->getMoveDirection() == Settings::UP)
		{
			if (modelPositionTopLeft.y >= wallPositionBottomCenter.y &&
				modelPositionTopLeft.y <= wallPositionTopCenter.y &&
				modelPositionTopLeft.x >= wallPositionLeftCenter.x &&
				modelPositionTopLeft.x <= wallPositionRightCenter.x)
			{
				if (model->getType() == Settings::TypePacman)
				{
					return true;
				}
				else if (it->getType() == Settings::TypeEntranceGhostHouse)
				{
					return false;
				}
				return true;
			}

			if (modelPositionTopRight.y >= wallPositionBottomCenter.y &&
				modelPositionTopRight.y <= wallPositionTopCenter.y &&
				modelPositionTopRight.x >= wallPositionLeftCenter.x &&
				modelPositionTopRight.x <= wallPositionRightCenter.x)
			{
				if (model->getType() == Settings::TypePacman)
				{
					return true;
				}
				else if (it->getType() == Settings::TypeEntranceGhostHouse)
				{
					return false;
				}
				return true;
			}
		}

		if (model->getMoveDirection() == Settings::DOWN)
		{
			if (modelPositionBottomLeft.y <= wallPositionTopCenter.y &&
				modelPositionBottomLeft.y >= wallPositionBottomCenter.y &&
				modelPositionBottomLeft.x >= wallPositionLeftCenter.x &&
				modelPositionBottomLeft.x <= wallPositionRightCenter.x)
			{
				if (model->getType() == Settings::TypePacman)
				{
					return true;
				}
				else if (it->getType() == Settings::TypeEntranceGhostHouse)
				{
					return false;
				}
				return true;
			}

			if (modelPositionBottomRight.y <= wallPositionTopCenter.y &&
				modelPositionBottomRight.y >= wallPositionBottomCenter.y &&
				modelPositionBottomRight.x >= wallPositionLeftCenter.x &&
				modelPositionBottomRight.x <= wallPositionRightCenter.x)
			{
				if (model->getType() == Settings::TypePacman)
				{
					return true;
				}
				else if (it->getType() == Settings::TypeEntranceGhostHouse)
				{
					return false;
				}
				return true;
			}
		}

		if (model->getMoveDirection() == Settings::RIGHT)
		{
			if (modelPositionTopRight.y >= wallPositionBottomCenter.y &&
				modelPositionTopRight.y <= wallPositionTopCenter.y &&
				modelPositionTopRight.x >= wallPositionLeftCenter.x &&
				modelPositionTopRight.x <= wallPositionRightCenter.x)
			{
				if (model->getType() == Settings::TypePacman)
				{
					return true;
				}
				else if (it->getType() == Settings::TypeEntranceGhostHouse)
				{
					return false;
				}
				return true;
			}

			if (modelPositionBottomRight.y >= wallPositionBottomCenter.y &&
				modelPositionBottomRight.y <= wallPositionTopCenter.y &&
				modelPositionBottomRight.x >= wallPositionLeftCenter.x &&
				modelPositionBottomRight.x <= wallPositionRightCenter.x)
			{
				if (model->getType() == Settings::TypePacman)
				{
					return true;
				}
				else if (it->getType() == Settings::TypeEntranceGhostHouse)
				{
					return false;
				}
				return true;
			}
		}

		if (model->getMoveDirection() == Settings::LEFT)
		{
			if (modelPositionTopLeft.y >= wallPositionBottomCenter.y &&
				modelPositionTopLeft.y <= wallPositionTopCenter.y &&
				modelPositionTopLeft.x >= wallPositionLeftCenter.x &&
				modelPositionTopLeft.x <= wallPositionRightCenter.x)
			{
				if (model->getType() == Settings::TypePacman)
				{
					return true;
				}
				else if (it->getType() == Settings::TypeEntranceGhostHouse)
				{
					return false;
				}
				return true;
			}

			if (modelPositionBottomLeft.y >= wallPositionBottomCenter.y &&
				modelPositionBottomLeft.y <= wallPositionTopCenter.y &&
				modelPositionBottomLeft.x >= wallPositionLeftCenter.x &&
				modelPositionBottomLeft.x <= wallPositionRightCenter.x)
			{
				if (model->getType() == Settings::TypePacman)
				{
					return true;
				}
				else if (it->getType() == Settings::TypeEntranceGhostHouse)
				{
					return false;
				}
				return true;
			}
		}
	}
	
	if (model->getType() == Settings::TypePacman)
	{
		glm::vec3 modelPositionTopCenter = model->getPosition() + Settings::TopCenter * Settings::DefaultScale;
		glm::vec3 modelPositionBottomCenter = model->getPosition() + Settings::BottomCenter * Settings::DefaultScale;
		glm::vec3 modelPositioLeftCenter = model->getPosition() + Settings::LeftCenter * Settings::DefaultScale;
		glm::vec3 modelPositionRightCenter = model->getPosition() + Settings::RightCenter * Settings::DefaultScale;

		//Points collision
		int i = 0;
		int erase = 0;
		bool hasEaten = false;
		for (std::vector<BasicDrawableObject>::iterator it = _points.begin(); it != _points.end(); it++)
		{
			if (modelPositionTopCenter.y >= it->getPosition().y &&
				modelPositionBottomCenter.y <= it->getPosition().y &&
				modelPositionRightCenter.x >= it->getPosition().x &&
				modelPositioLeftCenter.x <= it->getPosition().x)
			{
				erase = i;
				hasEaten = true;
			}
			i++;
		}
		if (hasEaten)
		{
			_points.erase(_points.begin() + erase);
			scoreboard->updateScore(Settings::PointEatenPoints);
			if (_pills.empty() && _points.empty())
			{
				Won();
			}
		}

		//Pills collision
		i = 0;
		erase = 0;
		hasEaten = false;
		for (std::vector<BasicDrawableObject>::iterator it = _pills.begin(); it != _pills.end(); it++)
		{
			if (modelPositionTopCenter.y >= it->getPosition().y &&
				modelPositionBottomCenter.y <= it->getPosition().y &&
				modelPositionRightCenter.x >= it->getPosition().x &&
				modelPositioLeftCenter.x <= it->getPosition().x)
			{
				erase = i;
				hasEaten = true;
			}
			i++;
		}
		if (hasEaten) 
		{
			_pills.erase(_pills.begin() + erase);
			scoreboard->updateScore(Settings::PillEatenPoints);
			for (std::vector<Ghost>::iterator it = _ghosts.begin(); it != _ghosts.end(); it++)
			{
				it->setModeFrightened();
			}
			if (_pills.empty() && _points.empty())
			{
				Won();
			}
		}
	}

	return false;
}

void Playground::draw()
{
	for (std::vector<BasicDrawableObject>::iterator it = _walls.begin(); it != _walls.end(); it++)
	{
		it->draw();
	}

	for (std::vector<BasicDrawableObject>::iterator it = _pills.begin(); it != _pills.end(); it++)
	{
		it->draw();
	}

	for (std::vector<BasicDrawableObject>::iterator it = _points.begin(); it != _points.end(); it++)
	{
		it->draw();
	}

	for (std::vector<Ghost>::iterator it = _ghosts.begin(); it != _ghosts.end(); it++)
	{
		it->draw();
	}

	scoreboard->draw();

	pacman->draw();
}

Playground::~Playground()
{
	delete pacman;
	
	delete scoreboard;
}