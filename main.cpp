#include "glad/glad.h"
#include "glad/khrplatform.h"
#include <GLFW/glfw3.h>
#include "shader.h"
#include <iostream>
#include <math.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void cursor_callback(GLFWwindow* window,double xPos, double yPos);

// settings
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;
float zoom = 1; double lastCX, lastCY,camX,camY;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MandelBrot Set Explorer", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    Shader MandelBrot("vertex.glsl", "fragment.glsl");

    // set up vertex data
    float vertices[] = {
        // positions         // colors
         3.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         -1.0f,  3.0f, 0.0f,  0.0f, 0.0f, 1.0f   // top
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        if(zoom <= 1){zoom = 1;}//makes sure the zoom coeficient isnt too big
        processInput(window);
        glfwSetScrollCallback(window, scroll_callback);
        glfwSetCursorPosCallback(window, cursor_callback);
        MandelBrot.setFloat("Time",glfwGetTime());
        MandelBrot.setFloat("zoom",(zoom));
        MandelBrot.setFloat("ScrRatio",float(SCR_WIDTH)/float(SCR_HEIGHT));
        MandelBrot.setFloat2("camera",camX,camY);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        MandelBrot.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_TAB) != GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        glfwGetWindowSize(window,&SCR_WIDTH, &SCR_HEIGHT);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions;
    glViewport(0, 0, width, height);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    zoom += yoffset*(zoom/10);

}
void cursor_callback(GLFWwindow* window,double xPos, double yPos)
{
    double diffX = xPos - lastCX;
    double diffY = yPos - lastCY;
    lastCX = xPos;
    lastCY = yPos;
    camX +=(diffX/(zoom))/SCR_WIDTH;
    camY -=(diffY/(zoom))/SCR_HEIGHT;

}
