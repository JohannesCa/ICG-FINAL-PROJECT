// Std. Includes
#include <string>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include <SOIL.h>

// Properties
GLuint screenWidth = 1280, screenHeight = 720;
GLfloat theta = 0;
bool enableKey = true;
bool enableExitKey = false;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();

// Camera
Camera camera(glm::vec3(4.0f, 1.6f, 0.0f));
bool keys[1024];
GLfloat lastX, lastY;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int KEY = -1;

// The MAIN function, from here we start our application and run our Game loop
int main()
{
// Initializing Window
    // Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Project Helios", nullptr, nullptr); // Windowed

    glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Initialize GLEW to setup the OpenGL Function pointers
	glewExperimental = GL_TRUE;
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, screenWidth, screenHeight);

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);

// Shaders - - - -

	// Setup and compile our shaders
	Shader shader("resources/shaders/model_loading.vs", "resources/shaders/model_loading.frag");

// Models - - - -


	glfwSetWindowTitle(window, "FAZ O SAMPLE DE GUITARRA");

	while(KEY!=GLFW_KEY_ENTER)
	{
	        glfwPollEvents();
	        // Clear the colorbuffer
	        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(window);
	}
	
    // Load Models
    Model Map("resources/models/Mapa.obj");
    Model Bat1("resources/models/Huge Battery.obj");
    Model Bat2("resources/models/Huge Battery.obj");
    Model Bat3("resources/models/Huge Battery.obj");
    Model Bat4("resources/models/Huge Battery.obj");
    Model Keycard("resources/models/Keycard.obj");
    Model KeyExit("resources/models/Keycard.obj");
    Model Gun("resources/models/The Gun.obj");

    // Draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


//LOOP - - - -
	// Game loop
	while(!glfwWindowShouldClose(window))
	{
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        Do_Movement();

        // Clear the colorbuffer
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();   // <-- Don't forget this one!


        // Transformation matrices
        glm::mat4 projection = glm::perspective(camera.Zoom, (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));


        // Draw the loaded model
        glm::mat4 model_map;
        glm::mat4 model_bat1;
        glm::mat4 model_bat2;
        glm::mat4 model_bat3;
        glm::mat4 model_bat4;
        glm::mat4 model_key;
        glm::mat4 model_keyExit;
        glm::mat4 model_gun;


        // Prepare Matrices
        model_map = glm::scale(model_map, glm::vec3(0.001f, 0.001f, 0.001f));

        model_bat1 = glm::translate(model_bat1, glm::vec3(6.5f, 0.0f, 4.0f));
        model_bat1 = glm::rotate(model_bat1, glm::radians(-135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model_bat1 = glm::scale(model_bat1, glm::vec3(0.001f, 0.001f, 0.001f));

        model_bat2 = glm::translate(model_bat2, glm::vec3(6.5f, 0.0f, -4.0f));
        model_bat2 = glm::rotate(model_bat2, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model_bat2 = glm::scale(model_bat2, glm::vec3(0.001f, 0.001f, 0.001f));

        model_bat3 = glm::translate(model_bat3, glm::vec3(6.5f, 0.0f, 0.0f));
        model_bat3 = glm::rotate(model_bat3, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model_bat3 = glm::scale(model_bat3, glm::vec3(0.001f, 0.001f, 0.001f));

        model_bat4 = glm::translate(model_bat4, glm::vec3(-6.5f, 0.0f, 4.0f));
        model_bat4 = glm::rotate(model_bat4, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model_bat4 = glm::scale(model_bat4, glm::vec3(0.001f, 0.001f, 0.001f));

        model_key = glm::translate(model_key, glm::vec3(1.6f, 1.32f, -0.3f));
        model_key = glm::rotate(model_key, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model_key = glm::scale(model_key, glm::vec3(0.001f, 0.001f, 0.001f));

        model_keyExit = glm::translate(model_keyExit, glm::vec3(-6.25f, 1.2f, -4.99f));
        model_keyExit = glm::rotate(model_keyExit, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model_keyExit = glm::scale(model_keyExit, glm::vec3(0.001f, 0.001f, 0.001f));


        // Draw
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model_map));
        Map.Draw(shader);

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model_bat1));
        Bat1.Draw(shader);

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model_bat2));
        Bat2.Draw(shader);

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model_bat3));
        Bat3.Draw(shader);

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model_bat4));
        Bat4.Draw(shader);


        // Verify if the key was taken
        if(enableKey){
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model_key));
            Keycard.Draw(shader);
        }

        if(enableExitKey){
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model_keyExit));
            KeyExit.Draw(shader);
        }


        // Swap the buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}


#pragma region "User input"

// Moves/alters the camera positions based on user input
void Do_Movement()
{
    //GLfloat offsetX = 0.0;//01 * cos(glm::radians(theta));
    GLfloat offsetY = 0.0005 * sin(glm::radians(theta));

    if((keys[GLFW_KEY_W])||(keys[GLFW_KEY_S])||(keys[GLFW_KEY_A])||(keys[GLFW_KEY_D])){

        // Camera controls
        if(keys[GLFW_KEY_W])
            camera.ProcessKeyboard(FORWARD, deltaTime, offsetY);
        if(keys[GLFW_KEY_S])
            camera.ProcessKeyboard(BACKWARD, deltaTime, offsetY);
        if(keys[GLFW_KEY_A])
            camera.ProcessKeyboard(LEFT, deltaTime, offsetY);
        if(keys[GLFW_KEY_D])
            camera.ProcessKeyboard(RIGHT, deltaTime, offsetY);

        if(theta > 360)
            theta = 0;
        else
            theta += 0.8;
    }

    if((camera.Position.x > 0.5)&&(camera.Position.x < 1.5)&&(camera.Position.z > -1)&&(camera.Position.z < 1)&&(keys[GLFW_KEY_E]))
        enableKey = false;

    if((camera.Position.x > -7.5)&&(camera.Position.x < -5)&&(camera.Position.z > -5)&&(camera.Position.z < -3)&&(keys[GLFW_KEY_E])&&(!enableKey))
        enableExitKey = true;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    KEY = key;
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if((camera.Position.x > -7.5)&&(camera.Position.x < -5)&&(camera.Position.z > -5)&&(camera.Position.z < -3)&&(keys[GLFW_KEY_E])&&(!enableKey))
        glfwSetWindowShouldClose(window, GL_TRUE);

    if(action == GLFW_PRESS)
        keys[key] = true;
    else if(action == GLFW_RELEASE)
        keys[key] = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

#pragma endregion
