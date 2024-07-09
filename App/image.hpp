#pragma once
//https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples#example-for-opengl-users
#include <iostream>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "logger.hpp"

class Image
{
public:
    enum class Format { None, RGBA, RGBA32F };
private:
    std::string m_filename;
    Format m_format = Format::None;
    int32_t m_width = 0;
    int32_t m_height = 0;
    float m_ratio = 0.0f;
    GLuint m_textureID = 0;
private:

    void LoadTexture()
    {
        // Load from file
        //TODO: REPLACE RAW POINTERS TO SMART POINTERS
        unsigned char* image_data = stbi_load(m_filename.data(), &m_width, &m_height, NULL, 4);
        if (!image_data) {
            PRINT("STBI_LOAD FAILS TO LOAD THE IMAGE");
            return;
        }

        // Create a OpenGL texture identifier
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        // Setup filtering parameters for display
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

        // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
        stbi_image_free(image_data);
    }

public:
    Image(const std::string_view filename, Format format)
        : m_filename{filename}, m_format{format}
    {
        LoadTexture();
        m_ratio = static_cast<float>(m_width) / static_cast<float>(m_height);
    }
    // Simple helper function to load an image into a OpenGL texture with common settings
    static bool LoadTextureFromFile(const std::string_view filename, GLuint* out_texture)
    {
        // Load from file
        int image_width = 0;
        int image_height = 0;
        unsigned char* image_data = stbi_load(filename.data(), &image_width, &image_height, NULL, 4);
        if (!image_data)
            return EXIT_FAILURE;

        // Create a OpenGL texture identifier
        GLuint image_texture;
        glGenTextures(1, &image_texture);
        glBindTexture(GL_TEXTURE_2D, image_texture);

        // Setup filtering parameters for display
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

        // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
        stbi_image_free(image_data);

        *out_texture = image_texture;
        return EXIT_SUCCESS;
    }

    /*
     * Getters and Setters
     */
    [[nodiscard]] inline ImTextureID ID() const { return reinterpret_cast<ImTextureID>(m_textureID); }
    [[nodiscard]] inline int32_t width() const { return m_width; }
    [[nodiscard]] inline int32_t height() const { return m_height; }
    [[nodiscard]] inline ImVec2 size() const { return ImVec2(m_width, m_height);}
    [[nodiscard]] inline float ratio() const { return m_ratio; }
    /*
     * Resize image method keeping iamge aspect ratio
     */
    [[nodiscard]] inline ImVec2 resize(const ImVec2& size) const {
        // Calculate resize ratio
        float width_ratio = (float) size.x / (float) m_width;
        float height_ratio = (float) size.y / (float) m_height;
        // Choose the smaller ratio to maintain aspect ratio
        float resize_ratio = (width_ratio < height_ratio) ? width_ratio : height_ratio;
        // Calculate new dimensions
        float target_width = (float) m_width * resize_ratio;
        float target_height = (float) m_height * resize_ratio;

        return ImVec2(target_width, target_height);
    }
};