#pragma once

#include <string>
#include "Models/Letter.h"
#include "Settings/Settings.h"
#include "Models/BasicDrawableObject.h"

#include <iostream>

class Scoreboard {

public:

	Scoreboard();

	void displayWon();

	void displayLost();

	void initMessages();

	void initFinalMessages();

	void draw();

	const unsigned short getLives() const;

	void removeLive();

	void updateScore(unsigned short);

private:

	std::vector<Letter> _scoreMessage;

	std::vector<Letter> _wonMessage;

	std::vector<Letter> _lostMessage;

	unsigned short _score;

	unsigned short _lives;

	bool _displayWon;

	bool _displayLost;

	BasicDrawableObject _live;

};