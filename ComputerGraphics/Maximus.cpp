/*-----------------------------------------------------------
  6th week (2020. 4. 20)

Keyboard
u a s : face
l k : blueleg
f d : blackleg
p o : right lower arm (90 ~ -90 restict)
r e : left lower arm
0 9 : �ȱ���

Special
UP and DOWN : jump
LEFT and RIGHT : moving-X

6����
(1) ȸ����Ű���� � ���Ϻ�ȯ �Լ��� �ʿ��ұ��? -> glRotatef(����, x��, y��, z��);
(2) ��� ���� ���󿡼� ���ù����� �ٸ��� ��� ���� �������� ȸ���ϰ� �ֳ���? -> z�� ����
(3) blue leg�� ȸ����Ű�� �ٸ� �κп� ������ ���ַ��� � �Լ��� ȣ���ؾ� �ϳ���? -> glPushMatrix(); glPopMatrix();
(4) ȸ����Ű�ϱ� �ٸ��� ��ü���� �и��˴ϴ�. �� ������ �����? -> ������ �������� ȸ���ϱ� ������, �ٸ��� ������ �ƴ� �ٸ� �������� ���� �; ������������ ȸ��
(5) ��Ȯ�� ������� �߽����� ȸ���Ϸ��� ��� �ϸ� �ɱ��?
	-> 1.�ٸ��� �������� �̵� -> 2.ȸ�� -> 3.���󺹱� (�������� ����)
	�ڵ�����
	push
	3. �ٸ� �������� ��ġ�� ����
	2. ȸ��
	1. �ٸ� �������� ��ġ�� �ݴ�
	�ٸ�(Begin ~ End)
	pop

7����
(1) ���� �Ȳ�ġ �Ʒ�(forearm)�� �����Դϴ�. �� ��ü ȸ�� ����� �߰��ϼ��� (P O R E)
   �������� ȥ���� ����ǹǷ� gRedforearm -> gRedforearm, gBlackforearm -> gBlackforearm ����
   �� ��ü�� �������� gRedupperarm, gBlackupperarm����
(2) �����ȿ� �þ�� ����� �߰�
   '0'(zero) ������ ���� �������, '9' ������ ���� ���󺹱��ϴ� �ڵ带 �߰�
(3) ���� scale �Լ��� translate �����ʰ� �ٷ� �𵨿� �����ϸ� �����? -> ������ ������ �ƴϱ� ������ ���� �þ�°� �ƴϰ� ���� Ŀ��
(4) ���� scale �Լ��� ��ü�� ���δ� push/pop ���� ���� ������ �����? -> ��ü�� �׳� �� Ŀ��
(5) �� ���� ����ġ�� �����ϰ� shear�� �����غ�����.
   �������� 1��, �迭����, ��İ� �Լ�(���Ʒ��� tanslate), special�Լ����� F1,F2,F3 �߰�
(6) 2���� �迭�� MyDisplay �Լ��ȿ� ���������� �����ߴµ�, ���������� �ٲٸ� � ���? ��������?
   -> �迭 ���� �� �ȿ� ������ ��������� �װ� ���� ��� ������ ���� ����ִ°Ŷ� ����, ���������� �����ϸ� �׳� 0�� ����ִ°Ŷ� ����, ���������� �Լ� ȣ��ø��� �迭�� ����ǹǷ�
   special�Լ����� �ٲ� ���� �ʱⰪ���� ���� ��
(7) �ٸ����� ����

9����
 - �������� 6�� �߰�
 - YourFlower�Լ��� ��ü������ glTranslatef(gFlowerX, gFlowerY, 0) �߰�
 - MyMotion �Լ�
 - MyReshape�Լ����� �������� 4���� ���������� �־���
 - glutMotionFuncȣ��

 10����
  - menu�߰� day, night (������, �ϴ�, �ʿ�, ��Ʈ, �� �� �ٿ�)
   - timer�߰� rainǥ��(����Լ��� Ư���� �̿��ؼ� �񳻸��� �� ǥ��)

   11����
    - mat�� polygon���� ���ƴµ� glOrtho���ϸ� �Ⱥ��̴� ���� : �������� �β��� �����Ƿ� ������������ �ٷκ��� ���� �Ⱥ���(���������ؾ���)
	- ���� motion���� �����̸� ������ �� �߳������� �ȵǴ� ���� : ���� �߽� y���� �������� ��ġ�� �־��� ������ ������ �Ŀ��� �߳������� �ȵ� -> ���� ������� ��ġ�� �ٲ���
	- glOrtho�� �� �ߵǴ� motion��, ���� �����ϱ� ���콺��ġ�� ���� �ٸ��� ���̴� ���� : �� ���󿡼� ��/���� z�� ���� ���� ���� �ִ� ��ó�� ���̴� �Ͱ� ���� ��ġ (z���� �ٸ��⶧���� �޶���)
-------------------------------------------------------------*/

