#pragma once
#include <memory>

#include "Constants.h"
#include "EntityManager.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Shader.h"

class LightManager
{
public:
    LightManager();
    ~LightManager();

    void initialize(std::shared_ptr<EntityManager> _entityManager);

    void moveLights();
    void setLights(std::shared_ptr<Shader>);

private:
    std::shared_ptr<EntityManager> entityManager;
    DirectionalLight directionalLight;
    PointLight pointLights[MAX_POINT_LIGHTS];
    SpotLight spotLights[MAX_SPOT_LIGHTS];

    unsigned int pointLightCount;
    unsigned int spotLightCount;
};

