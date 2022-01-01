#pragma once

#include <string>
#include <unordered_map>

using mat3 = std::array<float, 9>;
using mat4 = std::array<float, 16>;

/**
 * @brief rendering all objects in tetris only requires one shader. The shader
 * source code is provided in the definition of the constructor.
 */
class shader 
{
public:
    static constexpr mat4 I {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    static constexpr mat4 J {
        0.05f,  0.0f,           0.0f, 0.0f,
        0.0f,   -1.0f/15.0f,    0.0f, 0.0f,
        0.0f,   0.0f,           1.0f, 0.0f,
        -0.25f, -11.0f/15.0f,   0.0f, 1.0f
    };

    shader();

    ~shader();

    /**
     * @brief Set the uniform value of the shader. 
     * @requires The shader to be already bound.
     * 
     * @details to avoid the overhead of calling glGetUniformLocation() every
     * time, the uniform location is stored in the map. If the uniform is not
     * found in the map, it is added to the map and the location is retrieved
     * from OpenGL.
     * 
     * @param name the name of the uniform.
     * @param value the value of the uniform.
     */
    void uniform(const char *name, int value) const;

    void uniform(const char *name, const mat3 &value) const;

    void uniform(const char *name, const mat4 &value) const;

    
    /**
     * @brief Bind the shader to be used as the active program.
     */
    void bind() const noexcept;
    
    /**
     * @brief Unbind the shader by binding the active program to 0, which 
     * represents nothing.
     */
    void unbind() const noexcept;

private:
    /**
     * @brief The shader program id.
     */
    unsigned int id_;

    /**
     * @brief The map of known uniform locations.
     */
    mutable std::unordered_map<std::string, int> uniforms_;

    /**
     * @brief Compile and link the shader to the active program.
     * 
     * @param type the type of the shader specified by OpenGL.
     * @param source the source code of the shader.
     * @return the id of the shader specified by OpenGL.
     */
    unsigned int compile(unsigned int type, const char *source);
};
