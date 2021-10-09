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
    // we are flying around a circle, so we first divide the number of frames by 4
    // so we can specify the angle range based on the quarter-circle we are in
    unsigned int frames_per_quarter = num_frames / 4;
    float t_inc = 90.0f / frames_per_quarter;
    unsigned int frame_in_quarter = 0;
 
    // what quarter are we in?
    if (current_frame <= frames_per_quarter)
    {
        // 1st
        if (current_frame == frames_per_quarter)
        {
            // to avoid rounding errors we set to exactly
            // a quarter the way round the cirle
            current_t = 90.0f;
        }
        else
        {
            current_t = current_frame * t_inc;
        }  
    }
    else if (current_frame <= 2 * frames_per_quarter)
    {
        // 2nd
        if (current_frame == 2 * frames_per_quarter)
        {
            // to avoid rounding errors we set to exactly
            // half-way round the cirle
            current_t = 180.0f;
        }
        else
        {
            current_t = current_frame * t_inc;
        }  
    }
    else if (current_frame <= 3 * frames_per_quarter)
    {
        // 3nd
        if (current_frame == 3 * frames_per_quarter)
        {
            // to avoid rounding errors we set to exactly
            // three quarters of the way round the cirle
            current_t = 270.0f;
        }
        else
        {
            current_t = current_frame * t_inc;
        }  
    }
    else
    {
        //4th
        if (current_frame == num_frames)
        {
            // it's possible our number of frames
            // is not cleanly divisible by 4
            // so the 4th quarter might get an extra frame
            current_t = 360.0f;
        }
        else
        {
            current_t = current_frame * t_inc;
        }  
    }
}


glm::vec3 MotionCurveFlyer::compute_position_on_curve()
{
    float radius = 6.0f;
    float height = 4.0f;
    float z = radius * cosf(glm::radians(current_t));
    float x = radius * sinf(glm::radians(current_t)) + 2.0f;
    float y = height;
    return glm::vec3(x, y, z);
}


glm::vec3 MotionCurveFlyer::compute_tangent_on_curve()
{
    float radius = 6.0f;
    float z = radius * -sinf(glm::radians(current_t));
    float x = radius * cosf(glm::radians(current_t));
    float y = 0.0f;
    return glm::vec3(x, y, z);
}

glm::vec3 MotionCurveFlyer::get_starting_orientation()
{
    return glm::vec3(-1.0f, 0.0f, 0.0f);
}
