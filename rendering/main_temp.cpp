#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "sampler.hpp"
#include "shader.hpp"
#include "game/level.hpp"
#include "background.hpp"

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

    // draw background
    // draw frame
    // draw the "dead pieces"
    // draw the "active piece"
    // draw the shadow
    // draw the "next piece"
    // draw the numbers


    sampler s ("../assets/texatlas.png");
    s.bind(10);

    level_counter level;

    bkgd bkgd_(s, level);

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

        bkgd_.draw();


        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    return 0;
}
