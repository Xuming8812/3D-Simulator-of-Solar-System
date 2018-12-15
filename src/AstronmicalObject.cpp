#include "AstronmicalObject.h"
#include <cmath>
#include <vector>



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
        this->speedRevolution = 360.0f / sRevolute;
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
//AstronmicalObject::~AstronmicalObject(){}


/**
 * @name: drawObject
 * @description: Draw the astronmical object based on the graphic parameters
 * @return: void

 */
void AstronmicalObject::drawObject()
{
	//enable opengl function to draw line

    double PI=3.1415926;
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);

	glPushMatrix();
	{
		//if there is a parent object, use the parent as the reference center
		if (parent != nullptr && parent->distance > 0)
		{
			glRotatef(parent->angleRevolution, 0, 0, 1);

            float dis = parent->distance;
            double angle = static_cast<double>(parent->angleRevolution);
            int num = static_cast<int>(angle/360);
            angle-=num*360;
            angle = angle*PI/180;

            dis = 1.5*dis*dis/sqrt((1.5*dis*sin(angle))*(1.5f*dis*sin(angle))+(dis*cos(angle))*(dis*cos(angle)));

            glTranslatef(dis, 0.0, 0.0);
		}

		//draw orbit of this object
        glBegin(GL_LINES);

        //for planets the orbit is ellipse
        if(parent != nullptr && parent->distance > 0)
        {
            for (int i{ 0 }; i < NUM_ELEMENT; i++)
            {
                glVertex2f(distance * static_cast<float>(cos(2.0 * PI*i / NUM_ELEMENT)), distance*static_cast<float>(sin(2.0 * PI*i / NUM_ELEMENT)));
            }
        }
        else {
            for (int i{ 0 }; i < NUM_ELEMENT; i++)
            {
                glVertex2f(distance *1.5f* static_cast<float>(cos(2.0 * PI*i / NUM_ELEMENT)), distance*static_cast<float>(sin(2.0 * PI*i / NUM_ELEMENT)));
            }
        }

        glEnd();

		//draw this object
        if(parent != nullptr && parent->distance > 0)
        {
            glRotatef(angleRevolution, 0, 0, 1);
            glTranslatef(distance, 0.0, 0.0);
            glRotatef(angleRotation, 0, 0, 1);
        }
        else if(parent == nullptr)
        {
            glRotatef(angleRevolution, 0, 0, 1);
            glTranslatef(distance, 0.0, 0.0);
            glRotatef(angleRotation, 0, 0, 1);
        }
        else {
            glRotatef(angleRevolution, 0, 0, 1);
            float dis = distance;
            double angle = static_cast<double>(angleRevolution);

            int num = static_cast<int>(angle/360);
            angle-=num*360;
            angle = angle*PI/180;

            dis = 1.5*dis*dis/sqrt((1.5*dis*sin(angle))*(1.5*dis*sin(angle))+(dis*cos(angle))*(dis*cos(angle)));
            glTranslatef(dis, 0.0, 0.0);
            glRotatef(angleRotation, 0, 0, 1);
        }

        gluSphere(mySphere, static_cast<double>(radius), SLICES, STACKS);
        gluQuadricNormals(mySphere, GL_SMOOTH);
        gluQuadricTexture(mySphere, GL_TRUE);
	}

	glPopMatrix();
}


