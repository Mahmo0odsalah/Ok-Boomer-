#include <string>
#include <glut.h>
#include <stdio.h>
#include <math.h>
using namespace std;


void DrawMainCharacter();
void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawMainCharacter();
	glFlush();
}

void DrawMainCharacter() {
	glPushMatrix();
	glutSolidSphere(0.5f, 25, 25);

	glPopMatrix();
}

void main(int argc, char** argv) {
	
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(150, 150);

	glutCreateWindow("Bawency Bol");
	glutDisplayFunc(Display);
	//glutIdleFunc(Anim);
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glutIdleFunc(Display);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f ,600/600, 0.1f, 300.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0.0f, 2.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glutMainLoop();
}

float clamp(float n,float lower, float upper) {
	if (n > upper)
		return upper;
	if (n < lower)
		return lower;
	return n;
}

