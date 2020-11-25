#pragma once

// GLM Includes
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "CurveManager.h"

class Manager
{
private:
	CurveManager* curveManager;
	int shortestDistancePointToClick;
	bool edit;
	int windowHeight;

public:
	Manager();
	void createCurves();
	CurveManager* getCurveManager();

	int mouse(double mx, double my);
	bool arePointsDifferent(glm::vec3* point);
	void editPoints(double mx, double my, int numPoints);
	void setWindowHeight(int windowHeight);

	void addHeight();
	void subtractHeight();
	bool getEdit();
	void setEdit(bool edit);
};

