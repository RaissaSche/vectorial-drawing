#include "Manager.h"



void Manager::createBSpline()
{
	float inc = 1.0f / 100.0f;
	float x, y, z;
	int size = controlPoints.size();
	curvePoints.clear();

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

			curvePoints.push_back(x);
			curvePoints.push_back(y);
			curvePoints.push_back(z);
		}
	}
}

void Manager::createInternalCurve()
{
}

void Manager::initializeVAOsVBOs()
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
}

GLuint Manager::controlPointsToVBO()
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

GLuint Manager::curvePointsToVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBObspline);

	glBufferData(GL_ARRAY_BUFFER, curvePoints.size() * sizeof(GLfloat),
		curvePoints.data(), GL_STATIC_DRAW);

	return VAObspline;
}

std::vector<glm::vec3*> Manager::getControlPoints()
{
	return controlPoints;
}

std::vector<float> Manager::getCurvePoints()
{
	return curvePoints;
}

void Manager::addControlPoint(glm::vec3* point)
{
	controlPoints.push_back(point);
}
