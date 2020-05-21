#include <stdlib.h>
#include <glut.h>
static int shoulderL = -10, elbowL = -50;
static int shoulderR = 10, elbowR = 50;
void init(void) {
	glClearColor(0, 0, 0, 1);
	glShadeModel(GL_FLAT);
}

void face() {
	glPushMatrix();
		glTranslatef(0, 1.2, 0);
		glColor3f(1, 0, 0);
		glScalef(1, 1, 1);
		glutWireSphere(0.5, 20, 16);
	glPopMatrix();
}

void body() {
	glPushMatrix();
		glTranslatef(0, -0.2, 0);
		glColor3f(1, 0, 0);
		glScalef(1, 1.8, 1);
		glutWireCube(1); // ����
	glPopMatrix();
}

void leftArm() {
	glPushMatrix();
		glTranslatef(0.5, 0.5, 0); // Pivot ���� �� ��ü �̵�
		glRotatef((GLfloat)shoulderL, 0, 0, 1); // ���� ���� ȸ��
		glTranslatef(1, 0, 0); // Pivot�� �������� �̵�
		glPushMatrix(); // ������ �������� ��ü ���� �� ���/Ȯ��
			glColor3f(1, 0, 0);
			glScalef(2, 0.4, 1);
			glutWireCube(1); // �� ���
		glPopMatrix();

		glTranslatef(1, 0, 0); // Pivot ���� �� ��ü �̵�
		glRotatef((GLfloat)elbowL, 0, 0, 1); // ���� ���� ȸ��
		glTranslatef(1, 0, 0); // Pivot�� �������� �̵�
		glPushMatrix(); // ������ �������� ��ü ���� �� ���/Ȯ��
			glColor3f(1, 0, 0);
			glScalef(2, 0.4, 1);
			glutWireCube(1); // �� �Ϻ�
		glPopMatrix();
	glPopMatrix();
}

void rightArm() {
	glPushMatrix();
		glTranslatef(-0.5, 0.5, 0); // Pivot ���� �� ��ü �̵�
		glRotatef((GLfloat)shoulderR, 0, 0, 1); // ���� ���� ȸ��
		glTranslatef(-1, 0, 0); // Pivot�� �������� �̵�
		glPushMatrix(); // ������ �������� ��ü ���� �� ���/Ȯ��
			glColor3f(1, 1, 1);
			glScalef(2, 0.4, 1);
			glutWireCube(1); // �� ���
		glPopMatrix();

		glTranslatef(-1, 0, 0); // Pivot ���� �� ��ü �̵�
		glRotatef((GLfloat)elbowR, 0, 0, 1); // ���� ���� ȸ��
		glTranslatef(-1, 0, 0); // Pivot�� �������� �̵�
		glPushMatrix(); // ������ �������� ��ü ���� �� ���/Ȯ��
			glColor3f(1, 1, 1);
			glScalef(2, 0.4, 1);
			glutWireCube(1); // �� �Ϻ�
		glPopMatrix();
	glPopMatrix();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	leftArm();
	rightArm();
	body();
	face();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65, (GLfloat)w / (GLfloat)h, 1, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -5);
}
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'P':
		shoulderL = (shoulderL + 5) % 360; break;
	case 'O':
		shoulderL = (shoulderL - 5) % 360; break;
	case 'p':
		elbowL = (elbowL + 5) % 360; break;
	case 'o':
		elbowL = (elbowL - 5) % 360; break;
	case 'R':
		shoulderR = (shoulderR + 5) % 360; break;
	case 'E':
		shoulderR = (shoulderR - 5) % 360; break;
	case 'r':
		elbowR = (elbowR + 5) % 360; break;
	case 'e':
		elbowR = (elbowR - 5) % 360; break;
	case 27:
		exit(0); break;
	default:
		break;
	}
	glutPostRedisplay();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Robot Arm");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