#include <glut.h>
#include <math.h>
#define WIN_WIDTH 1000  // window 4:3
#define WIN_HEIGHT 750
#define Pi 3.141592

unsigned char gFace = 'u';   // u:usual  a:angry   s:smiling
GLfloat gY = 0.0;  // jump
GLfloat gX = 0.0;  // moving-X
GLfloat gZ= 0.0;  // �յ��̵�

GLfloat gBlueleg = 0.0, gBlackleg = 0.0; // ȸ������
GLfloat gRedforearm = 0.0, gBlackforearm = 0.0, gRedupperarm = 0.0, gBlackupperarm = 0.0; // ȸ������
GLfloat gRedarmlength = 1; // �������� ����
GLfloat gShear = 0.0, gShearleg = 0.0; // 7-(5), 7-(7)
GLfloat gFlowerShear = 0.0, gRootShear = 0.0; // �� ����

GLfloat gFlowerX = -2.8, gFlowerY = -1.5;
GLint gNewWidth, gNewHeight;
GLfloat gWidthFactor, gHeightFactor;
unsigned char gBackground = 'D';
GLint gTimeslot = 0;

void MyBackground();
void MyMat();
void MyFace();
void MyEyeMouth();
void MyBody();
void MyFlower();

void MyUmbrella() {
	if (gBackground == 'R') {
		glPushMatrix();
		glTranslatef(-0.5, 1.5, 0);
		glColor3f(1.0, 1.0, 1.0);
		glLineWidth(4);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, -1.5, 0);
		glEnd();
		glPushMatrix();
		glColor3f(1.0, 1.0, 0.0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(1.2, 0.8, 12, 12);
		glRotatef(90, 0, 1, 0);
		glPopMatrix();
		glPopMatrix();
		gBlackupperarm = 0;
		gBlackforearm = -50;
	}
}

void MyFlower() {
	// ���� ���κ�
	glColor3f(1.0, 1.0, 0.0); 
	glTranslatef(gFlowerX, gFlowerY, 0);
	glScalef(4, 4, 0);
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.03*cos(Angle), 0.035*sin(Angle) + 0.035, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.03*cos(Angle) - 0.03, 0.03*sin(Angle) - 0.035, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.03*cos(Angle) + 0.03, 0.03*sin(Angle) - 0.035, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.03*cos(Angle) + 0.04, 0.03*sin(Angle) + 0.02, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.03*cos(Angle) - 0.04, 0.03*sin(Angle) + 0.02, 0.0);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.04*cos(Angle), 0.04*sin(Angle), 0.0);
	glEnd();

	// ���� �Ʒ��κ�
	glPushMatrix();
	GLfloat flowerRoot_arr[4][4] = {
	   {1,0,0,0},
	   {gRootShear,1,0,0},
	   {0,0,1,0},
	   {0,0,0,1},
	};
	glTranslatef(0, -0.04, 0);
	glMultMatrixf((float*)flowerRoot_arr);
	glTranslatef(0, 0.04, 0);

	glColor3f(1, 1, 1);
	glLineWidth(4);
	glBegin(GL_LINES);
	glVertex3f(0, -0.04, 0);
	glVertex3f(0, -0.2, 0); 
	glEnd(); 
	glLineWidth(1);
	glPopMatrix();
} 

