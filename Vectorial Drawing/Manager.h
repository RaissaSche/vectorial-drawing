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
	std::vector<float> curvePoints, internalCurvePoints, externalCurvePoints;
	GLuint VAOcontrol, VBOcontrol, VAObspline, VBObspline,
			VAOinternal, VBOinternal, VAOexternal, VBOexternal;

public:
	//void createCasteljau();
	void createBSpline();
	void createInternalCurve(int size);
	void createExternalCurve(int size);
	void initializeVAOsVBOs();
	GLuint controlPointsToVBO();
	GLuint curvePointsToVBO();
	GLuint internalCurvePointsToVBO();
	GLuint externalCurvePointsToVBO();
	std::vector<glm::vec3*> getControlPoints();
	std::vector<float> getCurvePoints();
	void addControlPoint(glm::vec3* point);
};
