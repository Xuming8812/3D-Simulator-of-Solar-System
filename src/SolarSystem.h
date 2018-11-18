#pragma once

#include <GL/glut.h>
#include "AstronmicalObject.h"
#include <map>

class SolarSystem
{
public:

	SolarSystem();

	~SolarSystem();

	void display();
	void update();
	void keyboard(unsigned char key, int x, int y);

	void readParameters();

	//set eye coordinate in world coordinate system
	void setEyeCoordinate(GLdouble x, GLdouble y, GLdouble z)
	{
		eyeX = x;
		eyeY = y;
		eyeZ = z;
	}
	//set center of solarsystem in world coordinate system
	void setCenterCoordinate(GLdouble x, GLdouble y, GLdouble z)
	{
		centerX = x;
		centerY = y;
		centerZ = z;
	}
	//set direction of eye in world coordinate system
	void setUpCoordinate(GLdouble x, GLdouble y, GLdouble z)
	{
		upX = x;
		upY = y;
		upZ = z;
	}

private:
	enum OBJECTTYPE { STAR, PLANET, SATELLITE };

	struct objectInfo
	{
		std::string name;
		OBJECTTYPE type;
		GLfloat speedRevolution;
		GLfloat speedRotation;
		GLfloat radius;
		GLfloat distance;
		std::string parentName;
		GLfloat color[4];
	};



	//std::map<std::string,AstronmicalObject> objects;

	std::vector<AstronmicalObject*> objects;

	int objectNum;

	std::vector<objectInfo> parameters;
	// 定义观察视角的参数
	GLdouble eyeX, eyeY, eyeZ;
	GLdouble centerX, centerY, centerZ;
	GLdouble upX, upY, upZ;


	std::string getStringParameter(std::string input);
	OBJECTTYPE getTypeParameter(std::string input);
	GLfloat getFloatParameter(std::string input);
	GLfloat* getArrayParameter(std::string input);
};

