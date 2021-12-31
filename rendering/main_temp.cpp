#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "sampler.hpp"
#include "shader.hpp"

#include <iostream>


static void APIENTRY
debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
			  GLsizei length, const GLchar *message, const void *userParam)
{
	if (severity == GL_DEBUG_SEVERITY_HIGH)
	{
		std::cerr << "Error " << id << ":" << message << std::endl;
		throw std::runtime_error("OpenGL error");
	}
}

int main()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    GLFWmonitor *primary_monitor = glfwGetPrimaryMonitor();

    GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "Test",
                                          primary_monitor, nullptr);

    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        exit(1);
    }

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, nullptr);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // set frame rate to 60 fps
    glfwSwapInterval(1);

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    sampler s ("../assets/texatlas.png");
    s.bind(10);


    // 2d rectangle
    std::cout << s("number", 2).Nx << std::endl;
    std::cout << s("number", 2).Ny << std::endl;
    std::cout << s("number", 2).Px << std::endl;
    std::cout << s("number", 2).Py << std::endl;


    float vertices[] = {
        -1.0f, -1.0f, s("number", 2).Nx, s("number", 2).Ny,
        1.0f, -1.0f, s("number", 2).Px, s("number", 2).Ny,
        -1.0f, 1.0f, s("number", 2).Nx, s("number", 2).Py,
        1.0f, 1.0f, s("number", 2).Px, s("number", 2).Py,
    };

    // indices
    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    shader _s;
    _s.bind();
    _s.uniform("tex", 10);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            std::cout << "W pressed" << std::endl;
        }

        // draw elements
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    return 0;
}
