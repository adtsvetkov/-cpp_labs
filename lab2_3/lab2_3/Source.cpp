#include <time.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>

template <class T>

class gvector {
public:
	T x, y;

	gvector() :x(0), y(0) {}
	gvector(T x, T y) : x(x), y(y) {}
	gvector(const gvector& v) : x(v.x), y(v.y) {}

	gvector& operator=(const gvector& v);
	gvector operator+(gvector& v);
	gvector operator-(gvector& v);
	gvector& operator+=(gvector& v);
	gvector& operator-=(gvector& v);
	gvector operator+(double s);
	gvector operator-(double s);
	gvector operator*(double s);
	gvector operator/(double s);
	gvector& operator+=(double s);
	gvector& operator-=(double s);
	gvector& operator*=(double s);
	gvector& operator/=(double s);
	void set(T x, T y);
	void rotate(double deg);
	float length() const;
};

template <typename T>
gvector<T> gvector<T>::operator+(gvector& v) {
	return gvector(x + v.x, y + v.y);
}

template <typename T>
gvector<T> gvector<T>::operator-(gvector& v) {
	return gvector(x - v.x, y - v.y);
}

template <typename T>
gvector<T> gvector<T>::operator+(double s) {
	return gvector(x + s, y + s);
}

template <typename T>
gvector<T> gvector<T>::operator-(double s) {
	return gvector(x - s, y - s);
}

template <typename T>
gvector<T> gvector<T>::operator*(double s) {
	return gvector(x * s, y * s);
}

template <typename T>
gvector<T> gvector<T>::operator/(double s) {
	return gvector(x / s, y / s);
}

template <typename T>
gvector<T>& gvector<T>::operator=(const gvector& v) {
	x = v.x;
	y = v.y;
	return *this;
}

template <typename T>
gvector<T>& gvector<T>::operator+=(gvector& v) {
	x += v.x;
	y += v.y;
	return *this;
}

template <typename T>
gvector<T>& gvector<T>::operator-=(gvector& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

template <typename T>
gvector<T>& gvector<T>::operator+=(double s) {
	x += s;
	y += s;
	return *this;
}
template <typename T>
gvector<T>& gvector<T>::operator-=(double s) {
	x -= s;
	y -= s;
	return *this;
}

template <typename T>
gvector<T>& gvector<T>::operator*=(double s) {
	x *= s;
	y *= s;
	return *this;
}

template <typename T>
gvector<T>& gvector<T>::operator/=(double s) {
	x /= s;
	y /= s;
	return *this;
}

template <typename T>
void gvector<T>::set(T x, T y) {
	this->x = x;
	this->y = y;
}

template <typename T>
void gvector<T>::rotate(double deg) {
	double theta = deg / 180.0 * M_PI;
	double c = cos(theta);
	double s = sin(theta);
	double tx = x * c - y * s;
	double ty = x * s + y * c;
	x = tx;
	y = ty;
}

template <typename T>
float gvector<T>::length() const {
	return std::sqrt(x * x + y * y);
}

typedef gvector<double> gvectord;

int dir, num = 15;
int size = 4;

class dot {
private:
	int N = 30, M = 20;
	int scale = 25;
	gvectord dots[4];
public:
	void DrawTrace(int size = 1);
	void Tick(int dir, int size = 1);
	void Init();
};

void dot::DrawTrace(int size) {
	glColor3f(0.0, 0.0, 1.0);
	/*for (int i = 0; i < size - 1; i++)
	{
		glLineWidth(1000);
		glEnable(GL_LINE_SMOOTH);
		glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3d(dots[i].x*scale, dots[i].y*scale, 0.0);
		glVertex3d(dots[i + 1].x*scale, dots[i + 1].y*scale, 0.0);
		glEnd();
	}*/
	glPointSize(10);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3d(dots[0].x*scale, dots[0].y*scale, 0.0);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
}

void dot::Tick(int dir, int size) 
{
	/*for (int i = size - 1; i>0; --i)
	{
		dots[i].x = dots[i - 1].x;
		dots[i].y = dots[i - 1].y;
	}*/
	if (dir == 0) dots[0].y += 1;
	if (dir == 1) dots[0].x -= 1;
	if (dir == 2) dots[0].x += 1;
	if (dir == 3) dots[0].y -= 1;


//	if (dots[0].x>N) dir = 1;  if (dots[0].x<0) dir = 2;
	//if (dots[0].y>M) dir = 3;  if (dots[0].y<0) dir = 0;
}

void dot::Init() {
	for (int i = 0; i < 4; i++)
	{
		dots[i].x = 10 - i;
		dots[i].y = 10;
	}
}
dot d;
void Init()
{
	d.Init();
}

void KeyboardEvent(int key, int a, int b)
{
	switch (key)
	{
	case 101:  dir = 0; break;
	case 102:  dir = 2; break;
	case 100:  dir = 1; break;
	case 103:  dir = 3; break;
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	d.DrawTrace(4);
	glFlush();
	glutSwapBuffers();
}

void timer(int = 0)
{
	display();
	d.Tick(dir, 4);
	glutTimerFunc(200, timer, 0);
}

int main(int argc, char **argv) 
{
	dot c;
	srand(time(0));
	Init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(30 * 25, 20 * 25);
	glutCreateWindow("Test");
	glClearColor(1.0, 1.0, 0.6, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 30 * 25, 0, 20 * 25);

	glutDisplayFunc(display);
	glutSpecialFunc(KeyboardEvent);
	glutTimerFunc(50, timer, 0);

	glutMainLoop();
}