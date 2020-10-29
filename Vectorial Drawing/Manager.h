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
	std::vector<glm::vec3*> controlPoints;
	std::vector<float> curvePoints;
	GLuint VAOcontrol, VBOcontrol,
		VAObspline, VBObspline;

public:
	//void createCasteljau();
	void createBSpline();
	void initializeVAOsVBOs();
	GLuint controlPointsToVBO();
	GLuint curvePointsToVBO();
	std::vector<glm::vec3*> getControlPoints();
	void addControlPoint(glm::vec3* point);
};
