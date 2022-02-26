#pragma once

//#include <glad.h>
//#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "GL/freeglut.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    
    // Use the shader
    void Use();

    // Utility Uniform functions
    void SetUniform(const std::string& name, bool value) const;
    void SetUniform(const std::string& name, int value) const;
    void SetUniform(const std::string& name, float value) const;
    void SetUniform(const std::string& name, const glm::vec2& value) const;
    void SetUniform(const std::string& name, float x, float y) const;
    void SetUniform(const std::string& name, const glm::vec3& value) const;
    void SetUniform(const std::string& name, float x, float y, float z) const;
    void SetUniform(const std::string& name, const glm::vec4& value) const;
    void SetUniform(const std::string& name, float x, float y, float z, float w);
    void SetUniform(const std::string& name, const glm::mat2& mat) const;
    void SetUniform(const std::string& name, const glm::mat3& mat) const;
    void SetUniform(const std::string& name, const glm::mat4& mat) const;

private:
    // Utility function for checking shader compilation/linking errors.
    void CheckCompileErrors(GLuint shader, std::string type);
};