#include "AstronmicalObject.h"
#include <cmath>
#include <vector>

#define PI 3.1415926

#define SLICES 50
#define STACKS 50

#define NUM_ELEMENT 1000

/**
 * @name: AstronmicalObject
 * @description: Construtor of the AstronmicalObject class
 * @param label: name of the object
 * @param r: radius
 * @param d: distance to parent 
 * @param sRevolute: speed of revolution
 * @param sRotate: speed of rotation
 * @param par: pointer to parent object
 * @return: void
 */
AstronmicalObject::AstronmicalObject(std::string label, GLfloat r, GLfloat m, GLfloat d,
	GLfloat sRevolute, GLfloat sRotate, AstronmicalObject* par) 
{
    this->mySphere = gluNewQuadric();
	this->name = label;
	this->radius = r;
    this->mass = m;
	this->distance = d;

	this->speedRotation = sRotate;

    this->isVisible = true;
	
	//actually the speed is an angular velocity in degree
	if (sRevolute > 0)
	{
		this->speedRevolution = 360.0 / sRevolute;
	}
	else
	{
		this->speedRevolution = 0;
	}

	this->parent = par;
}

/**
 * @brief AstronmicalObject::~AstronmicalObject
 */
AstronmicalObject::~AstronmicalObject(){}

/**
 * @name: drawObject
 * @description: Draw the astronmical object based on the graphic parameters
 * @return: void
 */
void AstronmicalObject::drawObject()
{
	//enable opengl function to draw line
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);

	glPushMatrix();
	{
		//if there is a parent object, use the parent as the reference center
		if (parent != nullptr && parent->distance > 0)
		{
			glRotatef(parent->angleRevolution, 0, 0, 1);
            glTranslatef(parent->distance, 0.0, 0.0);
		}

		//draw orbit of this object
//		glBegin(GL_LINES);

//		for (int i{ 0 }; i < NUM_ELEMENT; i++)
//		{
//			glVertex2f(distance * cos(2 * PI*i / NUM_ELEMENT), distance*sin(2 * PI*i / NUM_ELEMENT));
//		}

//		glEnd();

		//draw this object

        glRotatef(angleRevolution, 0, 0, 1);
        glTranslatef(distance, 0.0, 0.0);
		glRotatef(angleRotation, 0, 0, 1);

//		glColor3f(color[0], color[1], color[2]);
        gluSphere(mySphere, radius, SLICES, STACKS);
        gluQuadricNormals(mySphere, GL_SMOOTH);
        gluQuadricTexture(mySphere, GL_TRUE);
//		glutSolidSphere(radius, SLICES, STACKS);

	}

	glPopMatrix();
}
/**
 * @name: update
 * @description: update the position of the object
 * @param time: the timespan
 * @return: void
 */
void AstronmicalObject::update(int time)
{
	
	//update the angle of rotation and revolution
    angleRevolution += time * speedRevolution / 3.0;
    angleRotation += time * speedRotation / 3.0;

}


/**
 * @name: Planet
 * @description: Construtor of the Planet class
 * @param label: name of the object
 * @param r: radius
 * @param d: distance to parent
 * @param sRevolute: speed of revolution
 * @param sRotate: speed of rotation
 * @param par: pointer to parent object
 * @param rgbColor: color of the planet
 * @return: void
 */
Planet::Planet(std::string label, GLfloat r, GLfloat m, GLfloat d, GLfloat sRevolute, GLfloat sRotate, AstronmicalObject* par, GLfloat rgbColor[4])
    :AstronmicalObject(label, r, m, d, sRevolute, sRotate, par)
{
	setColor(rgbColor);
}

/**
 * @name: drawPlanet
 * @description: Draw the planet based on the graphic parameters
 * @return: void
 */

/**
 * @brief Planet::~Planet
 */
Planet::~Planet(){}

void Planet::drawPlanet()
{
	// for test
    GLfloat ambient[4]{ 0.5, 0.5, 0.5, 1.0 };
    GLfloat diffuse[4]{ 0.5, 0.5, 0.5, 1.0 };
    GLfloat specular[4]{ 1.0, 1.0, 1.0, 1.0 };
    GLfloat emission[4]{color[0],color[1],color[2],color[3]};

    GLfloat shineness = 90;

    glMaterialfv(GL_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_BACK, GL_SHININESS, shineness);
    glMaterialfv(GL_BACK, GL_EMISSION, emission);
}

/**
 * @name: Star
 * @description: Construtor of the Star class
 * @param label: name of the object
 * @param r: radius
 * @param d: distance to parent
 * @param sRevolute: speed of revolution
 * @param sRotate: speed of rotation
 * @param par: pointer to parent object
 * @param rgbColor: color of the planet
 * @return: void
 */
Star::Star(std::string label, GLfloat r, GLfloat m, GLfloat d, GLfloat sRevolute, GLfloat sRotate, AstronmicalObject* par, GLfloat rgbColor[4])
    :Planet(label, r, m, d, sRevolute, sRotate, par, rgbColor)
{
}

/**
 * @brief Star::~Star
 */
Star::~Star(){}

/**
 * @name: addLightSource
 * @description: add a light source on the star based on the graphic parameters
 * @return: void
 */
void Star::addLightSource()
{
	// for test
    GLfloat position0[] = { 2.0, 0.0, 0.0, 1.0 };
    GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    GLfloat position1[] = { 0.0,2.0, .0, 1.0 };
    GLfloat position2[] = { -2.0, 0.0, .0, 1.0 };
    GLfloat position3[] = { 0.0, -2.0, .0, 1.0 };
    GLfloat position4[] = { 0.0, 3.0, .0, 1.0 };
    GLfloat position5[] = { 0.0, 3.0, .0, 1.0 };
    GLfloat position6[] = { 0.0, 3.0, .0, 1.0 };
    GLfloat position7[] = { 0.0, 3.0, .0, 1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

    glLightfv(GL_LIGHT2, GL_POSITION, position2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT3, GL_POSITION, position3);
    glLightfv(GL_LIGHT3, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
//    glLightfv(GL_LIGHT4, GL_POSITION, position4);
//    glLightfv(GL_LIGHT4, GL_AMBIENT, ambient);
//    glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse);
//    glLightfv(GL_LIGHT4, GL_SPECULAR, specular);

}
