#include "basicdrawableobject.h"

BasicDrawableObject::BasicDrawableObject(const std::string& file) : Model(ShadersManager::getInstance().getProgramID(Settings::BasicShader))
{
	_file = file;

	_vbo = ModelsManager::getInstance().getVBO(file);

	loadModelToVRAM();
}

void BasicDrawableObject::loadModelToVRAM()
{
	std::vector<GLfloat> _colors;
	std::vector<GLfloat> _coordinates;

	std::string vertex;
	std::ifstream _model(Settings::ModelsFilesPath + _file);

	char* value;
	unsigned int iterator = 0;

	if (_model.is_open())
	{
		while (getline(_model, vertex))
		{
			vertex.erase(std::remove(vertex.begin(), vertex.end(), ' '), vertex.end());
			
			iterator = 0;
			char* context = NULL;
			char * string = _strdup(vertex.c_str());

			value = strtok_s(string, ",()", &context);
			while (value != NULL)
			{
				iterator++;

				// The first three floating point values are always representing a position
				// the rest are representing colors.
				if (iterator <= 3)
				{
					_coordinates.push_back((GLfloat)(std::stof(value)));
				}
				else
				{
					_colors.push_back((GLfloat)(std::stof(value)));
				}

				value = strtok_s(NULL, ",()", &context);
			}

			delete[] string;

			_numVertices++;
		}
		_model.close();
	}
	else
	{
		std::cout << "An error occured while opening model file: " << _file.c_str() << "model.";
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glBufferData(GL_ARRAY_BUFFER, _numVertices * 7 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, _numVertices * 3 * sizeof(GLfloat), _coordinates.data());
	glBufferSubData(GL_ARRAY_BUFFER, _numVertices * 3 * sizeof(GLfloat), _numVertices * 4 * sizeof(GLfloat), _colors.data());
}

void BasicDrawableObject::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glUseProgram(_programID);

	GLuint positionID = glGetAttribLocation(_programID, "_Position");
	GLuint colorID = glGetAttribLocation(_programID, "_Color");
	GLuint matrixID = glGetUniformLocation(_programID, "mT");

	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(matrixID);

	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(_numVertices * 3 * sizeof(GLfloat)));

	glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(_transform));

	glDrawArrays(GL_TRIANGLES, 0, _numVertices);
}