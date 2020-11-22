#include "Manager.h"


CurveManager* Manager::getCurveManager()
{
	return curveManager;
}

void Manager::createCurves()
{
	curveManager->createBSpline();
	curveManager->createInternalCurve(10);
	curveManager->createExternalCurve(10);
}

int Manager::mouse(double mx, double my)
{
	glm::vec3* mousePos = new glm::vec3(mx, windowHeight - my, 0.0f);

	if (edit == false && (curveManager->getControlPoints().empty() || arePointsDifferent(mousePos))) {
		curveManager->addControlPoint(mousePos);
	}

	return curveManager->getControlPoints().size();
}

bool Manager::arePointsDifferent(glm::vec3* point) {

	glm::vec3* point2 = curveManager->getControlPoints().back();

	return point->x != point2->x && point->y != point2->y;
}

void Manager::editPoints(double mx, double my, int numPoints)
{
	glm::vec3* mousePos = new glm::vec3(mx, windowHeight - my, 0.0f);

	float distance, shortestDistance;

	for (int i = 0; i < numPoints; i++) {
		//raiz(pow(xb - xa) + pow(yb - ya) + pow(zb - za))
		glm::vec3* controlPos = curveManager->getControlPoints()[i];
		distance = glm::sqrt(
			pow(mousePos->x - controlPos->x, 2) +
			pow(mousePos->y - controlPos->y, 2) +
			pow(mousePos->z - controlPos->z, 2));

		if (i == 0) {
			shortestDistance = distance;
			shortestDistancePointToClick = 0;
		}

		if (distance < shortestDistance) {
			shortestDistance = distance;
			shortestDistancePointToClick = i;
		}
	}
}

void Manager::setWindowHeight(int windowHeight)
{
	this->windowHeight = windowHeight;
}

void Manager::addHeight()
{
	int size = curveManager->getControlPoints().size();
	int position;

	if (shortestDistancePointToClick == -1) {
		position = size - 1;
	}
	else {
		position = shortestDistancePointToClick;
	}

	if (size >= 4) {
		glm::vec3* lastPoint = curveManager->getControlPoints()[position];
		if (lastPoint->z >= 0 && lastPoint->z < 1) {
			lastPoint->z += 0.25f;
			curveManager->editControlPoint(lastPoint, position);
		}
	}
}

void Manager::subtractHeight()
{
	int size = curveManager->getControlPoints().size();
	int position;

	if (shortestDistancePointToClick == -1) {
		position = size;
	}
	else {
		position = shortestDistancePointToClick;
	}

	if (size >= 4) {
		glm::vec3* lastPoint = curveManager->getControlPoints()[position];
		if (lastPoint->z > 0 && lastPoint->z <= 1) {
			lastPoint->z -= 0.25f;
			curveManager->editControlPoint(lastPoint, position);
		}
	}

}

bool Manager::getEdit()
{
	return edit;
}

void Manager::setEdit(bool edit)
{
	this->edit = edit;
}
