#include "MotionCurve.h"

MotionCurve::MotionCurve() :
    num_frames(0), current_frame(0), current_t(0.0f)
{
}

MotionCurve::~MotionCurve()
{
}

unsigned int MotionCurve::reset()
{
}

bool MotionCurve::next()
{
    current_frame++;
    return current_frame <= num_frames;
}

void MotionCurve::compute_position(float speed_translate, glm::vec3& position)
{
    map_frame_to_t(speed_translate);
    position = compute_position_on_curve();
}

void MotionCurve::compute_tangent(glm::vec3& tangent)
{
    tangent = compute_tangent_on_curve();
}

void MotionCurve::map_frame_to_t(float speed_translate)
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
