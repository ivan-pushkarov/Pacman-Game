#pragma once

#include "Models/Model.h"
#include <string>
#include <iostream>
#include <algorithm>
#include "Managers/ModelsManager.h"

class BasicDrawableObject : public Model {

public:

	BasicDrawableObject(const std::string&);

	void draw();

	virtual void loadModelToVRAM();

private:

};