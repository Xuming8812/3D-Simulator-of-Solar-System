#pragma once

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


#include "AstronmicalObject.h"
#include <map>

class SolarSystem
{
public:
	//constructor
	SolarSystem();
	//destructor
	~SolarSystem();




	//display the whole solar system
	void display();
	//update the whole solar system
	void update();
	//respond to the whole solar system
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


    std::vector<AstronmicalObject*> getObjects(){
        return objects;
    }


private:

	//enum for type of an astronmical object
	enum OBJECTTYPE { STAR, PLANET, SATELLITE };

	//parameters for an astronmical object
	struct objectInfo
	{
		std::string name;
		OBJECTTYPE type;
		GLfloat speedRevolution;
		GLfloat speedRotation;
		GLfloat radius;
        GLfloat mass;
		GLfloat distance;
		std::string parentName;
		GLfloat color[4];
	};

	//std::map<std::string,AstronmicalObject> objects;
	
	//store all the pointers to the objects in the solar system
	std::vector<AstronmicalObject*> objects;
	
	//total number of objects in the system
	int objectNum;

	//store all the parameters for each and every object in the system
	std::vector<objectInfo> parameters;
	
	//parameters for eye system
	GLdouble eyeX, eyeY, eyeZ;
	GLdouble centerX, centerY, centerZ;
	GLdouble upX, upY, upZ;

	//helper function to read in parameters from external file
	std::string getStringParameter(std::string input);
	OBJECTTYPE getTypeParameter(std::string input);
	GLfloat getFloatParameter(std::string input);
	GLfloat* getArrayParameter(std::string input);
};

