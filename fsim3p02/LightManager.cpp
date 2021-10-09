#include "LightManager.h"

LightManager::LightManager() : 
    entityManager(nullptr), pointLightCount(0), spotLightCount(0)
{

}

LightManager::~LightManager()
{

}

void LightManager::initialize(EntityManager * _entityManager)
{
    // We need the EntityManager to connect lights to the motion of entities
    entityManager = _entityManager;

    // Create directional light
    directionalLight.initialize(
        nullptr,
        1.0f, 1.0f, 1.0f, 
        0.3f, 0.1f, 
        0.0f, 0.0f, -1.0f
    );

    // Create point lights
    pointLights[pointLightCount++].initialize(
        nullptr,
        0.0f, 0.0f, 1.0f,
        0.6f, 0.1f,
        0.0f, 1.1f, -5.0f,
        0.3f, 0.1f, 0.1f
    );
    pointLights[pointLightCount++].initialize(
        nullptr,
        0.0f, 0.0f, 1.0f,
        0.7f, 1.0f,
        -4.0f, 2.0f, 4.0f,
        0.3f, 0.1f, 0.1f
    );
    pointLights[pointLightCount++].initialize(
        nullptr,
        0.0f, 0.0f, 1.0f,
        0.7f, 1.0f,
        0.0f, 8.0f, -4.0f,
        0.3f, 0.1f, 0.1f
    );

    // Create spot lights
    spotLights[spotLightCount++].initialize(
        entityManager->getEntity(1)->getMotionPlan()->get_motion(),
        1.0f, 1.0f, 1.0f,
        2.0f, 0.2f,
        -2.3f, 1.0f, -4.7f,
        0.3f, 0.2f, 0.1f,
        0.0f, 0.0f, -1.0f, 0.71f
    );
    ;
    spotLights[spotLightCount++].initialize(
        entityManager->getEntity(1)->getMotionPlan()->get_motion(),
        1.0f, 1.0f, 1.0f,
        2.0f, 0.2f,
        -2.3f, 1.0f, -4.7f,
        0.3f, 0.2f, 0.1f,
        0.0f, 0.0f, 1.0f, 0.71f
    );
}

void LightManager::moveLights()
{
    for (unsigned int i = 0; i < spotLightCount; i++)
    {
        glm::vec3 new_direction;
        if (spotLights[i].getNewDirection(spotLights[i].getDirectionStart(), new_direction))
        {
            spotLights[i].setDirection(new_direction);
        }
    }
}

void LightManager::setLights(Shader* shader)
{
    shader->SetDirectionalLight(&directionalLight);
    shader->SetPointLights(pointLights, pointLightCount);
    shader->SetSpotLights(spotLights, spotLightCount);
}

