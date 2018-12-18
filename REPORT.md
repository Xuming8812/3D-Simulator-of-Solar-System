

# DIVE INTO SOLAR SYSTEM
## ENGN2912B - Scientific Computing in C++
### GPU Algorithm Acceleration, Group A


#### Xingchen Ming   xingchen_ming@brown.edu

#### Ming Xu     ming_xu1@brown.edu

#### Geng Yang   geng_yang@brown.edu

------

## CONTENTS

  - [Introduction](#introduction)
    - [Project Overview](#project-overview)
    - [Goals and Objectives](#goals-and-objectives)
  - [Software Architectural Design](#software-architectural-design)
    - [Required External Libraries](#required-external-libraries)
    - [Functional Block Diagrams](#functional-block-diagrams)
    - [Data Flow Diagrams](#data-flow-diagrams)
    - [UML Diagrams](#uml-diagrams)
  - [Interface Descriptions](#interface-descriptions)
    - [Graphical Interface](#graphical-interface)
    - [Threading and Concurrency](#threading-and-concurrency)
    - [Exception Handling](#exception-handling)
  - [Testing and Evaluation](#testing-and-evaluation)
    - [Functional testing](#Functional-testing)
    - [Instructions for compiling and running](#instructions-for-compiling-and-running)
  - [Conclusions](#conclusions)
    - [Major Accomplishments](#major-accomplishments)
    - [Results of effort](#results-of-effort)
  - [Future Work](#future-work)
  - [Author Contributions](#author-contributions)

## Introduction
### Project Overview
The Solar System model is a 3D simulation of the Solar System and night sky in real-time. All parameters and calculations are based on real data published by NASA. Users can find key information, position and time data for each planets. Our model is a great tool to help children and astronomy enthusiast know deeply to the real Solar System.
### Goals and Objectives
- Adjust view and zoom in/out.
- Adjust time speed to fast forward/rewind.
- Select particular planet and display its characteristics.
- Highlight a selected planet and hide the others.
- Customize parameters(radius, mass, etc.) of selected objects.
- The selected planet can be dragged along its orbit.
- Select particular time to see status of Solar System. 
- Update status using concurrency.
- Exception handling.

## Software Architectural Design
### Required External Libraries
- Qt 5.10.1
- OpenGL 4.1
- freeglut 3.0.0
### Functional Block Diagrams
![image](https://github.com/ENGN2912B-2018/GPU-A/blob/master/figures/Architecture.PNG)
### Data Flow Diagrams
![image](https://github.com/ENGN2912B-2018/GPU-A/blob/master/figures/FlowChart.png)
### UML Diagrams
![image](https://github.com/ENGN2912B-2018/GPU-A/blob/master/figures/UML.png)
## Interface Descriptions
### Graphical Interface
The graphical interface consists of two parts. The left one is the widget for displaying solar system, and the right one is for user manipulation.
![image](https://github.com/ENGN2912B-2018/GPU-A/blob/Geng/images/GUI.png)
### Threading and Concurrency
C++ 11 threads is employed for concurrency. To update the status of each astronomical object simultaneously and quickly, multithreading is needed and each thread is responsible for updating one object. 
```
void RenderingWidget::updatePosition(){
    std::vector<std::thread> threads;
    for (auto it : solarSystem->getObjects())
        threads.push_back(std::thread(&AstronmicalObject::update,it,timeSpeed));
    for_each(threads.begin(),threads.end(),mem_fn(&std::thread::join));
}
``` 
### Exception Handling
- Users are allowed to modidy basic parameters. New parameters should be positive numbers within a range and will be examined in the way of regular expression, or a dialog would show error information and suggest users to re-enter.
![image](https://github.com/ENGN2912B-2018/GPU-A/blob/Geng/images/exception.png)
- All the files that need parsing are added into Qt resource and can be accessed with relative path in code, which helps avoid invalid absolute paths.

## Testing and Evaluation
The operating system and software compiler/library version(s) tested are as follows.
- Operating system: macOS 10.14.1
- Compiler version: clang-1000.10.44.4
- Qt version: 5.11.2
- QMake version: 3.1
- OpenGL version: 4.1
- freeglut version: 3.0.0

### Functional testing
- Functions
  -  Click **Start/Pause** button to start/stop simulation.
  -  Select an object and click **Highlight** button, only selected object and its characteristics shown on screen.
  - Check **Time** box to stop and change date and time, the status of object would change accordingly.
  - Adjust **Time Speed** slider, planets’ revolution and rotation speed would be accelerated or slowed down. Positive  time speed would yield counterclockwise revolution while negative time speed would yield clockwise revolution.
  - Check **Data** box, modify selected object’s parameters and press confirm botton or return, object’s attribute would be modified simultaneously.(Object’s size would change with radius changed etc).  Invalid inputs would yield a warning and wouldn’t be accepted. Reset button help reset object’s attribute.

- Intereactions
    - Perspective changes when scroll mouse wheel or press left button and move mouse.
    - Perspective rotates 90 degrees with double click.
    - Time stops when click one of the objects, and **Data** box shows basic information of the selected object.
    - Object moves counterclockwise or clockwise by dragging it directly, other objects moves correspondingly, and time changes based on objects’ position.




### Instructions for compiling and running
1. Clone the repository
```
$ git clone git@github.com:ENGN2912B-2018/GPU-A.git
```
2. Generate MakeFile and Compile

Note: the ```build/``` directory should be in the same directory with ```GPU-A```
```
$ mkdir build
$ cd build
$ qmake ../GPU-A/SolarSystem.pro
$ make
```
3. Run the executable
```
open SolarSystem.app
```

## Conclusions
### Major Accomplishments

- Reasonable and logical class hierarchy design.
- An reasonable and concise GUI.
- Interaction using mouse.
  - Zoom in/out with mouse wheel.
  - Double click to switch the view horizontally and vertically.
  - Click on background, adjust view with left button.
  - Click on abstronomical object, drag it along orbit with left button.
- 3D display of the system.
- Highlight the selected astronomical object with introduction and hide the others.
- Customize date and time to switch to corresponding status.
- Customize time speed to fast foward/rewind the simulation.
- Customize parameter of selected astronomical object and verify the input.
### Results of effort

Most objectives have been achieved as proposed. There still exists a challenge unresolved, the simulation of changes brought by customized parameters. For example, when the revolution speed of Earth increases greatly, the Earth should run away from Sun with the speed decreasing gradually, and then run towards its original orbit and recover original status.

## Future Work
The software has provided APIs for customizing parameters of astronomical objects, which aims to simulate the real scene in solar system when when the property of objects changes suddenly.

## Author Contributions

Ming Xu designed class hierarchy and completed computing the status of astronomical objects.

Geng Yang designed the GUI, completed basic interactions (e.g. adjust view, set date and timespeed) and 3D display.

Xingchen Ming was responsible for parameter configuration, exception handling and interaction between user and astronomical objects.
