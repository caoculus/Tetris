#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "sampler.hpp"
#include "shader.hpp"
#include "game/level.hpp"
#include "background.hpp"
#include "frame.hpp"
#include "board.hpp"
#include "game/game.hpp"
#include <iostream>


static void APIENTRY
debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
			  GLsizei length, const GLchar *message, const void *userParam)
{
	if (severity >= GL_DEBUG_SEVERITY_MEDIUM)
	{
		std::cerr << "Error " << id << ":" << message << std::endl;
		throw std::runtime_error("OpenGL error");
	}
}

static std::ostream &operator<< (std::ostream &os, const board_t &board)
{
    for (const auto &row : board)
    {
        for (const auto &cell : row)
        {
            switch (cell)
            {
            case square::none:
                os << ".";
                break;
            case square::I:
                os << "I";
                break;
            case square::J:
                os << "J";
                break;
            case square::L:
                os << "L";
                break;
            case square::O:
                os << "O";
                break;
            case square::S:
                os << "S";
                break;
            case square::T:
                os << "T";
                break;
            case square::Z:
                os << "Z";
                break;
            default:
                os << "?";
                break;
            }
        }
        os << std::endl;
    }
    return os;
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // set frame rate to 60 fps
    glfwSwapInterval(1);

    // draw background
    // draw frame
    // draw the "dead pieces"
    // draw the "active piece"
    // draw the shadow
    // draw the "next piece"
    // draw the numbers


    game::tetris g(window);
    sampler s ("../assets/texatlas.png");
    s.bind(10);

    game::level_counter level;

    mesh::bkgd bkgd_(s, level);
    mesh::frame f (s, mode);
    mesh::board b (s, g.board());
    

    shader _s;
    _s.bind();
    _s.uniform("tex", 10);
    _s.uniform("transform", {1.0f, 0.0f, 0.0f, 0.0f, 
                             0.0f, 1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 1.0f, 0.0f,
                             1.0f, 1.0f, 0.0f, 1.0f});

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            std::cout << "W pressed" << std::endl;
        }
        
        g.tick();

        _s.uniform("transform", shader::I);
        bkgd_.draw();
        f.draw();

        _s.uniform("transform", shader::J);

        if (g.update())
        {
            b.update();
            std::cout << g.board() << std::endl;
            g.update(false);
        }
        b.draw();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    return 0;
}
