#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include <math.h>
#include <vector>
#include <sstream>

int maxScore = 2;
int WIDTH = 1280;
int HEIGHT = 720;
float rotAng;
int rotAngSky;
float posx = 8;
float curposx = 8;
float speedfac = 1;
GLuint tex;
char title[] = "3D Model Loader Sample";
bool fps;
int score;
float houseZ = 90;
bool win, lose;
// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 1000;
void objectsMove(void);
void initObjects();
class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};

Vector Eyet(12, 10, -20);
Vector Eyef(12, 6, 1);
Vector AtF(12, 6, 50);
Vector At(12, 6, 0);
Vector Up(0, 1, 0);
std::vector<Vector> objects;
std::vector<bool> objectsType; //true = phone

void reset() {
	posx = 8;
	curposx = 8;
	speedfac = 1;
	score = 0;
	houseZ = 90;
	win = false;
	lose = false;
	objects.clear();
	objectsType.clear();
	initObjects();
}


int cameraZoom = 0;

// Model Variables
Model_3DS model_phone;
Model_3DS model_man;
Model_3DS model_laptop;
Model_3DS model_house;

// Textures
GLTexture tex_road;
GLTexture tex_ground;

//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//


	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}

//=======================================================================
// Render Ground Function
//=======================================================================
void RenderRoad()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_road.texture[0]);	// Bind the ground texture
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(0,0.25, -20);
	glTexCoord2f(5, 0);
	glVertex3f(20, 0.25, -20);
	glTexCoord2f(5, 5);
	glVertex3f(20, 0.25, 100);
	glTexCoord2f(0, 5);
	glVertex3f(0, 0.25,100);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

void RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(20, 0.25, -20);
	glTexCoord2f(5, 0);
	glVertex3f(60, 0.25, -20);
	glTexCoord2f(5, 5);
	glVertex3f(60, 0.25, 100);
	glTexCoord2f(0, 5);
	glVertex3f(20, 0.25, 100);
	////
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);
	glVertex3f(-40, 0.25, -20);
	glTexCoord2f(5, 0);
	glVertex3f(0, 0.25, -20);
	glTexCoord2f(5, 5);
	glVertex3f(0, 0.25, 100);
	glTexCoord2f(0, 5);
	glVertex3f(-40, 0.25, 100);
	////
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}
//=======================================================================
// Display Function
//=======================================================================
int rotinc = 1;

void renderHouse() {
	glPushMatrix();
	glTranslatef(13, -2, houseZ);
	glRotatef(270, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glScalef(4, 4, 4);
	model_house.Draw();
	glPopMatrix();
	if(!win &&!lose)
	houseZ -= 0.1;
	if (houseZ <= 5.2) {
		win = true;
	}
}
void output(int x, int y,int z, float r, float g, float b, void* font, char *string)
{
	glColor3f(r, g, b);
	glRasterPos3f(x, y,z);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter((void*)font, string[i]);
		
	}
}
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	if (fps) {
		gluLookAt(curposx, Eyef.y, Eyef.z, AtF.x, AtF.y, AtF.z, Up.x, Up.y, Up.z);
	}
	else {
		gluLookAt(Eyet.x, Eyet.y, Eyet.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	}
	if (!win && !lose) {
		objectsMove();
		if (rotAng >=15 || rotAng <= -15) {
			rotinc *= -1;
		}
		rotAng += rotinc*speedfac*0.5;
		if (posx >= curposx) {
			if (posx - curposx < 0.1*speedfac) {
				curposx = posx;
			}
			else
				curposx += 0.1 *speedfac;
		}
		else {
			if (curposx -posx< 0.1* speedfac) {
				curposx = posx;
			}
			else
			curposx -= 0.1 * speedfac;
		}
	}
	else if(win) {
		glPushMatrix();
		std::ostringstream oss;
		oss << "Ok, Boomer! You WON!";
		std::string var = oss.str();
		output(10, 10, -10, 1, 1, 1, GLUT_BITMAP_TIMES_ROMAN_24, (char*)var.c_str());
		glPopMatrix();
	}
	else {
		glPushMatrix();
		std::ostringstream oss;
		oss << "You LOST!, press R to retry";
		std::string var = oss.str();
		output(10, 10, -10, 1, 0, 0, GLUT_BITMAP_TIMES_ROMAN_24, (char*)var.c_str());
		glPopMatrix();
	}
	

	if (score >= maxScore) {
		renderHouse();
	}
	rotAngSky += 1;

	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	// Draw Ground
	RenderRoad();
	RenderGround();
	// Draw Man Model
	glPushMatrix();
	glTranslatef(curposx, 0, 0);
	glScalef(0.07, 0.07, 0.07); 
	if (!win && !lose) {
		model_man.Objects[3].rot.y = rotAng;
		model_man.Objects[2].rot.y = rotAng;
		model_man.Objects[3].pos.y += rotinc / 10.0;
		model_man.Objects[2].pos.y += rotinc / 10.0;
		model_man.Objects[0].pos.y += rotinc / 10.0;
		model_man.Objects[1].pos.y += rotinc / 10.0;
		model_man.Objects[0].pos.z = 0.5f;
		for (int i = 4; i <= 8; i++) {
			model_man.Objects[i].rot.y = -rotAng;
		}
	}
	model_man.Draw();
	glPopMatrix();

	
	//sky box
	glPushMatrix();

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(rotAngSky/50.0, 0, 1, 0);
	glRotated(90, 1, 1, 0);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 100, 100, 100);
	gluDeleteQuadric(qobj);


	glPopMatrix();



	glutSwapBuffers();
}
bool detectCol(float player, float object) {
	if ((object == 8 && player <= 11) || (object == 14 && player >= 11)) {
		return true;
	}
	return false;
}

