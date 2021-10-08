#include "MotionCurveFlyer.h"

#include "Constants.h"

MotionCurveFlyer::MotionCurveFlyer()
{
}

MotionCurveFlyer::~MotionCurveFlyer()
{

}

void MotionCurveFlyer::initialize(float speed_translate)
{
    // each period of our flight will last 12 seconds if our speed is 1.0f
    num_frames = static_cast<unsigned int>(static_cast<float>(12 * FPS_WINDOW) / speed_translate);
}

void MotionCurveFlyer::map_frame_to_t()
{
    unsigned int frames_per_quarter = num_frames / 4;
    
}


glm::vec3 MotionCurveFlyer::compute_position_on_curve()
{

}


glm::vec3 MotionCurveFlyer::compute_tangent_on_curve()
{

}

