#pragma once

#include <vector>

// External Libs
#include <GL\glew.h>
#include <GLFW\glfw3.h>

// GLM Includes
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class CurveManager
{
private:
	std::vector<glm::vec3*> controlPoints;
	std::vector<float> bSplineCurvePoints, internalCurvePoints, externalCurvePoints;
	GLuint VAOcontrol, VBOcontrol, VAObspline, VBObspline,
		VAOinternal, VBOinternal, VAOexternal, VBOexternal;
	GLuint shaderProgram;

public:
	//create
	void createBSpline();
	void createInternalCurve(int size);
	void createExternalCurve(int size);

	//VAOs and VBOs
	void initializeVAOsVBOs();
	GLuint controlPointsToVBO();
	GLuint curvePointsToVBO();
	GLuint internalCurvePointsToVBO();
	GLuint externalCurvePointsToVBO();

	//GETs, SETs and ADDs
	std::vector<glm::vec3*> getControlPoints();
	std::vector<float> getBSplineCurvePoints();
	std::vector<float> getInternalCurvePoints();
	std::vector<float> getExternalCurvePoints();
	void addControlPoint(glm::vec3* point);
	void editControlPoint(glm::vec3* point, int position);
};
