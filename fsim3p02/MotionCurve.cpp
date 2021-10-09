#include "MotionCurve.h"

#include "Constants.h"
#include "quaternion_utils.hpp"

MotionCurve::MotionCurve() :
    num_frames(0), current_frame(0), current_t(0.0f), last_position(0.0f, 0.0f, 0.0f)
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

void MotionCurve::compute_rotation_matrix(glm::vec3 current_position, glm::tmat4x4<float> & rotation_matrix)
{
    glm::vec3 starting_orientation = glm::normalize(get_starting_orientation());
    glm::vec3 current_orientation = glm::normalize(compute_current_orientation(current_position));
    glm::quat quaternion = RotationBetweenVectors(starting_orientation, current_orientation);
    rotation_matrix = glm::toMat4(quaternion);
}

void MotionCurve::map_frame_to_t()
{
    current_t = 0.0f;
}

glm::vec3 MotionCurve::compute_position_on_curve()
{
    return glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 MotionCurve::get_starting_orientation()
{
    return glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 MotionCurve::compute_current_orientation(glm::vec3 current_position)
{
    glm::vec3 orientation = current_position - last_position;
    last_position = current_position;
    return orientation;
}