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
    std::shared_ptr<Shader> getShader(size_t index);

private:
    std::string vertex_code_path;
    std::string fragment_code_path;
    std::vector<std::shared_ptr<Shader>> shaderList;
};

