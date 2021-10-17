#include "GLFW/glfw3.h"

class Application {
public:
    void run();
private:
    GLFWwindow* window;

    void init();
    void loop();
    void clean();
};
