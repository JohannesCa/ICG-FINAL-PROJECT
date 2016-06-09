//lib includes


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include <string>

//project includes

#include "Window.hpp"

//src



void init(void);
void display(void);
void reshape (int w, int h);
void keyboard(unsigned char key, int x, int y);
void click(int button, int state, int x, int y);
void motion(int x, int y);
void grab(int x, int y);


Window* window = nullptr;

int main(int argc, char** argv)
{
	window = new Window(argc,argv,glm::vec2(512,512),glm::vec2(0,0),std::string("Janela"),init);

	window->display_callback(display);
	window->reshape_callback(reshape);
	window->motion_callback(motion);
	window->grab_callback(grab);
	window->click_callback(click);
	window->keyboard_callback(keyboard);

	(*window)();
	return 0;
}

void init(void)
{
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 10.0 };
   GLfloat light_position[] = { 0.0, 1.0, 1.0, 0.0 };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glutSolidSphere (1.0, 20, 16);
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
         1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
         1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}


void keyboard(unsigned char key, int x, int y)
{
	#define ESC 27

	std::cerr << "key: " << static_cast<int>(key) << " x: " << x << " y: " << y << std::endl;

	switch(static_cast<int>(key))
	{
		case 27:
			window->destroy();
			break;
		default:
			break;
	}
}

void click(int button, int state, int x, int y)
{
	std::cerr << "Button: " << button << " state: " << state << " x: " << x << " y: " << y << std::endl;
}

void motion(int x, int y)
{
	std::cerr << "x: " << x << " y: " << y << std::endl;
}

void grab(int x, int y)
{
	std::cerr << "x: " << x << " y: " << y << std::endl;
}