void MyDisplay() {
	// �Ʒ� ������ �׻� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); // display�� Modelview
	glLoadIdentity();
	//gluLookAt(0, 0, 5,  0, 0, 0,  0, 1, 0); // ���� z�� ������ -3, 5

	//glScalef(1, -1, 1); // 2d���� x�࿡ ���� �ݻ�
	//glScalef(-1, 1, 1); // 2d���� y�࿡ ���� �ݻ�

	glTranslatef(0, 0, -5);

	MyBackground();
	MyMat();

	//// y=x �� ���� �ݻ�
	//glRotatef(-45, 0, 0, 1);
	//glScalef(-1, 1, 1);
	//glRotatef(45, 0, 0, 1);

	// ���⼭���ʹ� Maximus
	//glTranslatef(2, 0, 0); // y=x�� ���� �ݻ�
	glPushMatrix();
	glTranslatef(gX, gY, gZ); // left, right, jump, �յ�
	GLfloat Shear_arr[4][4] = {
	   {1,0,0,0},
	   {gShear,1,0,0},
	   {0,0,1,0},
	   {0,0,0,1},
	};
	glTranslatef(0, -1, 0); // ���ù����� �߳�
	glMultMatrixf((float*)Shear_arr);
	glTranslatef(0, 1, 0);
	MyFace();
	MyEyeMouth();
	MyBody();
	MyUmbrella();
	glPopMatrix();

	// ���ܸ� �����ϴ� ���� ����
	glPushMatrix();
	GLfloat Flower_arr[4][4] = {
	   {1,0,0,0},
	   {gFlowerShear,1,0,0},
	   {0,0,1,0},
	   {0,0,0,1},
	};
	glTranslatef(gFlowerX, gFlowerY - 0.8, 0);
	glMultMatrixf((float*)Flower_arr);
	glTranslatef(-gFlowerX, -gFlowerY + 0.8, 0);
	glPushMatrix();
	MyFlower();
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();

} // MyDisplay

void MyBackground() {
	
	if (gBackground == 'D') {
		glColor3f(0, 1, 1); // sky 
	}
	else {
		glColor3f(0.2, 0.2, 0.2); // sky 
	}

	glBegin(GL_POLYGON);
	glVertex3f(-10, 0, -3.9);
	glVertex3f(10, 0, -3.9);
	glVertex3f(10, 8, -3.9);
	glVertex3f(-10, 8, -3.9);
	glEnd();

	if (gBackground == 'D') {
		glColor3f(0, 1, 0); // green 
	}
	else {
		glColor3f(0, 0.3, 0); // green 
	}

	glBegin(GL_POLYGON);
	glVertex3f(-10, -8, -3.9);
	glVertex3f(10, -8, -3.9);
	glVertex3f(10, 0, -3.9);
	glVertex3f(-10, 0, -3.9);
	glEnd();

	if (gBackground == 'R') {
		glColor3f(0.9, 0.9, 0.9); // �� ��
		if (gTimeslot % 3 == 0) {
			glBegin(GL_LINES);
			glVertex3f(-3, 2, 0); glVertex3f(-3, 1.8, 0);
			glVertex3f(3.3, 2.8, 0); glVertex3f(3.3, 2.6, 0);
			glEnd();
		}
		else if (gTimeslot % 3 == 1) {
			glBegin(GL_LINES);
			glVertex3f(0, 2.7, 0); glVertex3f(0, 2.5, 0);
			glEnd();
		}
		else {
			glBegin(GL_LINES);
			glVertex3f(-1, 1.7, 0); glVertex3f(-1, 1.5, 0);
			glVertex3f(2.9, 1.8, 0); glVertex3f(2.9, 1.6, 0);
			glEnd();
		}
	}
}

void MyMat() {
	if (gBackground == 'D') {
		glColor3f(0xE4 / 255.0, 0xBE / 255.0, 0xFE / 255.0); // �������   
	}
	else {
		glColor3f(0.3, 0, 0.3);
	}
	
	//glBegin(GL_POLYGON);
	//glVertex3f(-1.5, -1.3, 0); // �ٴڿ� �����־�� �ϴµ�, ���� 2D�� ���߿� ���ִ� ����纯��
	//glVertex3f(1.2, -1.3, 0); // 3D�ΰ���, ��¥ �ٴڿ� ������ ��Ʈ�� ��ȯ�� ����
	//glVertex3f(1.5, -0.8, 0);
	//glVertex3f(-1.2, -0.8, 0);
	//glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-1.5, -1, 1.5); // �ٴڿ� ������ ���簢��
	glVertex3f(1.5, -1, 1.5);
	glVertex3f(1.5, -1, -1.5);
	glVertex3f(-1.5, -1, -1.5);
	glEnd();

} // MyMat

