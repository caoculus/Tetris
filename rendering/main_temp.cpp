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
#include "active.hpp"
#include "next.hpp"
#include "number.hpp"
#include <iostream>


static void APIENTRY
debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
			  GLsizei length, const GLchar *message, const void *userParam)
{
		std::cerr << "Error " << id << ":" << message << std::endl;
		throw std::runtime_error("OpenGL error");
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

    int width  = mode->width    * 3;
    int height = mode->height   * 4;

    float x = height > width ? 1.f : (float)height / (float)width;
    float y = width > height ? 1.f : (float)width / (float)height;

    mat4 screen_matrix = {{
        x, 0.f, 0.f, 0.f,
        0.f, y, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    }};

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

    mesh::bkgd bkgd_(s, g.level());
    mesh::frame f (s);
    mesh::board b (s, g.board());
    mesh::active a(s, g.active_piece(), g.level(), g.state(), g.frame_num());
    mesh::next n(s, g.next());
    mesh::number num(s, g.level(), g.clk());
    

    shader _s;
    _s.bind();
    _s.uniform("tex", 10);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        g.tick();

        _s.uniform("transform", shader::I);
        _s.uniform("u_screen", shader::I);
        bkgd_.draw();

        _s.uniform("u_screen", screen_matrix);
        _s.uniform("transform", shader::J);

        if (g.update())
        {
            b.update();
            g.update(false);
        }
        b.draw();
        a.draw();
        n.update(g.next());
        n.draw();

        _s.uniform("transform", shader::I);
        f.draw();
        num.draw();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    return 0;
}
