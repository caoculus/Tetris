#include "shader.hpp"
#include <GL/glew.h>

shader::shader()
{
    id_ = glCreateProgram();

    const char *vertex_shader_source =
        "#version 450 core\n"
        "layout (location = 0) in vec4 position;\n"
        "layout (location = 1) in vec2 texcoord;\n"
        "uniform mat4 u_screen;\n"
        "uniform mat4 transform;\n"
        "out vec2 texcoord_out;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = u_screen * transform * position;\n"
        "    texcoord_out = texcoord;\n"
        "}\n",
    
    *fragment_shader_source =
        "#version 450 core\n"
        "in vec2 texcoord_out;\n" 
        "out vec4 color;\n"
        "uniform sampler2D tex;\n"
        "void main()\n"
        "{\n"
        "    color = texture(tex, texcoord_out);\n"
        "}\n";

    unsigned int vertex_shader = compile(GL_VERTEX_SHADER, vertex_shader_source);
    unsigned int fragment_shader = compile(GL_FRAGMENT_SHADER, fragment_shader_source);

    glLinkProgram(id_);
    glValidateProgram(id_);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

unsigned int shader::compile(unsigned int type, const char *source)
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);
    glAttachShader(id_, id);
    return id;
}

shader::~shader()
{
    glDeleteProgram(id_);
}

void shader::bind() const noexcept
{
    glUseProgram(id_);
}

void shader::unbind() const noexcept
{
    glUseProgram(0);
}

void shader::uniform(const char *name, int value) const
{
    if (uniforms_.find(name) == uniforms_.end())
    {
        uniforms_[name] = glGetUniformLocation(id_, name);
    }
    glUniform1i(uniforms_.at(name), value);
}

void shader::uniform(const char *name, const mat4 &value) const
{
    if (uniforms_.find(name) == uniforms_.end())
    {
        uniforms_[name] = glGetUniformLocation(id_, name);
    }
    glUniformMatrix4fv(uniforms_.at(name), 1, GL_FALSE, value.data());
}
