#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <string>

class Shader {
public:
    Shader(std::string vertexShaderSource, std::string fragmentShaderSource);
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    ~Shader();

    void Bind();
    void Unbind();

    unsigned int GetUniformLocation(const char* name);
private:
    unsigned int shaderProgram;

    unsigned int CreateShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource);
    unsigned int CompileShader(std::string source, unsigned int shaderType);

    std::string ReadFile(std::string filePath);
};
