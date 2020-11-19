#include "Shader.h"

Shader* Shader::s_instance = nullptr;
unsigned int Shader::shader = 0;

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
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

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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

void Shader::InitializeShader()
{
	std::string vertexShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec3 VertexPosition;\n"
		"layout(location = 1) in vec3 VertexColor;\n"
		"layout(location = 2) in vec2 VertexTexCoord;\n"
		"\n"
		"uniform mat4 MVP;\n"
		"uniform float offsetX;\n"
		"uniform float offsetY;\n"
		"\n"
		"out vec3 Color;\n"
		"out vec2 TexCoord;\n"
		"\n"
		"void main()\n"
		"{\n"
		"   Color = VertexColor;\n"
		"   TexCoord.x = VertexTexCoord.x + offsetX;\n"
		"   TexCoord.y = 1.0 - (VertexTexCoord.y + offsetY);\n"
		"   gl_Position = MVP * vec4(VertexPosition, 1.0f);\n"
		"}\n";

	std::string fragmentShader =
		"#version 330 core\n"
		"\n"
		"in vec3 Color;\n"
		"in vec2 TexCoord;\n"
		"\n"
		"uniform sampler2D tex1;\n"
		"uniform float alpha;\n"
		"uniform int mode;\n"
		"\n"
		"out vec4 Color0;"
		"\n"
		"void main()\n"
		"{\n"
		"   vec4 texColor = texture(tex1, TexCoord);\n"
		"   vec4 finalColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
		"   if (mode == 0)\n"
		"       finalColor = vec4(Color, alpha);\n"
		"   else{\n "
		"       texColor.rgb *= alpha; finalColor = texColor;\n"
		"   }"
		"   Color0 = finalColor;\n"
		"}\n";

    shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);
}

void Shader::DeleteShader()
{
    glDeleteProgram(shader);
}