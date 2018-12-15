#include "SolarSystem.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QString>
#include <QApplication>
#include <thread>

#define TIMEPAST 1

using namespace std;

/**
 * @name: SolarSystem
 * @description: constructor the class SolarSystem
 * @return: void
 */
SolarSystem::SolarSystem()
{
	readParameters();

	for (auto item : parameters)
	{
		if (item.type == STAR)
		{
            AstronmicalObject* current = new Star(item.name, item.radius, item.mass, item.distance, item.speedRevolution, item.speedRotation, nullptr);
			
			objects.push_back(current);
		
		}

		if (item.type == PLANET)
		{
			int index;

			for (index = 0; index < objects.size(); index++)
			{
				if (objects[index]->getName() == item.parentName)
				{
					break;
				}
			}

            AstronmicalObject* current = new Planet(item.name, item.radius, item.mass, item.distance, item.speedRevolution, item.speedRotation, objects[index]);
			objects.push_back(current);
		}
	}

	eyeX = 0;
	eyeY = -700;
	eyeZ = 700;

	centerX = centerY = centerZ = 0;
	upX = upY = 0;
	upZ = 1;
}

/**
 * @name: ~SolarSystem
 * @description: destructor the class SolarSystem
 * @return: void
 */
SolarSystem::~SolarSystem()
{
	for(auto item : objects)
	{
		AstronmicalObject* temp = item;
		delete temp;
	}
}

/**
 * @name: readParameters
 * @description: helper function to read in parameters
 * @return: void
 */
void SolarSystem::readParameters()
{
    ifstream fin;

    QString appPath = QCoreApplication::applicationDirPath();
    int endInd = appPath.indexOf("build");
    string curDir = appPath.toStdString().substr(0,endInd) + "GPU-A/Parameters.txt";
    fin.open(curDir);

	if (!fin)
	{
		return;
	}

	string line;
	//read total number of objects in system
	getline(fin, line);

	objectNum = stoi(line.substr(6));

	for (int i = 0; i < objectNum; i++)
	{
		if (!getline(fin, line))
		{
			break;
		}
		objectInfo current;
		//get name
		getline(fin, line);
		current.name = getStringParameter(line);
		//get type
		getline(fin, line);
		current.type = getTypeParameter(line);
		//get speed of revolution
		getline(fin, line);
		current.speedRevolution = getFloatParameter(line);
		//get speed of revolution
		getline(fin, line);
		current.speedRotation = getFloatParameter(line);
		//get radius
		getline(fin, line);
		current.radius = getFloatParameter(line);
        //get mass
        getline(fin, line);
        current.mass = getFloatParameter(line);
		//get distance
		getline(fin, line);
		current.distance = getFloatParameter(line);
		//get parent name
		getline(fin, line);
		current.parentName = getStringParameter(line);
		//get color
		getline(fin, line);
		
        GLfloat* temp= getArrayParameter(line);
        for (int i = 0; i < 4; i++)
        {
            current.color[i] = temp[i];
        }

		parameters.push_back(current);
	}

	fin.close();
}

/**
 * @name: getStringParameter
 * @description: helper function to read in string parameters
 * @param input: string stored in external file
 * @return: string value
 */
string SolarSystem::getStringParameter(string input)
{
	if (input.empty())
	{
		return "";
	}

	char quote = '\"';

	int start = input.find_first_of(quote);
	int end = input.find_last_of(quote);

	if (start>=end)
	{
		return "";
	}

	string result = input.substr(start + 1, end - start - 1);

	return result;
}

/**
 * @name: getArrayParameter
 * @description: helper function to read in float array parameters
 * @param input: string stored in external file
 * @return: float array value
 */
GLfloat* SolarSystem::getArrayParameter(string input)
{
	if (input.empty())
	{
		return nullptr;
	}

	int start = input.find_first_of('=');

	GLfloat result[4];

	stringstream ss;

	ss << input.substr(start + 2);

	for (int i = 0; i < 4; i++)
	{
		ss>>result[i];
	}

	return result;

}

/**
 * @name: getTypeParameter
 * @description: helper function to read in type of the astronmical object
 * @param input: string stored in external file
 * @return: type of the astronmical object
 */
SolarSystem::OBJECTTYPE SolarSystem::getTypeParameter(string input)
{
	if (input.empty())
	{
		return PLANET;
	}

	int position = input.find_first_of("type = ");

	if (position != 0)
	{
		return PLANET;
	}

	string typeStr = getStringParameter(input);

	if (typeStr == "Star")
	{
		return STAR;
	}
	else if (typeStr == "Planet")
	{
		return PLANET;
	}
	else
	{
		return PLANET;
	}
}

/**
 * @name: getFloatParameter
 * @description: helper function to read in float parameter
 * @param input: string stored in external file
 * @return: float value
 */
GLfloat SolarSystem::getFloatParameter(string input)
{
	if (input.empty())
	{
		return 0.0;
	}

	int start = input.find_first_of('=');

	float temp = stof(input.substr(start + 2));

	return static_cast<GLfloat>(temp);

}


/**
 * @name: keyboard
 * @description: callback function of keyboard input
 * @param key: the key pressed
 * @param x: parameter
 * @param y: parameter
 * @return: void
 */
void SolarSystem::keyboard(unsigned char key, int x, int y)
{

}


/**
 * @name: display
 * @description: show the solar system
 * @return: void
 */
void SolarSystem::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(.7f, .7f, .7f, .1f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0f, 1.0f, 1.0f, 40000000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

    for (auto item : objects)
    {
        item->draw();
    }


	glutSwapBuffers();
}

/**
 * @name: updateObject
 * @description: update the objects in the solar system
 * @return: void
 */
void updateObject(AstronmicalObject* item)
{
    item->update(TIMEPAST);
}

/**
 * @name: update
 * @description: update the solar system
 * @return: void
 */
void SolarSystem::update()
{
    vector<thread> threads;
    for (auto item : objects)
	{
        threads.push_back(thread(updateObject,item));

        //item->update(TIMEPAST);
	}

    for_each(threads.begin(),threads.end(),mem_fn(&thread::join));

	this->display();
}

