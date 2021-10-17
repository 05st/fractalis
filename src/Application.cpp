#include "Application.h"
#include "GLFW/glfw3.h"

void Application::run() {
    this->init();
    this->loop();
    this->clean();
}

void Application::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(800, 600, "Fractalis", nullptr, nullptr);
}

void Application::loop() {
    while (!glfwWindowShouldClose(this->window)) {
        glfwPollEvents();
    }
}

void Application::clean() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}
