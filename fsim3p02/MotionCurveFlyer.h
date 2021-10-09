#pragma once

#include "MotionCurve.h"

class MotionCurveFlyer :  public MotionCurve
{
public:
    MotionCurveFlyer();
    ~MotionCurveFlyer();

    void initialize(float speed_translate);

private:
    void map_frame_to_t();
    glm::vec3 compute_position_on_curve();
    glm::vec3 get_starting_orientation();
};

