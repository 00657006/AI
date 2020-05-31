#include"Rendering.h"

int width = 1200, height = 700;
int Display_Mode = FULL_SCREEN;
unsigned char gap = 0;

void camera_func(int value)
{
	switch (value)
	{
	case FULL_SCREEN:
		Display_Mode = FULL_SCREEN;
		break;
	case FOLLOW_BALL_0:
		Display_Mode = FOLLOW_BALL_0;
		break;
	case FOLLOW_BALL_1:
		Display_Mode = FOLLOW_BALL_1;
		break;
	}
}
void top_func(int value)
{
	switch (value)
	{
	case Reset:
		SetUpObject();
		gap = 0;
	}
	display();
}

void main(int argc, char** argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1200, 700);
	glutCreateWindow("AI_Engine");

	Init();
	
	int CAMERA_m = glutCreateMenu(camera_func);
	glutAddMenuEntry("FULL_SCREEN", FULL_SCREEN);
	glutAddMenuEntry("FOLLOW_BALL_0", FOLLOW_BALL_0);
	glutAddMenuEntry("FOLLOW_BALL_1", FOLLOW_BALL_1);

	int top_m = glutCreateMenu(top_func);
	glutAddSubMenu("Camera", CAMERA_m);
	glutAddMenuEntry("Reset!", Reset);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyin);

	glutIdleFunc(&myIdle);

	glutMainLoop();
}