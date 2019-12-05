//#include <iostream>
//#include <glut.h>
//
//GLuint texBufferID;
//GLuint texCoordID, texID;
//GLubyte image[2048][2048][3];
//GLfloat* uvs;
//
//float rotAng;
//float rotVal = 0.05;
//float posx = 0;
//float posy = 0;
//void DrawOldMan();
//void Display(void) {
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glPushMatrix();
//	DrawOldMan();
//	glPopMatrix();
//	glFlush();
//}
//
//
//void DrawOldMan() {
//	Head
//	glPushMatrix();
//	glTranslatef(0, 0.95f, 0);
//	glColor3f(1.0,0.878431372549,0.741176470588);
//	glutSolidSphere(0.5, 25, 25);
//	glPopMatrix();
//
//	Chest
//	glPushMatrix();
//	glColor3f(0.678431372549, 0.309803921569, 0.0274509803922);
//	glutSolidCube(1);
//	glPopMatrix();
//
//	Left Leg	
//	glPushMatrix();
//	glTranslatef(-0.3f, -1, 0);
//	glRotatef(rotAng*1.5f, 1, 0, 0);
//	glColor3f(0, 0, 0);
//	glutSolidCube(0.45f);
//	glTranslatef(0, -0.45f, 0);
//	glutSolidCube(0.45f);
//	glPopMatrix();
//
//	Right Leg
//	glPushMatrix();
//	glTranslatef(0.3f, -1, 0);
//	glRotatef(-rotAng*1.5f, 1, 0, 0);
//	glutSolidCube(0.45f);
//	glTranslatef(0, -0.45f, 0);
//	glutSolidCube(0.45f);
//	glPopMatrix();
//
//	Right Arm
//	glPushMatrix();
//	glColor3f(0.678431372549, 0.309803921569, 0.0274509803922);
//	glRotatef(10, 0, 0, 1);
//	glTranslatef(0.75f, 0.274f, 0);
//	glRotatef(rotAng, 1, 0, 0);
//	glutSolidCube(0.35f);
//	glTranslatef(0,-0.35f,0);
//	glutSolidCube(0.35f);
//	glTranslatef(0, -0.35f, 0);
//	glutSolidCube(0.35f);
//	glPopMatrix();
//
//	Left Arm
//	glPushMatrix();
//	glRotatef(-10, 0, 0, 1);
//	glTranslatef(-0.75f, 0.3f, 0);
//	glRotatef(-rotAng, 1, 0, 0);
//	glutSolidCube(0.35f);
//	glTranslatef(0, -0.35f, 0);
//	glutSolidCube(0.35f);
//	glTranslatef(0, -0.35f, 0);
//	glutSolidCube(0.35f);
//	glPopMatrix();
//
//
//}
//void Anim() {
//	if (rotAng > 20 || rotAng < -20)
//		rotVal *= -1;
//	rotAng += rotVal;
//	glutPostRedisplay();
//}
//
//unsigned char* readBMP(char* filename)
//{
//	int i;
//	FILE* f = fopen(filename, "rb");
//	unsigned char info[54];
//	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header
//
//	 extract image height and width from header
//	int width = *(int*)&info[18];
//	int height = *(int*)&info[22];
//
//	int size = 3 * width * height;
//	unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
//	fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
//	fclose(f);
//
//	for (i = 0; i < size; i += 3)
//	{
//		unsigned char tmp = data[i];
//		data[i] = data[i + 2];
//		data[i + 2] = tmp;
//	}
//
//	return data;
//}
//
//void main(int argc, char** argv) {
//	glutInit(&argc, argv);
//
//	glutInitWindowSize(700, 700);
//	glutInitWindowPosition(150, 150);
//
//	glutCreateWindow("OK Boomer!");
//	glutDisplayFunc(Display);
//	glutIdleFunc(Anim);
//	
//	glEnable(GL_TEXTURE_2D);
//	glGenTextures(1, &texBufferID);
//	glBindTexture(GL_TEXTURE_2D, texBufferID);
//	unsigned char* bitmap_data = readBMP("C:\\Users\\Abdelrahman Ashraf\\Downloads\\test1.bmp");
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2048, 2048, 0, GL_BGR_EXT,
//		GL_UNSIGNED_BYTE, bitmap_data);
//	texCoordID = glGetAttribLocation
//	//////
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
//
//	glEnable(GL_DEPTH_TEST);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(45.0f, 300 / 300, 0.1f, 300.0f);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(0, 2.0f, 5.0f, 0, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
//	glutMainLoop();
//}
