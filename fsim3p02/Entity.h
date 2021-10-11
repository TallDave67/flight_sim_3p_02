#pragma once

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

    Model* getModel();
    MotionPlan* getMotionPlan();

private:
    Model model;
    MotionPlan motionPlan;
    std::shared_ptr<Material> material;
};

