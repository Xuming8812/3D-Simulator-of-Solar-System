#pragma once


#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


#include<string>
#include<vector>

//class declaration of AstronmicalObject, which is the base class
class AstronmicalObject
{
public:
	//constructor

    AstronmicalObject(std::string label, GLfloat r, GLfloat m, GLfloat d, GLfloat sRevolute, GLfloat sRotate,  AstronmicalObject* par);

	//destructor
    ~AstronmicalObject();



	//access data member function for name of the astronmical object
	std::string getName() const
	{
		return name;
	}
	//access data member function for radius of the astronmical object
	GLfloat getRadius() const
	{
		return radius;
	}

    //access data member function for mass of the astronmical object
    GLfloat getMass() const
    {
        return mass;
    }

	//access data member function for rotation speed of the astronmical object
	GLfloat getSpeedRotation() const
	{
		return speedRotation;
	}
	//access data member function for revolution speed of the astronmical object
	GLfloat getSpeedRevolution() const
	{
		return speedRevolution;
	}
	//access data member function for distance of the astronmical object to its parent object
	GLfloat getDistance() const
	{
		return distance;
	}

    //access data member function for angleRevolution of the astronmical object to its parent object
    GLfloat getAngleRevolution() const
    {
        return angleRevolution;
    }


	//access data member function for color of the astronmical object
	GLfloat* getColor() const
	{
		GLfloat result[4];

		for (int i{ 0 }; i < 4; i++)
		{
			result[i] = color[i];
		}

		return result;
	}
	//access data member function for name of the astronmical object
	void setName(const std::string input)
	{
		if (!input.empty())
		{
			name = input;
		}
	}
	//access data member function for radius of the astronmical object
	void setRadius(GLfloat input)
	{
		if (input > 0)
		{
			radius = input;
		}
	}


    //access data member function for mass of the astronmical object
    void setMass(GLfloat input)
    {
        if (input > 0)
        {
            mass = input;
        }
    }


	//access data member function for distance of the astronmical object to its parent object
	void setDistance(GLfloat input)
	{
		// the distance shouldn`t be too small
		if (input > this->radius)
		{
			distance = input;
		}
	}
	//access data member function for color of the astronmical object
	void setColor(GLfloat input[4])
	{		
		for (int i{0};i<4;i++)
		{
			color[i] = input[i];
		}
	}
	
	//draw the object base on the radius and color
	void drawObject();
	
	//virtual function for draw the object
	//all subclasses need to override for polymorphism
	virtual void draw()
	{
		drawObject();
	}

	//virtual function for update the image
	//all subclasses need to override for polymorphism
	virtual void update(int time);

	//color of the object
	GLfloat color[4];


    bool visiblity(){
        return isVisible;
    }

    void setVisibility(bool v){
        isVisible = v;
    }
	
private:

    GLUquadricObj *mySphere;


	//name of the object, used in data visualization
	std::string name;

	//radius of the object
	GLfloat radius;


    //mass of the object
    GLfloat mass;


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


    // whether to display the body or not
    bool isVisible;


};

// class for planets and satellites
class Planet : public AstronmicalObject
{
public:

    Planet(std::string label, GLfloat r, GLfloat m, GLfloat d, GLfloat sRotate, GLfloat sRevolute, AstronmicalObject* par, GLfloat rgbColor[4]);
    ~Planet();


	//helper function to draw a planet
	void drawPlanet();

	//overload of draw function of the base class
	virtual void draw()
	{
		drawPlanet();
		drawObject();
	}
	//access data member function for ambient parameters
	void setMaterialAmbient(GLfloat input[4])
	{
		for (int i{ 0 }; i < 4; i++)
		{
			materialAmbient[i] = input[i];
		}
	}
	//access data member function for diffuse parameters
	void setMaterialDiffuse(GLfloat input[4])
	{
		for (int i{ 0 }; i < 4; i++)
		{
			materialDiffuse[i] = input[i];
		}
	}
	//access data member function for specular parameters
	void setMaterialEmission(GLfloat input[4])
	{
		for (int i{ 0 }; i < 4; i++)
		{
			materialEmission[i] = input[i];
		}
	}
	//access data member function for emission parameters
	void setMaterialSpecular(GLfloat input[4])
	{
		for (int i{ 0 }; i < 4; i++)
		{
			materialSpecular[i] = input[i];
		}
	}
	//access data member function for shineness parameters
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

    Star(std::string label, GLfloat r, GLfloat m, GLfloat d, GLfloat sRotate, GLfloat sRevolute, AstronmicalObject* par, GLfloat rgbColor[4]);
    ~Star();


	//helper function to add a light source to the star
	void addLightSource();

	//overload of draw function of the base class
	virtual void draw()
	{

        addLightSource();

		drawPlanet();
		drawObject();	
	}

	//access data member function for light source position
	void setLightPosition(GLfloat input[4])
	{
		for (int i{ 0 }; i < 4; i++)
		{
			lightPosition[i] = input[i];
		}
	}

	//access data member function for light source ambient
	void setLightAmbient(GLfloat input[4])
	{
		for (int i{ 0 }; i < 4; i++)
		{
			lightAmbient[i] = input[i];
		}
	}

	//access data member function for light source diffuse
	void setLightDiffuse(GLfloat input[4])
	{
		for (int i{ 0 }; i < 4; i++)
		{
			lightDiffuse[i] = input[i];
		}
	}
	//access data member function for light source specular
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
