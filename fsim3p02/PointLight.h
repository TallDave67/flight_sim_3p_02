#pragma once

#include "Light.h"

class PointLight : public Light
{
public:
    PointLight();
    ~PointLight();

    void initialize(
        std::shared_ptr<Motion> _motion,
        GLfloat red, GLfloat green, GLfloat blue,
        GLfloat _ambientIntensity, GLfloat _diffuseIntensity,
        GLfloat x, GLfloat y, GLfloat z,
        GLfloat _constant,  GLfloat _linear, GLfloat _exponent);

    void UseLight(
        GLuint colourLocation, GLuint ambientIntensityLocation, GLuint diffuseIntensityLocation,
        GLuint positionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation);

    void setPosition(glm::vec3 _position);
    glm::vec3 getPosition();
    glm::vec3 getPositionStart();

protected:
    glm::vec3 position;
    glm::vec3 position_start;
    GLfloat constant;
    GLfloat linear;
    GLfloat exponent;
};

