#include "common.hpp"

shift_t inputs::get_shift()
{
    bool k_left_pressed = (glfwGetKey(window, K_LEFT) == GLFW_PRESS);
    bool k_down_pressed = (glfwGetKey(window, K_DOWN) == GLFW_PRESS);
    bool k_right_pressed = (glfwGetKey(window, K_RIGHT) == GLFW_PRESS);

    shift_t shift;

    if (k_left_pressed and !k_right_pressed)
    {
        shift = shift_t::left;
    }
    else if (k_right_pressed and !k_left_pressed)
    {
        shift = shift_t::right;
    }
    else if (k_down_pressed)
    {
        shift = shift_t::down;
    }
    else
    {
        shift = shift_t::none;
    }

    if (shift == shift_t::down or shift == shift_t::none or shift != prev_shift)
    {
        das = 0;
    }
    else if (shift == prev_shift)
    {
        das++;
    }

    prev_shift = shift;

    return (das == 0 or das == DAS) ? shift : shift_t::none;
}

rotation_t inputs::get_rotation(bool spawn_frame)
{
    if (spawn_frame)
    {
        prev_k_ccw1_pressed = false;
        prev_k_cw_pressed = false;
        prev_k_ccw2_pressed = false;
    }

    bool k_ccw1_pressed = (glfwGetKey(window, K_CCW1) == GLFW_PRESS);
    bool k_cw_pressed = (glfwGetKey(window, K_CW) == GLFW_PRESS);
    bool k_ccw2_pressed = (glfwGetKey(window, K_CCW2) == GLFW_PRESS);

    rotation_t rotation;

    if ((k_ccw1_pressed and !prev_k_ccw1_pressed) or
        (k_ccw2_pressed and !prev_k_ccw2_pressed))
    {
        rotation = rotation_t::ccw;
    }
    else if (k_cw_pressed and !prev_k_cw_pressed)
    {
        rotation = rotation_t::cw;
    }
    else
    {
        rotation = rotation_t::none;
    }

    prev_k_ccw1_pressed = k_ccw1_pressed;
    prev_k_cw_pressed = k_cw_pressed;
    prev_k_ccw2_pressed = k_ccw2_pressed;

    return rotation;
}

