#pragma once
#include <vector>
#include <memory>

#include "Shader.h"

class ShaderManager
{
public:
    ShaderManager();
    ~ShaderManager();

    void initialize();

    void useShader(size_t index);
    Shader* getShader(size_t index);

private:
    std::string vertex_code_path;
    std::string fragment_code_path;
    std::vector<std::unique_ptr<Shader>> shaderList;
};

