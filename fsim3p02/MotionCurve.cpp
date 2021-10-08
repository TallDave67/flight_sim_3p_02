#include "MotionCurve.h"

MotionCurve::MotionCurve() :
    num_frames(0), current_frame(0), current_t(0.0f)
{
}

MotionCurve::~MotionCurve()
{
}

void MotionCurve::initialize(float speed_translate)
{
}

unsigned int MotionCurve::reset()
{
    current_frame = 0;
    return num_frames;
}

bool MotionCurve::next()
{
    current_frame++;
    return current_frame <= num_frames;
}

void MotionCurve::compute_position( glm::vec3 & position)
{
    map_frame_to_t();
    position = compute_position_on_curve();
}

void MotionCurve::compute_rotation_matrix(glm::tmat4x4<float> & rotation_matrix)
{
    glm::vec3 tangent = compute_tangent_on_curve();
    float elevation = asinf(tangent.y);
    float azimuth = asinf(tangent.x / cosf(elevation));
    rotation_matrix = glm::eulerAngleYZX(glm::radians(azimuth), glm::radians(elevation), glm::radians(0.0f));
}

void MotionCurve::map_frame_to_t()
{
    current_t = 0.0f;
}

glm::vec3 MotionCurve::compute_position_on_curve()
{
    return glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 MotionCurve::compute_tangent_on_curve()
{
    return glm::vec3(0.0f, 0.0f, 0.0f);
}
