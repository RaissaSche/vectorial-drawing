#pragma once

#include <vector>
#include "CurveManager.h"
	
class ObjManager
{
private:
	CurveManager* curveManager;
	std::vector<float> auxInternal, auxExternal, auxBSpline;
	int size;

public:
	void createObj(CurveManager* curveManager);
	glm::vec3 createVectorFrom2Points(glm::vec3 a, glm::vec3 b);
	void createBSplinePointsTxt(CurveManager* curveManager);
};
