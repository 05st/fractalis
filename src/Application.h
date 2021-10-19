#include "glad/glad.h"
#include <GLFW/glfw3.h>

class Application {
public:
    void Run();
private:
    GLFWwindow* window;

    void Init();
    void Loop();
    void Clean();

    void Render();
};
