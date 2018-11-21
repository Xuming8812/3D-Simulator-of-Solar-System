#include <GL/glut.h>
#include "SolarSystem.h"

//window size and location
#define WINDOW_X_POS 50
#define WINDOW_Y_POS 50
#define WIDTH 1500
#define HEIGHT 1000

SolarSystem solarSystem;
/**
 * @name: display
 * @description: package of display function for glut to call
 * @return: void
 */
void display(void) {
	solarSystem.display();
}

/**
 * @name: update
 * @description: package of update function for glut to call
 * @return: void
 */
void update(void) {
	solarSystem.update();
}

/**
 * @name: interactive
 * @description: package of keyboard function for glut to call
 * @param key: the key pressed
 * @param x: parameter
 * @param y: parameter
 * @return: void
 */
void interactive(unsigned char key, int x, int y) {
	solarSystem.keyboard(key, x, y);
}

/**
 * @name: main
 * @description: main function to test the class SolarSystem and AstronmicalObject
 * @return: error code
 */
int main(int argc, char*  argv[]) {

    //glutInit(&argc, argv);

	//set display mode as double buffer
    glutInitDisplayMode(GLUT_RGBA |  GLUT_DOUBLE);

	//set window position and size
    glutInitWindowPosition(WINDOW_X_POS, WINDOW_Y_POS);
	glutInitWindowSize(WIDTH, HEIGHT);

	//create window with the title
    glutCreateWindow("SolarSystem");

	//call back function for display, update, and keyboard input
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutKeyboardFunc(interactive);

	//keep running the program
    glutMainLoop();
    return 0;
}