void objectsMove(void) {

	for (int i = 0; i < objects.size(); i++)
	{
		Vector obj = objects[i];
		if (obj.z <= 0 && obj.z >-0.5*speedfac && detectCol(curposx, obj.x)) {
			lose = true;
		}
		if (obj.z <= -10) {
			score += 1;
			objects.erase(objects.begin() + i);
			objectsType.erase(objectsType.begin() + i);
			if (score <= maxScore) {
				Vector v(8, 5, 105);
				double r = ((double)rand() / (RAND_MAX));
				v.x = r > 0.5 ? 8 : 14;
				objects.push_back(v);
				r = ((double)rand() / (RAND_MAX));
				objectsType.push_back(r > 0.5);
			}

		}

		else {
			obj.z -= 0.1*speedfac;
			speedfac += speedfac >10 ? 0: 0.001;
			objects[i] = obj;
			if (objectsType[i]) {

				// Draw phone Model
				glPushMatrix();
				glTranslatef(obj.x, obj.y, obj.z);
				glScalef(10, 10, 10);
				glRotatef(90.f, 1, 0, 0);
				model_phone.Draw();
				glPopMatrix();
			}
			else {
				// Draw laptop Model
				glPushMatrix();
				glTranslatef(obj.x, obj.y, obj.z);
				glScalef(0.01, 0.01, -0.01);
				model_laptop.Draw();
				glPopMatrix();
			}
		}
	}
	
}

void initObjects() {
	Vector v4(8, 5, 85);
	objects.push_back(v4);
	objectsType.push_back(false);
	Vector v3(8, 5, 105);
	objects.push_back(v3);
	objectsType.push_back(false);
	Vector v(8, 5, 65);
	objects.push_back(v);
	objectsType.push_back(true);
	Vector v1(14, 5, 45);
	objects.push_back(v1);
	objectsType.push_back(true);
	Vector v2(8, 5, 25);
	objects.push_back(v2);
	objectsType.push_back(false);

}
//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char button, int x, int y)
{
	switch (button)
	{
	/*case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'r':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;*/
	case 'r':
		reset();
		break;
	case 'd':
		posx = 8;
		break;
	case 'a':
		posx = 15;
		break;
	case 'v':
		fps = !fps;
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

//=======================================================================
// Motion Function
//=======================================================================
//void myMotion(int x, int y)
//{
//	y = HEIGHT - y;
//
//	if (cameraZoom - y > 0)
//	{
//		Eye.x += -0.1;
//		Eye.z += -0.1;
//	}
//	else
//	{
//		Eye.x += 0.1;
//		Eye.z += 0.1;
//	}
//
//	cameraZoom = y;
//
//	glLoadIdentity();	//Clear Model_View Matrix
//
//	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters
//
//	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//
//	glutPostRedisplay();	//Re-draw scene 
//}

//=======================================================================
// Mouse Function
//=======================================================================
//void myMouse(int button, int state, int x, int y)
//{
//	y = HEIGHT - y;
//
//	if (state == GLUT_DOWN)
//	{
//		cameraZoom = y;
//	}
//}

//=======================================================================
// Reshape Function
//=======================================================================
//void myReshape(int w, int h)
//{
//	if (h == 0) {
//		h = 1;
//	}
//
//	WIDTH = w;
//	HEIGHT = h;
//
//	// set the drawable region of the window
//	glViewport(0, 0, w, h);
//
//	// set up the projection matrix 
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);
//
//	// go back to modelview matrix so we can move the objects about
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
//}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files
	model_phone.Load("Models/phone/nokiacityman.3DS");
	model_man.Load("models/man/tes.3DS");
	model_laptop.Load("models/laptop/laptop.3DS");
	model_house.Load("models/house/house.3DS");
	// Loading texture files
	tex_road.Load("Textures/road.bmp");
	tex_ground.Load("Textures/ground.bmp");

	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	initObjects();
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);

	//glutMotionFunc(myMotion);

	//glutMouseFunc(myMouse);

	//glutReshapeFunc(myReshape);

	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}