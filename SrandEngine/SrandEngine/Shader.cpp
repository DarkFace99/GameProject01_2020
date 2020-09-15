#include "Shader.h"

unsigned int shader;

std::string vertexShader =
"#version 330 core\n"
"\n"
"layout(location = 0) in vec4 position;\n"
"\n"
"void main()\n"
"{\n"
"   gl_Position = position;\n"
"}\n";

std::string fragmentShader =
"#version 330 core\n"
"\n"
"layout(location = 0) out vec4 color;\n"
"\n"
"void main()\n"
"{\n"
"   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\n";

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;

    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* messege = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, messege);

        std::cout << "Failed to Compile " <<
            (type == GL_VERTEX_SHADER ? "Vertex" : "Fragement")
            << "Shader" << std::endl;
        std::cout << messege << std::endl;

        glDeleteShader(id);

        return 0;
    }

    //TODO Error handling

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void InitializeShader()
{
    shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);
}

void DeleteShader()
{
    glDeleteProgram(shader);
}