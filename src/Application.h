#include "glad/glad.h"
#include <GLFW/glfw3.h>

class Application {
public:
    void Run();
private:
    GLFWwindow* window;
    int windowSizeLoc;

    void Init();
    void Loop();
    void Clean();

    void Render();

    void WindowSizeCallback(int width, int height);
};
