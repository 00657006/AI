#include"Rendering.h"

int width = 1200, height = 700;
enum list {
	Reset
};

void top_func(int value)
{
	switch (value)
	{
	case Reset:
		SetUpObject();
		break;
	}
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1200, 700);
	glutCreateWindow("AI_Engine");

	Init();

	int top_m = glutCreateMenu(top_func);
	glutAddMenuEntry("Reset!", Reset);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyin);

	glutIdleFunc(&myIdle);

	glutMainLoop();
}