#include "common.hpp"

shift_t inputs::update_shift()
{
    bool k_left_pressed = (glfwGetKey(window_, K_LEFT) == GLFW_PRESS);
    bool k_down_pressed = (glfwGetKey(window_, K_DOWN) == GLFW_PRESS);
    bool k_right_pressed = (glfwGetKey(window_, K_RIGHT) == GLFW_PRESS);

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

    if (shift == shift_t::down or shift == shift_t::none or shift != prev_shift_)
    {
        das_ = 0;
    }
    else if (shift == prev_shift_)
    {
        ++das_;
    }

    prev_shift_ = shift;

    return (das_ == 0 or das_ == DAS) ? shift : shift_t::none;
}

rotation_t inputs::update_rotation(bool spawn_frame)
{
    if (spawn_frame)
    {
        prev_k_ccw_1_pressed_ = false;
        prev_k_cw_pressed_ = false;
        prev_k_ccw_2_pressed_ = false;
    }

    bool k_ccw_1_pressed = (glfwGetKey(window_, K_CCW_1) == GLFW_PRESS);
    bool k_cw_pressed = (glfwGetKey(window_, K_CW) == GLFW_PRESS);
    bool k_ccw_2_pressed = (glfwGetKey(window_, K_CCW_2) == GLFW_PRESS);

    rotation_t rotation;

    if ((k_ccw_1_pressed and !prev_k_ccw_1_pressed_) or
        (k_ccw_2_pressed and !prev_k_ccw_2_pressed_))
    {
        rotation = rotation_t::ccw;
    }
    else if (k_cw_pressed and !prev_k_cw_pressed_)
    {
        rotation = rotation_t::cw;
    }
    else
    {
        rotation = rotation_t::none;
    }

    prev_k_ccw_1_pressed_ = k_ccw_1_pressed;
    prev_k_cw_pressed_ = k_cw_pressed;
    prev_k_ccw_2_pressed_ = k_ccw_2_pressed;

    return rotation;
}
