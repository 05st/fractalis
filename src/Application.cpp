#include "Application.h"
#include "Shader.h"

#include <iostream>
#include <stdexcept>

unsigned int width = 800, height = 600;

void Application::Run() {
    this->Init();
    this->Loop();
    this->Clean();
}

void Application::Init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(width, height, "Fractalis", nullptr, nullptr);
    if (!window)
        throw std::runtime_error("Failed to create GLFW window");
    
    glfwMakeContextCurrent(this->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow* window, int nwidth, int nheight) {
        width = nwidth;
        height = nheight;
        Application* app = (Application*)glfwGetWindowUserPointer(window);
        app->WindowSizeCallback(width, height);
    });

    // Setup shader program
    Shader shader = Shader("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");
    shader.Bind();

    // Setup quad
    float vertices[] = {
        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // glBindVertexArray(0);
    
    this->windowSizeLoc = shader.GetUniformLocation("windowSize");

    // VSync
    glfwSwapInterval(0);
}

void Application::Loop() {
    double lastTime = glfwGetTime();
    int nbFrames = 0;
    while (!glfwWindowShouldClose(this->window)) {
        this->Render();

        glfwSwapBuffers(this->window);
        glfwPollEvents();

        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0) {
            std::cout << (double)nbFrames << std::endl;
            nbFrames = 0;
            lastTime += 1.0;
        }
    }
}

void Application::Clean() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

void Application::Render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUniform2f(this->windowSizeLoc, width, height);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Application::WindowSizeCallback(int width, int height) {
    glViewport(0, 0, width, height);
}
