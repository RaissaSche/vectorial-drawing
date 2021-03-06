#include "CurveManager.h"



void CurveManager::createBSpline()
{
	float inc = 1.0f / 100.0f;
	float x, y, z;
	int size = controlPoints.size();
	bSplineCurvePoints.clear();

	for (int i = 0; i < size; i++) {
		for (float t = 0; t <= 1; t += inc) {
			x = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * controlPoints[i]->x +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 4) * controlPoints[(i + 1) % size]->x +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * controlPoints[(i + 2) % size]->x +
				(1 * pow(t, 3)) * controlPoints[(i + 3) % size]->x) / 6);

			y = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * controlPoints[i]->y +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 4) * controlPoints[(i + 1) % size]->y +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * controlPoints[(i + 2) % size]->y +
				(1 * pow(t, 3)) * controlPoints[(i + 3) % size]->y) / 6);

			z = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * controlPoints[i]->z +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 4) * controlPoints[(i + 1) % size]->z +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * controlPoints[(i + 2) % size]->z +
				(1 * pow(t, 3)) * controlPoints[(i + 3) % size]->z) / 6);

			bSplineCurvePoints.push_back(x);
			bSplineCurvePoints.push_back(y);
			bSplineCurvePoints.push_back(z);
		}
	}
}

void CurveManager::createInternalCurve(int thickness)
{
	float x, y, z, width, height, alpha, teta;
	float halfPi = glm::half_pi<float>();
	int size = bSplineCurvePoints.size();
	internalCurvePoints.clear();

	for (int i = 0; i < size; i += 3) { //loop through each point: x, y, z

		glm::vec3 p1 = glm::vec3(bSplineCurvePoints[i],
			bSplineCurvePoints[(i + 1) % size],
			bSplineCurvePoints[(i + 2) % size]);
		glm::vec3 p2 = glm::vec3(bSplineCurvePoints[(i + 3) % size],
			bSplineCurvePoints[(i + 4) % size],
			bSplineCurvePoints[(i + 5) % size]);

		width = p2.x - p1.x;
		height = p2.y - p1.y;
		teta = glm::atan(height / width);

		if (width > 0) {
			alpha = teta - halfPi;
		}
		else {
			alpha = teta + halfPi;
		}

		x = glm::cos(alpha) * thickness + p1.x;
		y = glm::sin(alpha) * thickness + p1.y;
		z = bSplineCurvePoints[(i + 2) % size];

		internalCurvePoints.push_back(x);
		internalCurvePoints.push_back(y);
		internalCurvePoints.push_back(z);
	}
}

void CurveManager::createExternalCurve(int thickness)
{
	float x, y, z, width, height, alpha, teta;
	float halfPi = glm::half_pi<float>();
	int size = bSplineCurvePoints.size();
	externalCurvePoints.clear();

	for (int i = 0; i < size; i += 3) { //loop through each point: x, y, z

		glm::vec3 p1 = glm::vec3(bSplineCurvePoints[i],
			bSplineCurvePoints[(i + 1) % size],
			bSplineCurvePoints[(i + 2) % size]);
		glm::vec3 p2 = glm::vec3(bSplineCurvePoints[(i + 3) % size],
			bSplineCurvePoints[(i + 4) % size],
			bSplineCurvePoints[(i + 5) % size]);

		width = p2.x - p1.x;
		height = p2.y - p1.y;
		teta = glm::atan(height / width);

		if (width < 0) {
			alpha = teta - halfPi;
		}
		else {
			alpha = teta + halfPi;
		}

		x = glm::cos(alpha) * thickness + p1.x;
		y = glm::sin(alpha) * thickness + p1.y;
		z = bSplineCurvePoints[(i + 2) % size];

		externalCurvePoints.push_back(x);
		externalCurvePoints.push_back(y);
		externalCurvePoints.push_back(z);
	}
}

void CurveManager::initializeVAOsVBOs()
{
	//control VAO & VBO
	glGenVertexArrays(1, &VAOcontrol);
	glGenBuffers(1, &VBOcontrol);

	glBindVertexArray(VAOcontrol);
	glBindBuffer(GL_ARRAY_BUFFER, VBOcontrol);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	//bspline VAO & VBO
	glGenVertexArrays(1, &VAObspline);
	glGenBuffers(1, &VBObspline);

	glBindVertexArray(VAObspline);
	glBindBuffer(GL_ARRAY_BUFFER, VBObspline);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	//internal curve VAO & VBO
	glGenVertexArrays(1, &VAOinternal);
	glGenBuffers(1, &VBOinternal);

	glBindVertexArray(VAOinternal);
	glBindBuffer(GL_ARRAY_BUFFER, VBOinternal);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	//external curve VAO & VBO
	glGenVertexArrays(1, &VAOexternal);
	glGenBuffers(1, &VBOexternal);

	glBindVertexArray(VAOexternal);
	glBindBuffer(GL_ARRAY_BUFFER, VBOexternal);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

GLuint CurveManager::controlPointsToVBO()
{
	std::vector<float> vertex;

	for (int i = 0; i < controlPoints.size(); i++) {
		glm::vec3* v = controlPoints[i];
		vertex.push_back(v->x);
		vertex.push_back(v->y);
		vertex.push_back(v->z);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBOcontrol);

	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(GLfloat),
		vertex.data(), GL_STATIC_DRAW);

	return VAOcontrol;
}

GLuint CurveManager::curvePointsToVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBObspline);

	glBufferData(GL_ARRAY_BUFFER, bSplineCurvePoints.size() * sizeof(GLfloat),
		bSplineCurvePoints.data(), GL_STATIC_DRAW);

	return VAObspline;
}

GLuint CurveManager::internalCurvePointsToVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBOinternal);

	glBufferData(GL_ARRAY_BUFFER, internalCurvePoints.size() * sizeof(GLfloat),
		internalCurvePoints.data(), GL_STATIC_DRAW);

	return VAOinternal;
}

GLuint CurveManager::externalCurvePointsToVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBOexternal);

	glBufferData(GL_ARRAY_BUFFER, externalCurvePoints.size() * sizeof(GLfloat),
		externalCurvePoints.data(), GL_STATIC_DRAW);

	return VAOexternal;
}

std::vector<glm::vec3*> CurveManager::getControlPoints()
{
	return controlPoints;
}

std::vector<float> CurveManager::getBSplineCurvePoints()
{
	return bSplineCurvePoints;
}

std::vector<float> CurveManager::getInternalCurvePoints()
{
	return internalCurvePoints;
}

std::vector<float> CurveManager::getExternalCurvePoints()
{
	return externalCurvePoints;
}

void CurveManager::addControlPoint(glm::vec3* point)
{
	controlPoints.push_back(point);
}

void CurveManager::editControlPoint(glm::vec3* point, int position)
{
	controlPoints[position] = point;
}
