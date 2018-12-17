

# DIVE INTO SOLAR SYSTEM v1.0
## GPU Algorithm Acceleration, Group A


Xingchen Ming   xingchen_ming@brown.edu

Ming Xu     ming_xu1@brown.edu

Geng Yang   geng_yang@brown.edu

------

## CONTENTS

<!-- TOC -->

  - [Introduction](#introduction)
    - [Project Overview](#project-overview)
    - [Goals and Objectives](#goals-and-objectives)
  - [Software Architectural Design (as appropriate)](#software-architectural-design-as-appropriate)
    - [Required External Libraries](#required-external-libraries)
    - [Functional Block Diagrams](#functional-block-diagrams)
    - [Data Flow Diagrams](#data-flow-diagrams)
    - [UML Diagrams showing Object Definition/Inheritance](#uml-diagrams-showing-object-definitioninheritance)
  - [Interface Descriptions (as appropriate)](#interface-descriptions-as-appropriate)
    - [Graphical Interface](#graphical-interface)
    - [Data Visualization](#data-visualization)
    - [Communications Protocols](#communications-protocols)
    - [Threading and Concurrency](#threading-and-concurrency)
    - [Exception Handling](#exception-handling)
  - [Testing and Evaluation](#testing-and-evaluation)
    - [Description of functional testing to date](#description-of-functional-testing-to-date)
    - [Instructions for compiling and running the software](#instructions-for-compiling-and-running-the-software)
  - [Conclusions](#conclusions)
    - [Major Accomplishments](#major-accomplishments)
    - [Results of effort](#results-of-effort)
  - [Future Work](#future-work)
  - [Author Contributions](#author-contributions)

## Introduction
### Project Overview
### Goals and Objectives

## Software Architectural Design (as appropriate)
### Required External Libraries
- Qt 5.10.1
- OpenGL 4.1
- freeglut 3.0.0
### Functional Block Diagrams
### Data Flow Diagrams
### UML Diagrams showing Object Definition/Inheritance

## Interface Descriptions (as appropriate)
### Graphical Interface
The graphical interface consists of two parts. The left one is the widget for displaying solar system, and the right one is for user manipulation.
![image](https://github.com/ENGN2912B-2018/GPU-A/blob/Geng/images/GUI.png)
### Data Visualization
### Communications Protocols
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

## Testing and Evaluation
The operating system and software compiler/library version(s) tested are as follows.
- Operating system: macOS 10.14.1
- Compiler version: clang-1000.10.44.4
- Qt version: 5.11.2
- QMake version: 3.1
- OpenGL version: 4.1
- freeglut version: 3.0.0

### Description of functional testing to date
### Instructions for compiling and running the software
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
- Reasonable and logical class hierarchy design
- An reasonable and concise GUI
- Interaction using mouse
  - Zoom in/out with mouse wheel.
  - Double click to switch the view horizontally and vertically
  - Click on background, adjust view with left button.
  - Click on abstronomical object, drag it along trajectory with left button.
- 3D display of the system.
- Highlight the selected astronomical object with introduction and hide the others.
- Customize date and time to switch to corresponding status
- Customize time speed to fast foward/rewind the simulation
- Customize parameter of selected astronomical object and verify the input.
### Results of effort

Most objectives have been achieved as proposed. There still exists a challenge unresolved, the simulation of changes brought by customized parameters. For example, when the revolution 

## Future Work
The software has provided APIs for customizing parameters of astronomical objects, which aims to simulate the real scene in solar system when when the property of objects changes suddenly.

## Author Contributions

Ming Xu designed class hierarchy and completed computing the status of astronomical objects.

Geng Yang designed the GUI, completed basic interactions and 3D display.

Xingchen Ming was responsible for parameter configuration, exception handling and interaction between user and astronomical objects.