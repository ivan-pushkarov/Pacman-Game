#include "scoreboard.h"

Scoreboard::Scoreboard() : _score(0), _lives(3), _live(Settings::PacmanState1), _displayWon(false), _displayLost(false)
{
	initMessages();

	initFinalMessages();

	_live.setRotation(glm::vec3(0.0, 0.0, 2 * Settings::Rotation));
}

void Scoreboard::draw()
{
	for (std::vector<Letter>::iterator it = _scoreMessage.begin(); it != _scoreMessage.end(); ++it)
	{
		it->draw();
	}

	if (_displayWon)
	{
		for (std::vector<Letter>::iterator it = _wonMessage.begin(); it != _wonMessage.end(); ++it)
		{
			it->draw();
		}
	}

	if (_displayLost)
	{
		for (std::vector<Letter>::iterator it = _lostMessage.begin(); it != _lostMessage.end(); ++it)
		{
			it->draw();
		}
	}

	for (unsigned short i = 0; i < _lives; i++)
	{
		_live.setPosition(Settings::ScoreBoardLivesPosition + (float)(5.5 + i) * Settings::TilesStep * Settings::RIGHT);
		_live.draw();
	}
}

void Scoreboard::displayWon()
{
	_displayWon = true;
}

void Scoreboard::displayLost()
{
	_displayLost = true;
}

void Scoreboard::initFinalMessages()
{
	_wonMessage.clear();

	glm::vec3 lettersOffset = Settings::TilesStep * Settings::RIGHT;

	std::string text = Settings::WinConditionMessage;

	Letter first(text[0]);
	first.setPosition(Settings::WonMessagePosition + glm::vec3(0.0, -(first.getHeight() / 2), 0.0));
	first.setScale(Settings::NormalScale);
	_wonMessage.push_back(first);

	for (unsigned int i = 1; i <= text.length() - 1; i++)
	{
		Letter letter(text[i]);
		letter.setPosition(_wonMessage[i - 1].getPosition() + lettersOffset);
		if (text[i] == 'I' || text[i] == 'i')
		{
			letter.setPosition(letter.getPosition() + (float)0.5 * lettersOffset);
		}
		letter.setScale(Settings::NormalScale);
		_wonMessage.push_back(letter);
	}

	_lostMessage.clear();

	text = Settings::LoseConditionMessage;

	Letter firstt(text[0]);
	firstt.setPosition(Settings::LostMessagePosition + glm::vec3(0.0, -(firstt.getHeight() / 2), 0.0));
	firstt.setScale(Settings::NormalScale);
	_lostMessage.push_back(firstt);

	for (unsigned int i = 1; i <= text.length() - 1; i++)
	{
		Letter letter(text[i]);
		letter.setPosition(_lostMessage[i - 1].getPosition() + lettersOffset);
		if (text[i] == 'I' || text[i] == 'i')
		{
			letter.setPosition(letter.getPosition() + (float)0.5 * lettersOffset);
		}
		letter.setScale(Settings::NormalScale);
		_lostMessage.push_back(letter);
	}
}

void Scoreboard::initMessages()
{
	_scoreMessage.clear();

	glm::vec3 lettersOffset = Settings::TilesStep * Settings::RIGHT;

	std::string text = Settings::ScoreMessage + std::to_string(_score);

	for (unsigned int i = 0; i < 6 - std::to_string(_score).length(); i++)
	{
		text += ' ';
	}
	
	text += Settings::LivesMessage;

	Letter init(text[0]);
	init.setPosition(Settings::ScoreBoardScorePosition + glm::vec3(0.0, -(init.getHeight() / 2), 0.0));
	init.setScale(Settings::NormalScale);
	_scoreMessage.push_back(init);

	for (unsigned int i = 1; i <= text.length() - 1; i++)
	{

		Letter letter(text[i]);
		letter.setPosition(_scoreMessage[i - 1].getPosition() + lettersOffset);
		letter.setScale(Settings::NormalScale);
		_scoreMessage.push_back(letter);
	}
}



void Scoreboard::removeLive()
{
	if (_lives != 0)
	{
		--_lives;
	}
}

const unsigned short Scoreboard::getLives() const
{
	return _lives;
}

void Scoreboard::updateScore(unsigned short score)
{
	_score += score;
	initMessages();
}