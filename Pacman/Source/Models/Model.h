#pragma once

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#include "Settings/Settings.h"
#include "Managers/ShadersManager.h"

class Model {
public:
	Model(GLuint);

	void setType(const std::string&);

	const std::string getType() const;

	void setScale(const glm::vec3&);
	
	void setPosition(const glm::vec3&);

	void setRotation(const glm::vec3&);

	const glm::vec3 getPosition() const;

	void calcTransform();

	virtual void draw() = 0;

protected:

	std::string _type;

	std::string _file;

	GLuint _vbo;

	GLuint _programID;

	glm::mat4 _transform;

	unsigned int _numVertices;

private:

	glm::vec3 _scale;

	glm::quat _rotate;

	glm::vec3 _translate;

	glm::vec3 _eulerAngles;

};