#include "Manager.h"
#include <iostream>
#include <fstream>


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

	bool firstItem = true;
	float distance, shortestDistance;

	for (int i = 0; i < numPoints; i++) {
		//raiz(pow(xb - xa) + pow(yb - ya) + pow(zb - za))
		glm::vec3* controlPos = curveManager->getControlPoints()[i];
		distance = glm::sqrt(glm::exp2(mousePos->x - controlPos->x) +
			glm::exp2(mousePos->y - controlPos->y) +
			glm::exp2(mousePos->z - controlPos->z));

		if (firstItem) {
			shortestDistance = distance;
			firstItem = false;
		}

		if (distance < shortestDistance) {
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
		position = size;
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

//gravar o y no lugar do z, e vice-versa
//multiplicar a z com uma variável de altura, 0 a 1 é muito baixinho (10)
//primeiro: gravar todos os vértices (x, y e z) da curva interna, e depois da externa
//segundo: gravar os mapeamentos de textura: 
	//conseguir uma foto próxima de asfalto, traçar para retângulos
//um grupo definindo a pista inteira "pista"
//mtl fixo: 
//normal: 0 1 0 pega vetor p[i] até p[i + 1] + ponto inicial de uma curva (p[i] da outra curva?)até a outra e produtoVetorial() neles!
//faces: vértices interna começam em 1 e terminam em N 
	//da externa começam em N+1 até 2N
	//for de i==1 até i<=N
		//i e i + 1 e i + N ----- i + N e i + 1 e i+N+1

void Manager::createObj()
{
	auxInternal = curveManager->getInternalCurvePoints();
	auxExternal = curveManager->getExternalCurvePoints();

	std::ofstream arq("track.obj");

	for (int i = 0; i < auxInternal.size(); i += 3) {//loop through each point: x, y, z
		arq << "v " << auxInternal[i] << " " //x
					<< auxInternal[i + 2] * 10 << " " //z
					<< auxInternal[i + 1] << std::endl; //y
	}

	arq << " " << std::endl;

	for (int i = 0; i < auxExternal.size(); i += 3) {
		arq << "v " << auxExternal[i] << " " //x
			<< auxExternal[i + 2] * 10 << " " //z
			<< auxExternal[i + 1] << std::endl; //y
	}

	arq << " " << std::endl;

	arq << "vt " << 0 << " " << 0 << std::endl;
	arq << "vt " << 1 << " " << 0 << std::endl;
	arq << "vt " << 1 << " " << 1 << std::endl;
	arq << "vt " << 0 << " " << 1 << std::endl;

	//vn

	arq << "g track" << std::endl;
	arq << "usemtl track" << std::endl;

	//faces

	arq.close();

}

/*
static void System::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS) {
		if (curveManager->getControlPoints().size() >= 4) {
			glm::vec3* lastPoint = curveManager->getControlPoints().back();
			if (lastPoint->z >= 0 && lastPoint->z < 1) {
				curveManager->getControlPoints().pop_back();
				lastPoint->z += 0.25f;
				curveManager->addControlPoint(lastPoint);
			}
		}
	}
}
*/
