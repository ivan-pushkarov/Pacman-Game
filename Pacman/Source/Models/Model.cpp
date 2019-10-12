#include "Model.h"

Model::Model(GLuint programID) :
	_programID(programID),
	_numVertices(0)
{
	_scale = Settings::DefaultScale;
	_rotate = glm::quat(Settings::DefaultVector);
	_translate = Settings::DefaultVector;

	calcTransform();
}

const std::string Model::getType() const
{
	return _type;
}

void Model::setType(const std::string& type)
{
	_type = type;
}

void Model::setScale(const glm::vec3& scale)
{
	_scale = scale;

	calcTransform();
}

void Model::setPosition(const glm::vec3& translate)
{
	_translate = translate;

	calcTransform();
}

const glm::vec3 Model::getPosition() const
{
	return _translate;
}

void Model::setRotation(const glm::vec3& rotation)
{
	if (_type != "ghost")
	{
		_eulerAngles = rotation;

		_rotate = glm::quat(_eulerAngles);

		calcTransform();
	}
}

void Model::calcTransform()
{
	_transform = glm::translate(glm::mat4(1.0f), _translate) * glm::mat4(_rotate) * glm::scale(glm::mat4(1.0f), _scale);
}