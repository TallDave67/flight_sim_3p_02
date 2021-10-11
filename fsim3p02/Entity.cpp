#include "Entity.h"

#include <glm/gtc/type_ptr.hpp>

Entity::Entity() :
    model(nullptr), motionPlan(nullptr), material(nullptr)
{
}

Entity::~Entity()
{
}

void Entity::initialize(std::shared_ptr<Material> _material)
{
    model = std::make_shared<Model>();
    motionPlan = std::make_shared<MotionPlan>();
    material = _material;
}

void Entity::moveEntity()
{
    if (motionPlan)
    {
        motionPlan->move();
    }

}

void Entity::renderEntity(std::shared_ptr<Shader> shader)
{
    if (model)
    {
        glm::mat4 model_matrix(1.0f);
        if (motionPlan)
        {
            Motion* motion = motionPlan->get_motion();
            if (motion)
            {
                motion->apply_translation(model_matrix);
                motion->apply_rotation(model_matrix);
                motion->apply_scaling(model_matrix);
            }
        }
        glUniformMatrix4fv(shader->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model_matrix));
        if (material)
        {
            material->UseMaterial(shader->GetSpecularIntensityLocation(), shader->GetShininessLocation());
        }
        model->RenderModel();
    }
}

std::shared_ptr<Model> Entity::getModel()
{
    return model;
}

std::shared_ptr<MotionPlan> Entity::getMotionPlan()
{
    return motionPlan;
}

