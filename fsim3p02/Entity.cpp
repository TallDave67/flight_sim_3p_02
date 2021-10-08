#include "Entity.h"

#include <glm/gtc/type_ptr.hpp>

Entity::Entity() :
    material(nullptr)
{
}

Entity::~Entity()
{
}

void Entity::initialize(Material* _material)
{
    material = _material;
}

void Entity::moveEntity()
{
    motionPlan.move();
}

void Entity::renderEntity(Shader* shader)
{
    glm::mat4 model_matrix(1.0f);
    Motion* motion = motionPlan.get_motion();
    motion->apply_translation(model_matrix);
    motion->apply_rotation(model_matrix);
    motion->apply_scaling(model_matrix);
    glUniformMatrix4fv(shader->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model_matrix));
    if (material)
    {
        material->UseMaterial(shader->GetSpecularIntensityLocation(), shader->GetShininessLocation());
    }
    model.RenderModel();
}

Model* Entity::getModel()
{
    return &model;
}

MotionPlan* Entity::getMotionPlan()
{
    return &motionPlan;
}