void MyFace() {
	if (gBackground == 'D') {
		glColor3f(251 / 255.0, 206 / 255.0, 177 / 255.0); // �챸��
	}
	else {
		glColor3f(0.6, 0.4, 0.4);
	}
	glPushMatrix(); // ��� ����(3�忡�� �ڼ��� ���)
	glTranslatef(0, 1, 0); // ���� �̵���Ű�� ���ؼ�
	glutSolidSphere(0.5, 50, 50); // glut�� ������ �������� �׷���
	glPopMatrix(); // push�� ������ pop

} // MyFace 

void MyEyeMouth() {

	if (gFace == 'a') {  // angry

		glColor3f(0, 0, 0); // black
		glBegin(GL_LINES);
		glVertex3f(-0.3, 1.2, 0.0); // eye
		glVertex3f(-0.1, 1.0, 0.0);
		glVertex3f(0.1, 1.0, 0.0); // eye
		glVertex3f(0.3, 1.2, 0.0);
		glEnd();

		glBegin(GL_LINE_LOOP); // mouth
		glVertex3f(-0.1, 0.9, 0.0);
		glVertex3f(0.1, 0.9, 0.0);
		glVertex3f(0.1, 0.8, 0.0);
		glVertex3f(-0.1, 0.8, 0.0);
		glEnd();
	}
	else if (gFace == 's') { // smiling

		glColor3f(0, 0, 0); // black
		glBegin(GL_LINE_STRIP); // eye
		glVertex3f(-0.3, 1.1, 0.0);
		glVertex3f(-0.2, 1.15, 0.0);
		glVertex3f(-0.1, 1.1, 0.0);
		glEnd();

		glBegin(GL_LINE_STRIP);   // eye
		glVertex3f(0.1, 1.1, 0.0);
		glVertex3f(0.2, 1.15, 0.0);
		glVertex3f(0.3, 1.1, 0.0);
		glEnd();

		glColor3f(1, 0, 0); // red
		glBegin(GL_LINE_LOOP); // mouth
		glVertex3f(-0.1, 0.9, 0.0);
		glVertex3f(0.1, 0.9, 0.0);
		glVertex3f(0, 0.8, 0.0);
		glEnd();
	}
	else if (gFace == 'u') { // usual

		glColor3f(0, 0, 0); // black
		glBegin(GL_LINES);
		glVertex3f(-0.3, 1.1, 0.0); // eye
		glVertex3f(-0.1, 1.1, 0.0);
		glVertex3f(0.1, 1.1, 0.0); // eye
		glVertex3f(0.3, 1.1, 0.0);
		glVertex3f(-0.1, 0.9, 0.0); // mouth
		glVertex3f(0.1, 0.9, 0.0);
		glEnd();
	}

} // MyEyeMouth 

