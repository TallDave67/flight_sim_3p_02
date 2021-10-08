#include "LightManager.h"

LightManager::LightManager() : 
    pointLightCount(0), spotLightCount(0)
{

}

LightManager::~LightManager()
{

}

void LightManager::initialize()
{
    // Create directional light
    directionalLight.initialize(
        1.0f, 1.0f, 1.0f, 
        0.3f, 0.1f, 
        0.0f, 0.0f, -1.0f
    );

    // Create point lights
    pointLights[pointLightCount++].initialize(
        0.0f, 0.0f, 1.0f,
        0.6f, 0.1f,
        0.0f, 1.1f, -5.0f,
        0.3f, 0.1f, 0.1f
    );
    pointLights[pointLightCount++].initialize(
        0.0f, 0.0f, 1.0f,
        0.7f, 1.0f,
        -4.0f, 2.0f, 4.0f,
        0.3f, 0.1f, 0.1f
    );
    pointLights[pointLightCount++].initialize(
        0.0f, 0.0f, 1.0f,
        0.7f, 1.0f,
        0.0f, 8.0f, -4.0f,
        0.3f, 0.1f, 0.1f
    );

    // Create spot lights
    spotLights[spotLightCount++].initialize(
        1.0f, 1.0f, 1.0f,
        2.0f, 0.2f,
        -4.0f, 0.5f, 3.0f,
        0.3f, 0.2f, 0.1f,
        0.0f, -1.0f, 0.0f, 0.71f
    );
    ;
    spotLights[spotLightCount++].initialize(
        1.0f, 1.0f, 1.0f,
        2.0f, 0.2f,
        -4.0f, 0.5f, 3.0f,
        0.3f, 0.2f, 0.1f,
        0.0f, 1.0f, 0.0f, 0.71f
    );

    // Motion
    spotlightMotion.initialize(1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 1.0f);
}

void LightManager::moveLights()
{
    spotlightMotion.compute_incremental_rotation(DIRECTION_NONE, DIRECTION_POSITIVE, DIRECTION_NONE);
}

void LightManager::setLights(std::unique_ptr<Shader> & shader)
{
    shader->SetDirectionalLight(&directionalLight);
    shader->SetPointLights(pointLights, pointLightCount);
    //
    spotLights[0].setDirection(spotlightMotion.get_direction(glm::vec3(0.0f, 0.0f, 0.0001f)));
    spotLights[1].setDirection(-spotlightMotion.get_direction(glm::vec3(0.0f, 0.0f, 0.0001f)));
    shader->SetSpotLights(spotLights, spotLightCount);
}

