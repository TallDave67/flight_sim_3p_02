#include "MotionCurve.h"

#include "Constants.h"

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
    glm::vec3 tangent = glm::normalize(compute_tangent_on_curve());
    //
    float angle_z = 0.0f;
    angle_z = -((PI / 2.0f) - acosf(tangent.y));
    if (tangent.x >= 0.0f)
    {
        angle_z = PI - angle_z;
    }
    //
    float angle_y = 0.0f;
    angle_y = PI + acosf(tangent.x);
    if (tangent.z >= 0.0f)
    {
        angle_y = (2 * PI) - angle_y;
    }
    //
    float angle_x = 0.0f;
    angle_x = -((PI / 2.0f) - acosf(tangent.z));
    if (tangent.y >= 0.0f)
    {
        angle_x = PI - angle_x;
    }
    rotation_matrix = glm::eulerAngleYZX(angle_y, 0.0f/*angle_z*/, 0.0f/*angle_x*/);
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
