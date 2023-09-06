#include "shader.h"

#include <glad/glad.h>

Shader::Shader(const char* vertexSrc, const char* fragmentSrc) {
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSrc, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512] = {0};
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    _prgId = glCreateProgram();
    glAttachShader(_prgId, vertexShader);
    glAttachShader(_prgId, fragmentShader);
    glLinkProgram(_prgId);
    glGetShaderiv(_prgId, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(_prgId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
void Shader::Use()
{
    glUseProgram(_prgId);
}

void Shader::SetBool(const std::string &name, bool val) const
{
    glUniform1i(glGetUniformLocation(_prgId, name.c_str()), (int)val);
}
void Shader::SetInt(const std::string &name, int val) const
{
    glUniform1i(glGetUniformLocation(_prgId, name.c_str()), val);
}
void Shader::SetFloat(const std::string &name, float val) const
{
    glUniform1f(glGetUniformLocation(_prgId, name.c_str()), val);
}
void Shader::SetVec2(const std::string &name, const glm::vec2& val) const
{
    glUniform2fv(GetUniformLocation(name.c_str()), 1, &val[0]);
}
void Shader::SetVec2(const std::string &name, float x, float y) const
{
    glUniform2f(GetUniformLocation(name.c_str()), x, y);
}
void Shader::SetVec3(const std::string &name, const glm::vec3& val) const
{
    glUniform3fv(GetUniformLocation(name.c_str()), 1, &val[0]);
}
void Shader::SetVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(GetUniformLocation(name.c_str()), x, y, z);
}
void Shader::SetVec4(const std::string &name, const glm::vec4& val) const
{
    glUniform4fv(GetUniformLocation(name.c_str()), 1, &val[0]);
}
void Shader::SetVec4(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(GetUniformLocation(name.c_str()), x, y, z, w);
}
void Shader::SetMat2(const std::string &name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(GetUniformLocation(name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::SetMat3(const std::string &name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(GetUniformLocation(name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::SetMat4(const std::string &name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(GetUniformLocation(name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

unsigned int Shader::GetUniformLocation(const std::string& name) const
{
    return glGetUniformLocation(_prgId, name.c_str());
}