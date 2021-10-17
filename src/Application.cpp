#include "Application.h"

#include <stdexcept>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

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
    if (!window)
        throw std::runtime_error("Failed to create GLFW window");
    
    glfwMakeContextCurrent(this->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
}

void Application::loop() {
    while (!glfwWindowShouldClose(this->window)) {
        this->render();

        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}

void Application::clean() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

void Application::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


}
