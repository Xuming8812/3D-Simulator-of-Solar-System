# GPU-A
This is the repository for final project of group GPU-A.

## Design Philosophy
Our work is to develop a cross-platform 3D solar system model which simulates how the solar system operates, such as the trajectory of the planets. The work will employ Qt to implement GUI, C++ AMP for GPU acceleration, and multithreading computation will also be used to increase calculation speed. The
main objectives of the implementation are as follows. 

* Zoom in/out with mouse scrolling or sliding bar.
* Adjust time speed (i.e. fast forward/rewind) with sliding bar.
* Show motion data of a selected planet.
* Highlight a selected planet and hide the others.
* Enable customized parameters of a selected planet to simulate what will happen to the solar system.
* Drag a selected planet smoothly along the trajectory and updates the status of the others simultaneously.
* Click on a selected astronomical object to see the detailed information and a realistic image.


## Build Instruction
1. Clone the repository
```
git clone git@github.com:ENGN2912B-2018/GPU-A.git
```
2. Load module qt/5.10.1 and freeglut/3.0.0 on CCV
```
moudle load qt/5.10.1
```
```
freeglut/3.0.0
```
3. Generate MakeFile and Compile
```
mkdir build
cd build
qmake ../SolarSystem.pro
make
```
4. Run the executable
```
SolarSystem
```

## Usage Documentation
1. Click on **Start** button to start the simulation.
2. Select any celestial body and click on **Motion Data** to check the motion inforamtion of it.
3. Click on **Parameter** button to set the parameter of a selected celestial body and see what will happen.
4. Click on **Highlight** to highlight the trajectory of the selected celestial body and hide the others'.
5. Adjust time to see the status of different time.
6. Use the slider or **+/-** buttons to zoom in/out.
