#define RENDERING_ENGINE 1

#include "rendering/rendering.hpp"
#include "game.hpp"
#include <cstring>
#include <utility>

/**
 * @brief Initializes GLFWwindow and OpenGL context using GLEW.
 *
 * @param proj_xx xx entry of the screen matrix.
 * @param proj_yy yy entry of the screen matrix.
 *
 * @details The screen matrix projects the emulated Tetris game to the actual
 * screen.
 *
 * @return pointer to the created window
 * @throws window_exception if the window could not be created.
 */
static GLFWwindow *init(float &proj_xx, float &proj_yy);

/**
 * @brief Parses the command line arguments.
 *
 * @param argc number of arguments.
 * @param argv array of arguments.
 * @param bkgd_dim number from 0 to 8 indicated how much the background should
 * be dimmed.
 * @param sampler_path  path to the texture atlas.
 * @return true if the arguments were parsed successfully and false if the
 * user asked for help and the program should exit.
 * @throws std::invalid_argument if the arguments are invalid.
 */
static bool parse_args(int argc, char **argv, std::size_t &bkgd_dim,
                       std::string &sampler_path);

int main(int argc, char **argv)
{
    std::size_t bkgd_dim;
    std::string sampler_path;
    if (!parse_args(argc, argv, bkgd_dim, sampler_path))
        exit(1);

    float proj_xx, proj_yy;
    GLFWwindow *window = init(proj_xx, proj_yy);

    mat4 screen_matrix{{
                           proj_xx, 0.f, 0.f, 0.f,
                           0.f, proj_yy, 0.f, 0.f,
                           0.f, 0.f, 1.f, 0.f,
                           0.f, 0.f, 0.f, 1.f
                       }};

    game::tetris game(window);
    sampler tex_atlas(sampler_path);
    tex_atlas.bind();

    mesh::bkgd bkgd(tex_atlas, game.level());
    mesh::frame frame(tex_atlas);
    mesh::board board(tex_atlas, game.board());
    mesh::active active_piece(tex_atlas, game.active_piece(), game.level(),
        game.state(), game.frame_num());
    mesh::next next_piece(tex_atlas, game.next());
    mesh::number numbers(tex_atlas, game.level(), game.clk(), game.score(), game.grade());
    mesh::dim dim_board(tex_atlas, bkgd_dim);

    shader program;
    program.bind();
    program.uniform("tex", 0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        try
        {
            game.tick();
        }
        catch (game::game_over_exception &e)
        {
            std::cout << "Game over" << std::endl;
            while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
            {
                glfwWaitEvents();
            }
            // close window
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        program.uniform("transform", shader::I);
        program.uniform("u_screen", shader::I);
        bkgd.draw();

        program.uniform("u_screen", screen_matrix);
        program.uniform("transform", shader::J);
        dim_board.draw();

        if (game.update())
        {
            board.update();
            game.update(false);
        }

        board.draw();
        active_piece.draw();
        next_piece.update(game.next());
        next_piece.draw();

        program.uniform("transform", shader::I);
        numbers.draw();
        frame.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

class window_exception : public std::exception
{
public:
    explicit window_exception(std::string msg) : msg(std::move(msg))
    {}

    [[nodiscard]] const char *what() const noexcept override
    { return msg.c_str(); }

private:
    std::string msg;
};

static GLFWwindow *init(float &proj_xx, float &proj_yy)
{
    if (!glfwInit())
        throw window_exception("Failed to initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_SUBVERSION);

    GLFWmonitor *primary_monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(primary_monitor);

    GLFWwindow *window = glfwCreateWindow(mode->width, mode->height,
        "Tetris the Grand Master I (Palmer Edition)", primary_monitor, nullptr);

    if (!window)
    {
        glfwTerminate();
        throw window_exception("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        throw window_exception("Failed to initialized OpenGL through GLEW");
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSwapInterval(1);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    int width = mode->width * EMULATED_HEIGHT;
    int height = mode->height * EMULATED_WIDTH;

    proj_xx = height > width ? 1.f : (float) height / (float) width;
    proj_yy = width > height ? 1.f : (float) width / (float) height;

    return window;
}

static bool parse_args(int argc, char **argv, std::size_t &bkgd_dim,
                       std::string &sampler_path)
{
    if (argc == 1)
    {
        bkgd_dim = 4;
        sampler_path = DEFAULT_SAMPLER_PATH;
        return true;
    }
    else if (argc == 2)
    {
        if (strlen(argv[1]) == 1)
        {
            bkgd_dim = std::stoul(argv[1]);
            sampler_path = DEFAULT_SAMPLER_PATH;
            return true;
        }
        else if (strcmp(argv[1], "--help") == 0 or strcmp(argv[1], "-h") == 0)
        {
            std::cout << "Usage: " << argv[0]
                      << " [transparency (0 to 9)] [sampler_path]" << std::endl;
            return false;
        }
        else
        {
            sampler_path = argv[1];
            bkgd_dim = 4;
            return true;
        }
    }
    else if (argc == 3)
    {
        bkgd_dim = std::stoul(argv[1]);
        sampler_path = argv[2];
        return true;
    }
    else
    {
        throw std::invalid_argument(
            "Arguments to the program invalid. Use --help or -h for help");
    }
}
