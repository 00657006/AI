#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Rendering.h"

static float  Normal[][4] = { { 0.0, 0.0, -1.0 },{ 0.0, -1.0, 0.0 },{ 1.0, 0.0, 0.0 },
{ 0.0, 0.0, 1.0 },{ 0.0, 1.0, 0.0 },{ -1.0, 0.0, 0.0 } };

static float points[][3] = { { -0.5, -0.5, -0.5 },{ 0.5, -0.5, -0.5 },
{ 0.5, 0.5, -0.5 },{ -0.5, 0.5, -0.5 },
{ -0.5, -0.5, 0.5 },{ 0.5, -0.5, 0.5 },
{ 0.5, 0.5, 0.5 },{ -0.5, 0.5, 0.5 } };

static int face[][4] = { { 0, 3, 2, 1 },{ 0, 1, 5, 4 },{ 1, 2, 6, 5 },
{ 4, 5, 6, 7 },{ 2, 3, 7, 6 },{ 0, 4, 7, 3 } };

static float  flr_diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
static float  flr_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
static float  flr_specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
static float  flr_shininess = 16.0;
static float  lit1_position[] = { 10, 24, 40, 1.0 }; /*point light*/
static float  lit1_diffuse[] = { 0.7, 0.7, 0.4, 1.0 };
static float  lit1_specular[] = { 0.7, 0.7, 0.7, 1.0 };
static float  global_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
static GLUquadricObj* sphere = NULL, * cylinder = NULL, * Circle;
static float ort_ang = 100.0f, per_ang = 45.0f;
static float eye[3] = { 100.0f, 25.0f, 100.0f }, focus[3] = { 75.0f, 0.0f, 75.0f }, V_up[3] = { 0.0f, 1.0f, 0.0f };

unsigned char  checkboard[TSIZE2][TSIZE2][4];   /* checkboard textures **/
unsigned char  tree[TSIZE][TSIZE][4];   /* checkboard textures */
unsigned char  texture[TSIZE][TSIZE][4];   /* checkboard textures */
unsigned char  brick[TSIZE][TSIZE][4];        /* brick wall textures */
unsigned char  circle[TSIZE][TSIZE][4];
unsigned char  waterwave[TSIZE][TSIZE][4];
unsigned char  star[TSIZE][TSIZE][4];
unsigned char  land[TSIZE][TSIZE][4];
unsigned int textName[3];                   /* declare two texture maps*/
unsigned int TextureID[4];

void draw_cube()
{
	int    i;
	for (i = 0; i < 6; i++) {
		glNormal3fv(Normal[i]);
		glBegin(GL_POLYGON);  /* Draw the face */
		glVertex3fv(points[face[i][0]]);
		glVertex3fv(points[face[i][1]]);
		glVertex3fv(points[face[i][2]]);
		glVertex3fv(points[face[i][3]]);
		glEnd();
	}
}

void draw_floor()
{
	glPushMatrix();
	/*glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, textName[0]);
	glMatrixMode(GL_MODELVIEW);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, flr_diffuse);  /*diffuse color */
	/*glMaterialfv(GL_FRONT, GL_AMBIENT, flr_ambient);
	glNormal3f(0.0, 1.0, 0.0);*/
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	//glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	//glTexCoord2f(8, 0);
	glVertex3f(0, 0, 200);
	//glTexCoord2f(8, 8);
	glVertex3f(200, 0, 200);
	//glTexCoord2f(0, 8);
	glVertex3f(200, 0, 0);
	/*glEnd();
	glDisable(GL_TEXTURE_2D);*/
	glPopMatrix();
}

void Init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);  /*Enable depth buffer for shading computing */
	glEnable(GL_NORMALIZE);   /*Enable mornalization  */

	glLightfv(GL_LIGHT2, GL_DIFFUSE, lit1_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lit1_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, lit1_position);  /*fixed position in eye space---*/

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);
	glDisable(GL_LIGHTING);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); /* local viewer */


	sphere = gluNewQuadric();
	cylinder = gluNewQuadric();
	Circle = gluNewQuadric();

	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricNormals(cylinder, GLU_SMOOTH);
	gluQuadricDrawStyle(Circle, GLU_FILL);
	gluQuadricNormals(Circle, GLU_SMOOTH);

	int Width, Height, nrChannels;

	/*unsigned char* data = stbi_load("basket_burned.png", &Width, &Height, &nrChannels, 0);
	glGenTextures(1, &ball);
	glBindTexture(GL_TEXTURE_2D, ball);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);*/

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(3, textName);

	make_check();
	glBindTexture(GL_TEXTURE_2D, textName[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TSIZE2, TSIZE2, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, checkboard);
	
	brick_pattern();
	glBindTexture(GL_TEXTURE_2D, textName[1]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TSIZE, TSIZE, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, brick);

	make_tree();
	glBindTexture(GL_TEXTURE_2D, textName[2]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TSIZE, TSIZE, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, tree);

}

void eye_location(int mode)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	switch (mode)
	{
	case 0:
		gluLookAt(eye[0], eye[1], eye[2], focus[0], focus[1], focus[2], V_up[0], V_up[1], V_up[2]);
		break;
	}
}

void projection(int mode)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glPushMatrix();
	switch (mode)
	{
	case 0:
		if (width > height)
			glOrtho(-1 * ort_ang, ort_ang, -1 * ort_ang * (float)height / (float)width,
				ort_ang * (float)height / (float)width,
				-0.0, 100.0);
		else
			glOrtho(-1 * ort_ang * (float)width / (float)height,
				ort_ang * (float)width / (float)height, -1 * ort_ang, ort_ang,
				-0.0, 100.0);
		break;
	case 1:
		gluPerspective(per_ang, (double)width / (double)height, 1.5, 100.0);
		break;
	}
}

void viewport(int mode)
{
	switch (mode)
	{
	case 0:
		glViewport(0, height / 2, width / 2, height / 2);
		break;
	case 1:
		glViewport(width / 2, height / 2, width / 2, height / 2);
		break;
	case 2:
		glViewport(0, 0, width / 2, height / 2);
		break;
	case 3:
		glViewport(width / 2, 0, width / 2, height / 2);
		break;
	case 4:
		glViewport(0, 0, width, height);
		break;
	}
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	projection(0);
	eye_location(0);
	viewport(4);
	draw_scene();
	
	glutSwapBuffers();
	glFlush();
}
void draw_scene()
{
	draw_floor();
}
void myIdle()
{
}
void keyin(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
		break;
	}
}
void reshape(int w, int h)
{
	width = w, height = h;
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w > h)
		glOrtho(-ort_ang, ort_ang, -ort_ang*(float)h / (float)w, ort_ang * (float)h / (float)w,
			0, 100.0);
	else
		glOrtho(-ort_ang * (float)w / (float)h, ort_ang * (float)w / (float)h, -ort_ang, ort_ang,
			0, 100.0);
	glutPostRedisplay();
}