void MyBody() {

	glColor3f(0, 0, 0); // black neck
	glBegin(GL_LINES);
	glVertex3f(0, 0.5, 0.0);
	glVertex3f(0, 0.3, 0.0);
	glEnd();

	glColor3f(0.5, 0.5, 0.5); // gray spine
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, -0.3, 0.0);
	glVertex3f(0.05, -0.3, 0.0);
	glVertex3f(0.05, 0.3, 0.0);
	glVertex3f(-0.05, 0.3, 0.0);
	glEnd();


	glPushMatrix(); // red ū �� ����
	glTranslatef(0.05, 0.3, 0.0);
	glRotatef(gRedupperarm, 0, 0, 1);
	glScalef(gRedarmlength, gRedarmlength, 1);
	glTranslatef(-0.05, -0.3, 0.0);
	glLineWidth(3); // line 
	glColor3f(1, 0, 0); // red arm
	glBegin(GL_LINES); // upper
	glVertex3f(0.05, 0.3, 0.0);
	glVertex3f(0.25, 0.1, 0.0);
	glEnd();

	glPushMatrix();
	glTranslatef(0.25, 0.1, 0.0);
	glRotatef(gRedforearm, 0, 0, 1);
	glTranslatef(-0.25, -0.1, 0.0);
	glBegin(GL_LINES); // lower   
	glVertex3f(0.25, 0.1, 0.0);
	glVertex3f(0.5, -0.2, 0.0);
	glEnd();
	glPopMatrix();
	glPopMatrix(); // ū �� pop

	glPushMatrix(); // black ū �� ����
	glTranslatef(-0.05, 0.3, 0.0);
	glRotatef(gBlackupperarm, 0, 0, 1);
	glTranslatef(0.05, -0.3, 0.0);
	glColor3f(0, 0, 0); // black arm
	glBegin(GL_LINES); //upper
	glVertex3f(-0.05, 0.3, 0.0);
	glVertex3f(-0.25, 0.1, 0.0);
	glEnd();

	glPushMatrix();
	glTranslatef(-0.25, 0.1, 0.0);
	glRotatef(gBlackforearm, 0, 0, 1);
	glTranslatef(0.25, -0.1, 0.0);
	glBegin(GL_LINES); //lower
	glVertex3f(-0.25, 0.1, 0.0);
	glVertex3f(-0.5, -0.2, 0.0);
	glEnd();
	glPopMatrix();
	glPopMatrix(); // ū �� pop

	// �ٸ��� ����
	glPushMatrix(); // �ٸ� �ΰ� ����
	GLfloat Shearleg_arr[4][4] = {
	   {1,0,0,0},
	   {gShearleg,1,0,0},
	   {0,0,1,0},
	   {0,0,0,1},
	};
	glTranslatef(0, -0.3, 0);
	glMultMatrixf((float*)Shearleg_arr);
	glTranslatef(0, 0.3, 0);

	glColor3f(0, 0, 1); // blue leg
	glPushMatrix();
	glTranslatef(0.05, -0.3, 0.0); // (3) �ٸ��� ���󺹱�
	glRotatef(gBlueleg, 0, 0, 1); // (2) z�� �������� ȸ��
	glTranslatef(-0.05, 0.3, 0.0); // (1) �ٸ��� �������� �����ϵ��� �̵�
	glBegin(GL_LINES);
	glVertex3f(0.05, -0.3, 0.0); // leg high point
	glVertex3f(0.3, -1.0, 0.0);
	glEnd();
	glPopMatrix();

	glColor3f(0, 0, 0); // black leg
	glPushMatrix();
	glTranslatef(-0.05, -0.3, 0.0);
	glRotatef(gBlackleg, 0, 0, 1);
	glTranslatef(0.05, 0.3, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-0.05, -0.3, 0.0);
	glVertex3f(-0.3, -1.0, 0.0);
	glEnd();
	glPopMatrix();
	glPopMatrix(); // �δٸ� �����Ѱ� pop
	glLineWidth(1);  // line

} // MyBody

void MyKeyboard(unsigned char key, int x, int y) {

	switch (key) {

	case 'Q':
	case 'q':   exit(0);  break;

	case 'a':
	case 's':
	case 'u':   gFace = key;   break;    // face

	case 'l':   gBlueleg += 10; break; // �ٸ�ȸ��
	case 'k':   gBlueleg -= 10; break;

	case 'f':   gBlackleg += 10; break; // �ٸ�ȸ��
	case 'd':   gBlackleg -= 10; break;

	case 'p':   if (gRedforearm < 90) gRedforearm += 3; break;
	case 'o':   if (gRedforearm > -90) gRedforearm -= 3; break;

	case 'r':   if (gBlackforearm < 90) gBlackforearm += 3; break;
	case 'e':   if (gBlackforearm > -90) gBlackforearm -= 3; break;

	case 'P':   if (gRedupperarm < 90) gRedupperarm += 3; break;
	case 'O':   if (gRedupperarm > -90) gRedupperarm -= 3; break;

	case 'R':   if (gBlackupperarm < 90) gBlackupperarm += 3; break;
	case 'E':   if (gBlackupperarm > -90) gBlackupperarm -= 3; break;

	case '0':   gRedarmlength *= 1.1; break;
	case '9':   if (gRedarmlength > 1) gRedarmlength /= 1.1; break;
	}

	glutPostRedisplay();

} // MyKeyboard

