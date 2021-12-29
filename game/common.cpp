#include "common.hpp"

void inputs::update()
{
    bool k_left_pressed = (glfwGetKey(window, K_LEFT) == GLFW_PRESS);
    bool k_down_pressed = (glfwGetKey(window, K_DOWN) == GLFW_PRESS);
    bool k_right_pressed = (glfwGetKey(window, K_RIGHT) == GLFW_PRESS);

    if (k_left_pressed && !k_right_pressed)
    {
        shift_ = shift_t::left;
    }
    else if (k_right_pressed && !k_left_pressed)
    {
        shift_ = shift_t::right;
    }
    else if (k_down_pressed)
    {
        shift_ = shift_t::down;
    }
    else
    {
        shift_ = shift_t::none;
    }

    bool k_ccw1_pressed = (glfwGetKey(window, K_CCW1) == GLFW_PRESS);
    bool k_cw_pressed = (glfwGetKey(window, K_CW) == GLFW_PRESS);
    bool k_ccw2_pressed = (glfwGetKey(window, K_CCW2) == GLFW_PRESS);

    if ((k_ccw1_pressed && !prev_k_ccw1_pressed) ||
        (k_ccw2_pressed && !prev_k_ccw2_pressed))
    {
        rotation_ = rotation_t::ccw_d;
    }
    else if (k_cw_pressed && !prev_k_cw_pressed)
    {
        rotation_ = rotation_t::cw_d;
    }
    else if (k_ccw1_pressed || k_ccw2_pressed)
    {
        rotation_ = rotation_t::ccw_p;
    }
    else if (k_cw_pressed)
    {
        rotation_ = rotation_t::cw_p;
    }
    else
    {
        rotation_ = rotation_t::none;
    }

    prev_k_ccw1_pressed = k_ccw1_pressed;
    prev_k_cw_pressed = k_cw_pressed;
    prev_k_ccw2_pressed = k_ccw2_pressed;
}

void inputs::get(shift_t &shift, rotation_t &rotation) const 
{
    shift = shift_;
    rotation = rotation_;
}
