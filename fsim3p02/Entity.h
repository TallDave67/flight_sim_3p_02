#pragma once

#include <memory>

#include "Model.h"
#include "MotionPlan.h"
#include "Material.h"
#include "Shader.h"

class Entity
{
public:
    Entity();
    ~Entity();
    
    void initialize(std::shared_ptr<Material> _material);

    void moveEntity();
    void renderEntity(std::shared_ptr<Shader>);

    std::shared_ptr<Model> getModel();
    std::shared_ptr<MotionPlan> getMotionPlan();

private:
    std::shared_ptr<Model> model;
    std::shared_ptr<MotionPlan> motionPlan;
    std::shared_ptr<Material> material;
};

