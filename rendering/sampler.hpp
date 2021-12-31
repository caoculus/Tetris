#pragma once

#include <string>
#include <unordered_map>
#include <vector>

/**
 * @brief sample textures from a .png texture atlas, alongside the layout of 
 * the texture atlas in a .layout file, to be used in the game.
 * 
 * @warning The .layout file MUST have the same filename as the .png file, but 
 * with the extension .layout instead of .png.
 * 
 * @note The .layout file is a text file with the following format:
 * 
 */
class sampler
{
private:
    /**
     * @brief To obtain the normalized texture coordinates (between 0 and 1),
     * this struct would be returned by the sampler. Nx and Ny for the negative
     * x and y vertices of the rect, and Px and Py for the positive x and y 
     * vertices of the rect. 
     */
    struct tex_rect
    {
        float Nx, Py, Px, Ny;
    };

public:
    sampler(const std::string &_global_texture_atlas_path);

    ~sampler();

    /**
     * @brief binds the texture atlas to the given texture slot in OpenGL.
     * 
     * @param slot the slot to bind the texture atlas to. Default is 0.
     */
    void bind(unsigned int slot = 0) const noexcept;

    /**
     * @brief unbind the texture atlas from the given texture slot in OpenGL.
     */
    void unbind() const noexcept;

    /**
     * @brief Obtain the normalized texture coordinates for a given object in
     * the game stored in the texture atlas.
     * 
     * @param thing the name of the object in the game.
     * @throws out_of_range exception if the thing is wrong.
     * @param index the index, only if there are multiple objects of the same 
     * name.
     * @throws out_of_range exception if the index is out of range.
     * @return tex_rect the normalized texture coordinates for the given object.
     */
    tex_rect operator() (const std::string &thing, std::size_t index=0) const;

    /** 
     * @return the width of the texture atlas.
     */
    constexpr std::size_t width() const { return width_; }

    /**
     * @return the height of the texture atlas.
     */
    constexpr std::size_t height() const { return height_; }

private:
    /**
     * @brief The width and height of the texture atlas.
     */
    std::size_t width_, height_;

    /**
     * @brief the map between the objects and their normalized texture
     * coordinates, which are read from the layout file. 
     */
    std::unordered_map<std::string, std::vector<tex_rect>> locs_;

    /**
     * @brief the OpenGL id of the texture unit. 
     */
    unsigned int id_;

    /**
     * @brief load the locations of objects into the map so they can be
     * referenced by the renderer.
     * 
     * @param _atlas_layout_path the path to the layout file.
     */
    void load_atlas(const std::string &_atlas_layout_path);

    /**
     * @brief load the texture into OpenGL to be used by the renderer.
     * 
     * @param _global_texture_atlas_path the path to the texture atlas.
     * @pre the image must be a .png file.
     */
    void load_texture(const std::string &_global_texture_atlas_path);
};

/**
 * @brief exception that is thrown when there is some problem preventing the
 * texture image from loading.
 */
class texture_loading_error : public std::exception
{
public:
    texture_loading_error(const std::string &_msg)
        : msg(_msg) {}

    const char *what() const noexcept override { return msg.c_str(); }
private:
    std::string msg;
};

/**
 * @brief exception that is thrown when there is some problem preventing the
 * layout of the texture atlas to be parsed. 
 */
class layout_parsing_error : public std::exception
{
public:
    layout_parsing_error(const std::string &line, std::size_t index);
    layout_parsing_error(const std::string &read_failure);

    const char *what() const noexcept override { return msg.c_str(); }
private:
    std::string msg;
};
