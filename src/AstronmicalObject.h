#pragma once

#include<GL/glut.h>
#include<string>
#include<vector>

//class declaration of AstronmicalObject,which is the base class
class AstronmicalObject
{
public:
	//constructor
	AstronmicalObject(std::string label, GLfloat r, GLfloat d, GLfloat sRevolute, GLfloat sRotate, AstronmicalObject* par);

	//destructor
	//~AstronmicalObject();


	//access data member function
	std::string getName() const
	{
		return name;
	}

	GLfloat getRadius() const
	{
		return radius;
	}

	GLfloat getSpeedRotation() const
	{
		return speedRotation;
	}

	GLfloat getSpeedRevolution() const
	{
		return speedRevolution;
	}

	GLfloat getDistance() const
	{
		return distance;
	}

	GLfloat* getColor() const
	{
		GLfloat result[4];

		for (int i{ 0 }; i < 4; i++)
		{
			result[i] = color[i];
		}

		return result;
	}

	void setName(const std::string input)
	{
		if (!input.empty())
		{
			name = input;
		}
	}

	void setRadius(GLfloat input)
	{
		if (input > 0)
		{
			radius = input;
		}
	}

	void setDistance(GLfloat input)
	{
		// the distance shouldn`t be too small
		if (input > this->radius)
		{
			distance = input;
		}
	}

	void setColor(GLfloat input[4])
	{


		for (int i{ 0 }; i < 4; i++)
		{
			color[i] = input[i];
		}
	}


	//draw the object base on the radius and color
	void drawObject();

	//virtual function for subclasses to override for polymorphism
	virtual void draw()
	{
		drawObject();
	}

	virtual void update(int time);

	GLfloat color[4];

private:
	//name of the object, used in data visualization
	std::string name;

	//radius of the object
	GLfloat radius;

	//rotation speed and revolution speed
	GLfloat speedRotation, speedRevolution;

	//current rotation angle and revolution angle
	GLfloat angleRotation, angleRevolution;

	//the object which this object is orbiting
	AstronmicalObject* parent;

	//the color vector for this object


	//TODO: use texture of image instead of the single color to respresent the object

	//in demo, the orbit will be regarded as a circle
	GLfloat distance;

	//TODO:  declare a class/structure to store the real orbit function
	//OrbitData orbit();


};

// class for planets and satellites
class Planet : public AstronmicalObject
{
public:
	Planet(std::string label, GLfloat r, GLfloat d, GLfloat sRotate, GLfloat sRevolute, AstronmicalObject* par, GLfloat rgbColor[4]);
	//~Planet();

	void setAmbient();
	void setDiffuse();
	void setSpecular();
	void setEmission();
	void setShineness();

	void drawPlanet();

	virtual void draw()
	{
		drawPlanet();
		drawObject();
	}

	void setMaterialAmbient(GLfloat input[4])
	{
		for (int i{ 0 }; i < 4; i++)
		{
			materialAmbient[i] = input[i];
		}
	}

	void setMaterialDiffuse(GLfloat input[4])
	{
		for (int i{ 0 }; i < 4; i++)
		{
			materialDiffuse[i] = input[i];
		}
	}

	void setMaterialEmission(GLfloat input[4])
	{
		for (int i{ 0 }; i < 4; i++)
		{
			materialEmission[i] = input[i];
		}
	}

	void setMaterialSpecular(GLfloat input[4])
	{
		for (int i{ 0 }; i < 4; i++)
		{
			materialSpecular[i] = input[i];
		}
	}

	void setMaterialShineness(GLfloat input)
	{

		materialShineness = input;

	}

private:
	GLfloat materialAmbient[4];
	GLfloat materialDiffuse[4];
	GLfloat materialSpecular[4];
	GLfloat materialEmission[4];
	GLfloat materialShineness;
};



// class for star, in this system, the sun
class Star : public Planet
{
public:
	Star(std::string label, GLfloat r, GLfloat d, GLfloat sRotate, GLfloat sRevolute, AstronmicalObject* par, GLfloat rgbColor[4]);
	//~Star();

	void addLightSource();

	virtual void draw()
	{
		addLightSource();
		drawPlanet();
		drawObject();
	}

	void setLightPosition(GLfloat input[4])
	{
		for (int i{ 0 }; i < 4; i++)
		{
			lightPosition[i] = input[i];
		}
	}

	void setLightAmbient(GLfloat input[4])
	{
		for (int i{ 0 }; i < 4; i++)
		{
			lightAmbient[i] = input[i];
		}
	}

	void setLightDiffuse(GLfloat input[4])
	{
		for (int i{ 0 }; i < 4; i++)
		{
			lightDiffuse[i] = input[i];
		}
	}

	void setLightSpecular(GLfloat input[4])
	{
		for (int i{ 0 }; i < 4; i++)
		{
			lightSpecular[i] = input[i];
		}
	}

private:
	GLfloat  lightPosition[4];
	GLfloat  lightAmbient[4];
	GLfloat  lightDiffuse[4];
	GLfloat  lightSpecular[4];
};