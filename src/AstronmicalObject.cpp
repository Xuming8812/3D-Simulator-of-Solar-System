#pragma once

#include "AstronmicalObject.h"
#include <cmath>
#include <vector>

#define PI 3.1415926

#define SLICES 50
#define STACKS 50

#define NUM_ELEMENT 1000

AstronmicalObject::AstronmicalObject(std::string label, GLfloat r, GLfloat d,
	GLfloat sRevolute, GLfloat sRotate, AstronmicalObject* par)
{
	this->name = label;
	this->radius = r;
	this->distance = d;

	this->speedRotation = sRotate;

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
		glBegin(GL_LINES);

		for (int i{ 0 }; i < NUM_ELEMENT; i++)
		{
			glVertex2f(distance * cos(2 * PI*i / NUM_ELEMENT), distance*sin(2 * PI*i / NUM_ELEMENT));
		}

		glEnd();

		//draw this object
		glRotatef(angleRevolution, 0, 0, 1);
		glTranslatef(distance, 0.0, 0.0);

		glRotatef(angleRotation, 0, 0, 1);

		glColor3f(color[0], color[1], color[2]);

		glutSolidSphere(radius, SLICES, STACKS);
	}

	glPopMatrix();
}

void AstronmicalObject::update(int time)
{

	//update the angle of rotation and revolution
	angleRevolution += time * speedRevolution;
	angleRotation += time * speedRotation;

}


Planet::Planet(std::string label, GLfloat r, GLfloat d, GLfloat sRevolute, GLfloat sRotate, AstronmicalObject* par, GLfloat rgbColor[4])
	:AstronmicalObject(label, r, d, sRevolute, sRotate, par)
{
	setColor(rgbColor);
}

void Planet::drawPlanet()
{
	// for test
	GLfloat ambient[4]{ 0.0, 0.0, 0.5, 1.0 };
	GLfloat diffuse[4]{ 0.0, 0.0, 0.5, 1.0 };
	GLfloat specular[4]{ 0.0, 0.0, 1.0, 1.0 };
	//GLfloat emission[4];

	GLfloat emission[4]{ color[0],color[1],color[2],color[3] };



	GLfloat shineness = 90.0;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMaterialf(GL_FRONT, GL_SHININESS, shineness);
}

Star::Star(std::string label, GLfloat r, GLfloat d, GLfloat sRevolute, GLfloat sRotate, AstronmicalObject* par, GLfloat rgbColor[4])
	:Planet(label, r, d, sRevolute, sRotate, par, rgbColor)
{
}

void Star::addLightSource()
{
	// for test
	GLfloat position[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}