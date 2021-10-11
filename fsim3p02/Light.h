#pragma once
#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Motion.h"

class Light
{
public:
    Light();
    ~Light();

    void initialize(
        std::shared_ptr<Motion> _motion,
        GLfloat red, GLfloat green, GLfloat blue,
        GLfloat _ambientIntensity, GLfloat _diffuseIntensity);

    bool getNewPosition(glm::vec3 old_position, glm::vec3 & new_position);
    bool getNewDirection(glm::vec3 old_direction, glm::vec3 & new_direction);
    void UseLight(GLuint colourLocation, GLuint ambientIntensityLocation, GLuint diffuseIntensityLocation);

protected:
    std::shared_ptr<Motion> motion;
    glm::vec3 colour;
    GLfloat ambientIntensity;
    GLfloat diffuseIntensity;
};

