/*
Rotating Rings Code.
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_DEPTH 500

void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides, GLfloat anglex, GLfloat anglez);

int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
    {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho(-SCREEN_WIDTH / 2, SCREEN_WIDTH/2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT/2, -SCREEN_DEPTH / 2, SCREEN_DEPTH/2); // essentially set coordinate system
    glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity(); // same as above comment



    bool flag = true;
    int i = 0;
    float anglex;
    float anglez;
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        i++;
        anglex = i / 2000.0f;
        anglez = i / 2000.0f;
        drawCircle(0.0f,0.0f, 0.0f, 200, 36, anglex, anglez);
        drawCircle(0.0f, 0.0f, 0.0f, 170, 36, -anglez+1, anglex);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides, GLfloat anglex,GLfloat anglez)
{
    const int Temp = 36 + 1;

    const GLint numberOfVertices = Temp;
    const float M_PI = atan(1) * 4;

    GLfloat doublePi = 2.0f * M_PI;

    GLfloat circleVerticesX[numberOfVertices];
    GLfloat circleVerticesY[numberOfVertices];
    GLfloat circleVerticesZ[numberOfVertices];

    GLfloat allCircleVertices[37*2*3];

    for (int i = 0; i < numberOfVertices; i++)
    {
        float Temp1 = y + (radius * sin((float)i * doublePi / numberOfSides));
        float Temp2 = z;

        float A;
        float B;
        float C;

        A = x + (radius * cos((float)i * doublePi / numberOfSides));
        B = cos(anglex)*Temp1 - sin(anglex) * Temp2;
        C = sin(anglex) * Temp1 + cos(anglex) * Temp2;

        allCircleVertices[6 * i + 0] = cos(anglez) * A + sin(anglez) * C;
        allCircleVertices[6 * i + 1] = B;
        allCircleVertices[6 * i + 2] = -sin(anglez) * A + cos(anglez) * C;

        Temp1= y + (1.1f * radius * sin((float)i * doublePi / numberOfSides));
        Temp2 = z;

        A = x + (1.1f * radius * cos((float)i * doublePi / numberOfSides));
        B = cos(anglex) * Temp1 - sin(anglex) * Temp2;
        C = sin(anglex) * Temp1 + cos(anglex) * Temp2;
        allCircleVertices[6 * i + 3] = cos(anglez) * A + sin(anglez) * C;
        allCircleVertices[6 * i + 4] = B;
        allCircleVertices[6 * i + 5] = -sin(anglez) * A + cos(anglez) * C;
    }    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);

    glDrawArrays(GL_QUAD_STRIP, 0, 37*2);
    glDisableClientState(GL_VERTEX_ARRAY);
}