void MySpecial(int key, int x, int y) {

	switch (key) {

	case GLUT_KEY_UP:
		gY = 1;
		gFace = 's';
		gRedforearm = 30; // �ݽð�
		gBlackforearm = -30; // �ð�
		gBlueleg = -19.5; // �ݽð�
		gBlackleg = 19.5; // �ð�
		break;
	case GLUT_KEY_DOWN:
		gY = 0;
		gFace = 'u';
		gRedforearm = gBlackforearm = gBlueleg = gBlackleg = 0;
		break;
	case GLUT_KEY_LEFT:
		if (gY == 0) {
			gX -= 0.1;
			if (gX < -1.5 || gX > 1.5) gFace = 'a';
			else gFace = 'u';
		}
		break;
	case GLUT_KEY_RIGHT:
		if (gY == 0) {
			gX += 0.1;
			if (gX < -1.5 || gX > 1.5) gFace = 'a';
			else gFace = 'u';
		}
		break;
	case GLUT_KEY_F1: gShear = -0.5; gFace = 's'; gRedupperarm = 48; gBlackupperarm = -48; gFlowerShear = -0.5; break; // ���� ����
	case GLUT_KEY_F2: gShear = 0.0; gFace = 'u'; gRedupperarm = 0; gBlackupperarm = 0; gFlowerShear = 0.0; break;
	case GLUT_KEY_F3: gShear = 0.5; gFace = 's'; gRedupperarm = 48; gBlackupperarm = -48; gFlowerShear = 0.5; break;

	case GLUT_KEY_F4: gShearleg = 0.5; gFace = 's'; gRedupperarm = 48; gBlackupperarm = -48; gRootShear = 0.5; break; // �ٸ� ���� (���Ű� ��ȣ�� �ٸ� ���� : ��ݽ��� �������� �ٸ��� ������)
	case GLUT_KEY_F5: gShearleg = 0.0; gFace = 'u'; gRedupperarm = 0; gBlackupperarm = 0; gRootShear = 0.0; break;
	case GLUT_KEY_F6: gShearleg = -0.5; gFace = 's'; gRedupperarm = 48; gBlackupperarm = -48; gRootShear = -0.5; break;

	case GLUT_KEY_F11: if (gZ <= 3) { gZ += 0.1; } break;
	case GLUT_KEY_F12: if (gZ >= -3) { gZ -= 0.1; } break;
	}

	glutPostRedisplay();

} // MySpecial

void MyMotion(GLint X, GLint Y) {
	gFlowerX = (GLfloat)X / gNewWidth * 8 * gWidthFactor - 4 * gWidthFactor;
	gFlowerY = (GLfloat)(gNewHeight - Y) / gNewHeight * 6 * gHeightFactor - 3  * gHeightFactor;
	glutPostRedisplay();
} // MyMotion

void MyReshape(int NewWidth, int NewHeight) {

	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)WIN_WIDTH;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)WIN_HEIGHT;
	gWidthFactor = WidthFactor, gHeightFactor = HeightFactor;
	gNewWidth = NewWidth, gNewHeight = NewHeight;
	glMatrixMode(GL_PROJECTION); // reshape���� projection
	glLoadIdentity();
	//glOrtho(-4.0 * WidthFactor, 4.0 * WidthFactor, -3.0 * HeightFactor, 3.0 * HeightFactor, 1, 9); // z���� x�� �����ɷ� ����
	gluPerspective(65, (GLfloat)NewWidth / NewHeight, 1, 9);

} // MyReshape

void MyTimer(int Value) {
	if (gBackground == 'R') {
		gTimeslot = (gTimeslot + 1) % 100;
		glutPostRedisplay();
		glutTimerFunc(400, MyTimer, 1);
	}
}

void MyMainMenu(int entryID) {
	if (entryID == 1) {
		glClearColor(1, 1, 1, 1);
		gBackground = 'D';
	}
	else if (entryID == 2) {
		glClearColor(0, 0, 0, 0);
		gBackground = 'N';
	}
	else {
		glClearColor(0, 0, 0, 0);
		gBackground = 'R';
		glutTimerFunc(400, MyTimer, 1);
	}
	glutPostRedisplay();
}

void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0); 
	//glEnable(GL_DEPTH_TEST);
	// menu callback 
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("Day", 1);
	glutAddMenuEntry("Night", 2);
	glutAddMenuEntry("Rain", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

} // MyInit

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutInitWindowPosition(150, 0);
	glutCreateWindow("Maximus");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MySpecial);
	glutMotionFunc(MyMotion);
	glutMainLoop();
	return 0;
}