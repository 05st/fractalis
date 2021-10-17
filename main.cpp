#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class Application {
public:
    void run();
private:
    VkInstance instance;
    GLFWwindow* window;

    void init();
    void loop();
    void cleanup();

    void createInstance();
};

void Application::run() {
    this->init();
    this->loop();
    this->cleanup();
}

void Application::init() {
    // Initialize GLFW window
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->window = glfwCreateWindow(WIDTH, HEIGHT, "Fractalis", nullptr, nullptr);

    // Initialize Vulkan
    this->createInstance();
}

void Application::createInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Fractalis";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "N/A";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &glfwExtensionCount, nullptr);

    std::vector<VkExtensionProperties> extensions(glfwExtensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &glfwExtensionCount, extensions.data());

    // std::cout << "Available Extensions:" << std::endl;
    // for (const auto& extension : extensions) {
    //     std::cout << '\t' << extension.extensionName << std::endl;
    // }

    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::cout << "Checking Required Extensions:" << std::endl;
    for (int i = 0; i < glfwExtensionCount; i++) {
        std::cout << '\t' << glfwExtensions[i];
        bool found = false;
        for (const auto& extension : extensions) {
            if (strcmp(glfwExtensions[i], extension.extensionName)) {
                found = true;
                break;
            }
        }
        std::cout << (found ? " [OK]" : "[FAIL]") << std::endl;
    }

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    
    createInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&createInfo, nullptr, &this->instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create instance");
    }
}

void Application::loop() {
    while (!glfwWindowShouldClose(this->window)) {
        glfwPollEvents();
    }
}

void Application::cleanup() {
    vkDestroyInstance(this->instance, nullptr);
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

int main() {
    Application app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
