#include "common.hpp"

void inputs::update()
{
    bool k_left_pressed = (glfwGetKey(window, K_LEFT) == GLFW_PRESS);
    bool k_down_pressed = (glfwGetKey(window, K_DOWN) == GLFW_PRESS);
    bool k_right_pressed = (glfwGetKey(window, K_RIGHT) == GLFW_PRESS);

    if (k_left_pressed && !k_right_pressed)
    {
        shift_ = shift::left;
    }
    else if (k_right_pressed && !k_left_pressed)
    {
        shift_ = shift::right;
    }
    else if (k_down_pressed)
    {
        shift_ = shift::down;
    }
    else
    {
        shift_ = shift::none;
    }

    bool k_ccw1_pressed = (glfwGetKey(window, K_CCW1) == GLFW_PRESS);
    bool k_cw_pressed = (glfwGetKey(window, K_CW) == GLFW_PRESS);
    bool k_ccw2_pressed = (glfwGetKey(window, K_CCW2) == GLFW_PRESS);

    if ((k_ccw1_pressed && !prev_k_ccw1_pressed) ||
        (k_ccw2_pressed && !prev_k_ccw2_pressed))
    {
        rotation_ = rotation::ccw_d;
    }
    else if (k_cw_pressed && !prev_k_cw_pressed)
    {
        rotation_ = rotation::cw_d;
    }
    else if (k_ccw1_pressed || k_ccw2_pressed)
    {
        rotation_ = rotation::ccw_p;
    }
    else if (k_cw_pressed)
    {
        rotation_ = rotation::cw_p;
    }
    else
    {
        rotation_ = rotation::none;
    }

    prev_k_ccw1_pressed = k_ccw1_pressed;
    prev_k_cw_pressed = k_cw_pressed;
    prev_k_ccw2_pressed = k_ccw2_pressed;
}

void inputs::get(shift &s, rotation &r)
{
    s = shift_;
    r = rotation_;
}
