//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
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
static float  lit1_position[] = { 100, 20, 100, 1.0 }; /*point light*/
static float  lit1_diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
static float  lit1_specular[] = { 0.7, 0.7, 0.7, 1.0 };
static float  global_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
static GLUquadricObj* sphere = NULL, * cylinder = NULL, * Circle;
static float ort_ang = 150.0f, per_ang = 45.0f;
static float eye[3] = { 100.0f, 25.0f, 100.0f }, focus[3] = { 100.0f, 0.0f, 100.0f }, V_up[3] = { 0.0f, 0.0f, -1.0f };
static float fresh_ball_diffuse[4] = { 0.4f, 0.6f, 0.05f, 1.0f };//light green
static float fresh_ball_ambient[4] = { 0.01f, 0.4f, 0.01f,1.0f };
static float fresh_ball_specular[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
static float fresh_ball_shiness = 64.0f;
static float red_ball_diffuse[4] = { 0.5f, 0.01f, 0.01f, 1.0f };
static float red_ball_ambient[4] = { 0.4f, 0.01f, 0.01f,1.0f };
static float red_ball_specular[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
static float red_ball_shiness = 64.0f;
static float blue_ball_diffuse[4] = { 0.1f, 0.15f, 0.6f, 1.0f };
static float blue_ball_ambient[4] = { 0.01f, 0.01f, 0.4f,1.0f };
static float blue_ball_specular[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
static float blue_ball_shiness = 64.0f;
static float green_ball_diffuse[4] = { 0.1f, 0.6f, 0.05f, 1.0f };
static float green_ball_ambient[4] = { 0.01f, 0.4f, 0.01f,1.0f };
static float green_ball_specular[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
static float green_ball_shiness = 64.0f;
static float pink_ball_diffuse[4] = { 0.6f, 0.4f, 0.1f, 1.0f };
static float pink_ball_ambient[4] = { 0.4f, 0.01f, 0.01f,1.0f };
static float pink_ball_specular[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
static float pink_ball_shiness = 64.0f;
static float skyblue_ball_diffuse[4] = { 0.1f, 0.4f, 0.6f, 1.0f };//light blue
static float skyblue_ball_ambient[4] = { 0.01f, 0.01f, 0.4f,1.0f };
static float skyblue_ball_specular[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
static float skyblue_ball_shiness = 64.0f;
static float metal2_ambient[] = { 0.247250, 0.224500, 0.064500, 1.000000 };/*Gold*/
static float metal2_diffuse[] = { 0.346150, 0.314300, 0.090300, 1.000000 };
static float metal2_specular[] = { 0.797357, 0.723991, 0.208006, 1.000000 };
static float metal2_shininess = 40.199997;
static float mat1_ambient[] = { 0.174500, 0.011750, 0.011750, 1 };/*紅寶石*/
static float mat1_diffuse[] = { 0.614240, 0.041360, 0.041360, 1 };
static float mat1_specular[] = { 0.727811, 0.626959, 0.626959, 1 };
static float mat1_emission[] = { 0.4, 0.4, 0.8, 1.0 };
static float mat1_shininess = 5;

unsigned char  checkboard[TSIZE2][TSIZE2][4];   /* checkboard textures **/
unsigned char  tree[TSIZE][TSIZE][4];   /* tree textures */
unsigned char  texture[TSIZE][TSIZE][4];   /*  textures */
unsigned char  brick[TSIZE][TSIZE][4];        /* brick wall textures */
unsigned char  circle[TSIZE][TSIZE][4];
unsigned char  waterwave[TSIZE][TSIZE][4];
unsigned char  star[TSIZE][TSIZE][4];
unsigned char  land[TSIZE][TSIZE][4];
unsigned int textName[3];                   /* declare two texture maps*/
unsigned int TextureID[4];
ball Ball[12];
int NumofBalls = 12;

void InitSpeed(ball* object, float x, float y, float z)
{
	object->speed[0] = x;
	object->speed[1] = y;
	object->speed[2] = z;
}
void Location(ball* object, float x, float y, float z)
{
	object->xyz[0] = x;
	object->xyz[1] = y;
	object->xyz[2] = z;
}
void SetUpObject()
{
	for (int i = 0; i < NumofBalls; i++)
	{
		if (i < 2)		// 0 、 1 are predators
		{
			Ball[i].role = 0;
			Ball[i].R = 2.0f;
			if (i == 0)
			{
				Location(&Ball[i], 2.0f, 2.0f, 198.0f);
				InitSpeed(&Ball[i], 0.0f, 0.0f, -1.0f);
				Ball[i].Area = 0;
				Ball[i].right=true;
				Ball[i].BottleNeck = 0;
			}	
			else
			{
				Location(&Ball[i], 198.0f, 2.0f, 2.0f);
				InitSpeed(&Ball[i], 0.0f, 0.0f, 1.0f);
				Ball[i].Area = 1;
				Ball[i].right = true;
				Ball[i].BottleNeck = 0;
			}
		}
		else if (i < 4) // 2、3 are hovers
		{
			Ball[i].role = 1; 
			Ball[i].R = 2.0f;
			if (i == 2)
			{
				Location(&Ball[i], 100.0f, 2.0f, 42.0f);
				InitSpeed(&Ball[i], 0.0f, 0.0f, 1.0f);
			}
			else
			{
				Location(&Ball[i], 100.0f, 2.0f, 100.0f);
				InitSpeed(&Ball[i], 1.0f, 0.0f, 0.0f);
			}
				
		}
		else            // 4~ 11 are food
		{
			Ball[i].role = 2;
			Ball[i].R = 1.0f;
			if (i == 4)
				Location(&Ball[i], 100.0f, 1.0f, 100.0f);
		}			
	}
}
void draw_cube()
{
	int    i;
	glMaterialfv(GL_FRONT, GL_AMBIENT, metal2_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, metal2_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, metal2_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, metal2_shininess);
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
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, textName[0]);
	glMatrixMode(GL_MODELVIEW);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, flr_diffuse);  /*diffuse color */
	glMaterialfv(GL_FRONT, GL_AMBIENT, flr_ambient);
	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, 200);
	glTexCoord2f(1, 1);
	glVertex3f(200, 0, 200);
	glTexCoord2f(0, 1);
	glVertex3f(200, 0, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glPopMatrix();
}
void CreateTextures()
{
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
void Init()
{
	CreateTextures();
	SetUpObject();

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
		if (width < height)
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
void JudgeMaterial(const ball* object)
{
	switch (object->role)
	{
	case 0:
		glMaterialfv(GL_FRONT, GL_AMBIENT, fresh_ball_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, fresh_ball_specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, fresh_ball_diffuse);
		glMaterialf(GL_FRONT, GL_SHININESS, fresh_ball_shiness);
		break;
	case 1:
		glMaterialfv(GL_FRONT, GL_AMBIENT, red_ball_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, red_ball_specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, red_ball_diffuse);
		glMaterialf(GL_FRONT, GL_SHININESS, red_ball_shiness);
		break;
	case 2:
		glMaterialfv(GL_FRONT, GL_AMBIENT, skyblue_ball_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, skyblue_ball_specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, skyblue_ball_diffuse);
		glMaterialf(GL_FRONT, GL_SHININESS, skyblue_ball_shiness);
		break;
	}
}
void draw_balls()
{
	for (int i = 0; i < 5; i++)
	{
		glPushMatrix();
		glEnable(GL_LIGHTING);
		glTranslatef(Ball[i].xyz[0], Ball[i].xyz[1], Ball[i].xyz[2]);
		JudgeMaterial(&Ball[i]);
		gluSphere(sphere, Ball[i].R, 12, 12);
		glDisable(GL_LIGHTING);
		glPopMatrix();
	}
}
void draw_wall(float x, float y, float z, float  Zx, float  Zy, float  Zz)
{
	glPushMatrix();
	glEnable(GL_LIGHTING);
	glTranslatef(x, y, z);
	glScalef(Zx, Zy, Zz);
	draw_cube();
	glDisable(GL_LIGHTING);
	glPopMatrix();
}
void draw_maze()
{
	draw_wall(8.0f, 4.0f, 196.0f, 4.0f, 8.0f, 8.0f);/*left bottom corner*/
	draw_wall(2.0f, 4.0f, 184.0f, 4.0f, 8.0f, 4.0f);

	draw_wall(192.0f, 4.0f, 4.0f, 4.0f, 8.0f, 8.0f);/*right top corner*/
	draw_wall(198.0f, 4.0f, 16.0f, 4.0f, 8.0f, 4.0f);

	draw_wall(184.0f, 4.0f, 16.0f, 8.0f, 8.0f, 4.0f);/*右上出發點*/
	draw_wall(182.0f, 4.0f, 10.0f, 4.0f, 8.0f, 8.0f);

	draw_wall(66.0f, 4.0f, 70.0f, 4.0f, 8.0f, 8.0f);/*open space*/
	draw_wall(68.0f, 4.0f, 64.0f, 8.0f, 8.0f, 4.0f);
	draw_wall(134.0f, 4.0f, 70.0f, 4.0f, 8.0f, 8.0f);
	draw_wall(132.0f, 4.0f, 64.0f, 8.0f, 8.0f, 4.0f);
	draw_wall(66.0f, 4.0f, 130.0f, 4.0f, 8.0f, 8.0f);
	draw_wall(68.0f, 4.0f, 136.0f, 8.0f, 8.0f, 4.0f);
	draw_wall(134.0f, 4.0f, 130.0f, 4.0f, 8.0f, 8.0f);
	draw_wall(132.0f, 4.0f, 136.0f, 8.0f, 8.0f, 4.0f);

	draw_wall(192.0f, 4.0f, 35.0f, 4.0f, 8.0f, 20.0f);/*右上出發點*/
	draw_wall(196.0f, 4.0f, 35.0f, 8.0f, 8.0f, 4.0f);

	draw_wall(100.0f, 4.0f, 48.0f, 54.0f, 8.0f, 4.0f); /*open space 外圍牆(上)*/
	draw_wall(150.0f, 4.0f, 100.0f, 4.0f, 8.0f, 54.0f);/*open space 外圍牆(右)*/
	draw_wall(100.0f, 4.0f, 150.0f, 54.0f, 8.0f, 4.0f);/*open space 外圍牆(下)*/
	draw_wall(50.0f, 4.0f, 100.0f, 4.0f, 8.0f, 54.0f);/*open space 外圍牆(左)*/


}
void draw_scene()
{
	glEnable(GL_LIGHTING);
	draw_floor();

	draw_balls();

	draw_maze();	
	glDisable(GL_LIGHTING);
}
void Forward_Proceeding(ball* object, int WhichOne)
{
	object->xyz[0] += object->speed[0];
	object->xyz[1] += object->speed[1];
	object->xyz[2] += object->speed[2];
	Detect_Boundary(object);
	Investigation(Ball, WhichOne);
}
void myIdle()
{
	Forward_Proceeding(&Ball[0], 0);
	Forward_Proceeding(&Ball[1], 1);
	Forward_Proceeding(&Ball[3], 3);
	display();
}
void keyin(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '+':
		ort_ang -= 5;
		if (ort_ang <= 10)
			ort_ang = 10;
		break;
	case '-':
		ort_ang += 5;
		break;
	case '8':
		eye[2] -= 5.0f;
		focus[2] -= 5.0f;
		break;
	case '2':
		eye[2] += 5.0f;
		focus[2] += 5.0f;
		break;
	case '4':
		eye[0] -= 5.0f;
		focus[0] -= 5.0f;
		break;
	case '6':
		eye[0] += 5.0f;
		focus[0] += 5.0f;
		break;
	}
	display();
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