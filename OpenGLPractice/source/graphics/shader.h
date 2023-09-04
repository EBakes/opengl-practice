#pragma once

#include <iostream>

#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const char* vertexSrc, const char* fragmentSrc);
    void Use();

    void SetBool(const std::string &name, bool val) const;
    void SetInt(const std::string &name, int val) const;
    void SetFloat(const std::string &name, float val) const;

    void SetVec2(const std::string &name, const glm::vec2& val) const;
    void SetVec2(const std::string &name, float x, float y) const;
    void SetVec3(const std::string &name, const glm::vec3& val) const;
    void SetVec3(const std::string &name, float x, float y, float z) const;
    void SetVec4(const std::string &name, const glm::vec4& val) const;
    void SetVec4(const std::string &name, float x, float y, float z, float w) const;
    void SetMat2(const std::string &name, const glm::mat2& mat) const;
    void SetMat3(const std::string &name, const glm::mat3& mat) const;
    void SetMat4(const std::string &name, const glm::mat4& mat) const;

    unsigned int GetUniformLocation(const std::string &name) const;

private:
    unsigned int _prgId;
};