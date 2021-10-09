#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Motion.h"

class Light
{
public:
    Light();
    ~Light();

    void initialize(
        Motion* _motion,
        GLfloat red, GLfloat green, GLfloat blue,
        GLfloat _ambientIntensity, GLfloat _diffuseIntensity);

    void UseLight(GLuint colourLocation, GLuint ambientIntensityLocation, GLuint diffuseIntensityLocation);

protected:
    Motion* motion;
    glm::vec3 colour;
    GLfloat ambientIntensity;
    GLfloat diffuseIntensity;
};

