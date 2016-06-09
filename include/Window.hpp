#ifndef WINDOW_H
#define WINDOW_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Window
{
	private:

	public:


		void destroy()
		{
			glutDestroyWindow(1);
		}

		void display_callback(void (*display)())
		{
			glutDisplayFunc(display);
		}

		void reshape_callback(void (*reshape)(int w, int h))
		{
			glutReshapeFunc(reshape);
		}

		void keyboard_callback(void (*keyboard)(unsigned char key, int x, int y))
		{
			glutKeyboardFunc(keyboard);
		}

		void mouse_callback(void (*mouse)(int button, int state, int x, int y))
		{
			glutMouseFunc(mouse);
		}

		void operator()()
		{
			glutMainLoop();
		}

		Window(int argc, char** argv, glm::vec2 size, glm::vec2 position, std::string name, void (*init)()=nullptr)
		{
			glutInit(&argc, argv);
			glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
			glutInitWindowSize (size.x, size.y);
			glutInitWindowPosition (position.x, position.y);
			glutCreateWindow (name.c_str());

			if(init!=nullptr)
			{
				init();
			}
		}
};


#endif
