#include "headers/error_codes.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int main() {

    if (!glfwInit()) {

        fprintf(stderr, "Error on trying to init glfw");
        return GLFW_CANT_INIT;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Test", NULL, NULL);

    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, 800, 800);

    glClearColor(0.07f, 0.13f, 0.17f, 0.5f);

    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
