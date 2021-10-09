#pragma once

#include "Constants.h"
#include "EntityManager.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Motion.h"
#include "Shader.h"

class LightManager
{
public:
    LightManager();
    ~LightManager();

    void initialize(EntityManager * _entityManager);

    void moveLights();
    void setLights(Shader*);

private:
    EntityManager* entityManager;
    DirectionalLight directionalLight;
    PointLight pointLights[MAX_POINT_LIGHTS];
    SpotLight spotLights[MAX_SPOT_LIGHTS];

    unsigned int pointLightCount;
    unsigned int spotLightCount;

    Motion spotlightMotion;
};

