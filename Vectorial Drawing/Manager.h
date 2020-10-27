#pragma once

#include <vector>

// External Libs
#include <GL\glew.h>
#include <GLFW\glfw3.h>

// GLM Includes
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Manager
{
private:
	std::vector<glm::vec2*> points;

public:
	void casteljau();
	GLuint pointsToVBO();
	std::vector<glm::vec2*> getPoints();
	void setPoints(std::vector<glm::vec2*> points);
	void addPoint(glm::vec2* point);
};
