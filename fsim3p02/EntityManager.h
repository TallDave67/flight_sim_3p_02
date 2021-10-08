#pragma once
#include <vector>
#include <memory>

#include "Entity.h"
#include "Material.h"
#include "Shader.h"

class EntityManager
{
public:
    EntityManager();
    ~EntityManager();

    void initialize();

    Material* addMaterial();
    Material* getMaterial(size_t index);

    Entity* addEntity();
    void moveEntities();
    void renderEntities(std::unique_ptr<Shader> & shader);
    
private:
    std::vector<std::unique_ptr<Material>> materialList;
    std::vector<std::unique_ptr<Entity>> entityList;
};

