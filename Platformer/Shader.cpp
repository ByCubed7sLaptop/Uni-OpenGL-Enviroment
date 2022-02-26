#include "Shader.h"

//#define VERBOSE

#include <glad.h>
#include <GLFW/glfw3.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
    // 1. LOAD SHADERS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#ifdef VERBOSE
    std::cout << "Shader :: LOADING SHADER" << std::endl;
#endif


#ifdef VERBOSE
    std::cout << "Shader :: Setting up shader file loader" << std::endl;
#endif
    std::ifstream shaderFile;
    // Ensure shaderFile can throw exceptions:
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // Load Vertex Shader Code
    std::string vertexCode;
    if (vertexPath != nullptr) 
    {
        try
        {
            shaderFile.open(vertexPath);
            std::stringstream vShaderStream;
            vShaderStream << shaderFile.rdbuf();
            shaderFile.close();
            vertexCode = vShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::VERTEX::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
        }
    }
    // else error

    // Load Fragment Shader Code
    std::string fragmentCode;
    if (fragmentPath != nullptr)
    {
        try
        {
            shaderFile.open(fragmentPath);
            std::stringstream fShaderStream;
            fShaderStream << shaderFile.rdbuf();
            shaderFile.close();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FRAGMENT::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
        }
    }
    // else error

    // Load Geometry Shader Code
    std::string geometryCode;
    if (geometryPath != nullptr)
    {
        try
        {
            shaderFile.open(geometryPath);
            std::stringstream gShaderStream;
            gShaderStream << shaderFile.rdbuf();
            shaderFile.close();
            geometryCode = gShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::GEOMETRY::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
        }
    }

    // 2. COMPILE SHADERS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    //*
    unsigned int vertex;
    if (vertexPath != nullptr)
    {
        const char* vShaderCode = vertexCode.c_str();
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        CheckCompileErrors(vertex, "VERTEX");
    }
    else std::cerr << "VertexPath is nullptr!" << std::endl;
    

    unsigned int fragment;
    if (fragmentPath != nullptr)
    {
        const char* fShaderCode = fragmentCode.c_str();
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        CheckCompileErrors(fragment, "FRAGMENT");
    }
    else std::cerr << "FragmentPath is nullptr!" << std::endl;

    unsigned int geometry;
    if (geometryPath != nullptr)
    {
        const char* gShaderCode = geometryCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        CheckCompileErrors(geometry, "GEOMETRY");
    }

    // 3. LINK PROGRAM - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Shader Program
    ID = glCreateProgram();
    if (vertexPath   != nullptr) glAttachShader(ID, vertex);
    if (fragmentPath != nullptr) glAttachShader(ID, fragment);
    if (geometryPath != nullptr) glAttachShader(ID, geometry);
    
    glLinkProgram(ID);
    CheckCompileErrors(ID, "PROGRAM");
    
    
    // 4. CLEAN UP - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // Delete the shaders as they're linked into our program now and no longer necessery
    if (vertexPath   != nullptr) glDeleteShader(vertex);
    if (fragmentPath != nullptr) glDeleteShader(fragment);
    if (geometryPath != nullptr) glDeleteShader(geometry);
}

void Shader::Use()
{
    glUseProgram(ID);
}

void Shader::SetUniform(const std::string& name, bool value) const { glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); } // setBool
void Shader::SetUniform(const std::string& name, int value) const { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); } // setInt
void Shader::SetUniform(const std::string& name, float value) const { glUniform1f(glGetUniformLocation(ID, name.c_str()), value); } // setFloat
void Shader::SetUniform(const std::string& name, const glm::vec2& value) const { glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); } // setVec2
void Shader::SetUniform(const std::string& name, float x, float y) const { glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); } // setVec2
void Shader::SetUniform(const std::string& name, const glm::vec3& value) const { glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); } // setVec3
void Shader::SetUniform(const std::string& name, float x, float y, float z) const { glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); } // setVec3
void Shader::SetUniform(const std::string& name, const glm::vec4& value) const { glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); } // setVec4
void Shader::SetUniform(const std::string& name, float x, float y, float z, float w) { glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); } // setVec4
void Shader::SetUniform(const std::string& name, const glm::mat2& mat) const { glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); } // setMat2
void Shader::SetUniform(const std::string& name, const glm::mat3& mat) const { glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); } // setMat3
void Shader::SetUniform(const std::string& name, const glm::mat4& mat) const { glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); } // setMat4


void Shader::CheckCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
