#pragma once

#include "Constants.h"
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

    void initialize();

    void moveLights();
    void setLights(Shader*);

private:
    DirectionalLight directionalLight;
    PointLight pointLights[MAX_POINT_LIGHTS];
    SpotLight spotLights[MAX_SPOT_LIGHTS];

    unsigned int pointLightCount;
    unsigned int spotLightCount;

    Motion spotlightMotion;
};

