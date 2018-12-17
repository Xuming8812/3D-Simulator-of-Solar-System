# GPU-A v1.0
This is the repository for final project of group GPU-A. The best environment to run is MACOS.

## Design Philosophy
Our work is to develop a cross-platform 3D solar system model which simulates how the solar system operates, such as the trajectory of the planets. The work will employ Qt to implement GUI, C++ AMP for GPU acceleration, and multithreading computation will also be used to increase calculation speed. The
main objectives of the implementation are as follows. 

* Zoom in/out with mouse scrolling.
* Adjust time speed (i.e. fast forward/rewind) with sliding bar.
* Show motion data of a selected planet.
* Highlight a selected planet and hide the others.
* Enable customized parameters of a selected planet.
* Drag a selected planet smoothly along the trajectory and updates the status of the others simultaneously.
* Click on a selected astronomical object to see the detailed information.


## Build Instruction

1. Clone the repository
```
git clone git@github.com:ENGN2912B-2018/GPU-A.git
```
2. To compile on CCV, load module qt/5.10.1 and freeglut/3.0.0, else please skip this step
```
moudle load qt/5.10.1
moudle freeglut/3.0.0
```
3. Generate MakeFile and Compile

Note: the ```build``` should be in the same directory with ```GPU-A```
```
mkdir build
cd build
qmake ../GPU-A/SolarSystem.pro
make
```
4. Run the executable
```
open SolarSystem.app
```

## Usage Documentation
1. Click on **Start/Pause** button to start or pause the simulation.
2. Select any object and click on **Highlight** to highlight the object with wiki and hide the others.
3. Check **Time** box and change time to see the status of corresponding time.
4. Change time speed to adjust simulation speed.
5. Check **Data** box and change basic parameters of selected object to see corresponding effects.
6. Click on background, press left button and move mouse to adjust view.
7. Click on object, press left button and move mouse to drag the object along trajectory.
7. Double click on background to reset the view quickly.
8. Scorll mouse wheel to zoom in/out.

