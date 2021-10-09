#include "Light.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

Light::Light() :
    motion(nullptr), colour(1.0f, 1.0f, 1.0f), ambientIntensity(1.0),  diffuseIntensity(0.0f)
{
}

Light::~Light()
{
}

void Light::initialize(
    Motion* _motion,
    GLfloat red, GLfloat green, GLfloat blue,
    GLfloat _ambientIntensity, GLfloat _diffuseIntensity)
{
    motion = _motion;
    colour = glm::vec3(red, green, blue);
    ambientIntensity = _ambientIntensity;
    diffuseIntensity = _diffuseIntensity;
}

void Light::UseLight(GLuint colourLocation, GLuint ambientIntensityLocation, GLuint diffuseIntensityLocation)
{
    glUniform3f(colourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}
