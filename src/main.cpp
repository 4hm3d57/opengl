#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <header/shader.h>
#include <iostream>
#include <cmath>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);



const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



int main() {
    //initialize and configure glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Ahmed's window", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to initialize window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize glad" << std::endl;
        return -1;
    }
    
    //shader stuff
    Shader ourShader("./shaders/default.vert", "./shaders/default.frag");


    float vertices[] = {
         0.0f,  0.5f, 0.0f, 1.0, 0.0, 0.0,
        -0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0,
         0.5f, -0.5f, 0.0f, 0.0, 0.0, 1.0
    };

    //vertex attrib stuff
    unsigned int vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    //vertices
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //positional attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //render void loop

    while (!glfwWindowShouldClose(window)) {
        //input
        processInput(window);
        //rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0 + 0.5;
        int vertexColorLocation = glGetUniformLocation(ourShader.ID, "ourColor");
        ourShader.use();
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glfw swapbuffer and poll event
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window){
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
    glfwSetWindowShouldClose(window, true);
    std::cout << "---------------------" << std::endl;
    std::cout << "[LOG]: TASK COMPLETED" << std::endl;
    std::cout << "---------------------" << std::endl;
  }
}

