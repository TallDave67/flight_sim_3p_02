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

    std::shared_ptr<Material> addMaterial();
    std::shared_ptr<Material> getMaterial(size_t index);

    std::shared_ptr<Entity> addEntity();
    std::shared_ptr<Entity> getEntity(size_t index);

    void moveEntities();
    void renderEntities(std::shared_ptr<Shader>);
    
private:
    std::vector<std::shared_ptr<Material>> materialList;
    std::vector<std::shared_ptr<Entity>> entityList;
};

