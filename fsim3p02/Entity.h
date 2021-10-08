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
    
    void initialize(Material* _material);

    void moveEntity();
    void renderEntity(std::unique_ptr<Shader> & shader);

    Model* getModel();
    MotionPlan* getMotionPlan();

private:
    Model model;
    MotionPlan motionPlan;
    Material* material;
};

