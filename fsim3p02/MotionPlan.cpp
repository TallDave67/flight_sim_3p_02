#include "MotionPlan.h"

#include "Constants.h"

MotionPlan::MotionPlan() :
    start_x(0.0f), start_y(0.0f), start_z(0.0f), 
    start_angle_x(0.0f), start_angle_y(0.0f), start_angle_z(0.0f), start_scale(0.0f),
    motion_segments(nullptr), current_segment(0), type(MOTION_PLAN_TYPE_NONE)
{
}

MotionPlan::~MotionPlan()
{
}

void MotionPlan::initialize(
        float _start_x, float _start_y, float _start_z,
        float _start_angle_x, float _start_angle_y, float _start_angle_z, float _start_scale,
        std::vector<MotionSegment> *_motion_segments, unsigned int _type,
        float _speed_translate_x, float _speed_translate_y, float _speed_translate_z,
        float _speed_rotate_x, float _speed_rotate_y, float _speed_rotate_z, float _speed_scale
)
{
    start_x = _start_x;
    start_y = _start_y;
    start_z = _start_z;
    start_angle_x = _start_angle_x;
    start_angle_y = _start_angle_y;
    start_angle_z = _start_angle_z;
    start_scale = _start_scale;

    motion_segments = _motion_segments;
    type =_type;

    motion.initialize(
        _speed_translate_x, _speed_translate_y, _speed_translate_z, 
        _speed_rotate_x, _speed_rotate_y, _speed_rotate_z, _speed_scale
    );
    gotoStart();
}
    
void MotionPlan::move()
{
    if (type & MOTION_PLAN_TYPE_INFINITE)
    {
        execute();
    }
    else
    {
        if (next())
        {
            execute();
        }
        else if (type & MOTION_PLAN_TYPE_REPEAT)
        {
            if (reset())
            {
                move();
            }
        }
    }
}

bool MotionPlan::reset()
{
    motion.reset_motion();
    gotoStart();

    current_segment = 0;
    unsigned int num_frames = 0;
    if (motion_segments)
    {
        std::vector<MotionSegment>::iterator itr_seg = motion_segments->begin();
        for (; itr_seg != motion_segments->end(); itr_seg++)
        {
            num_frames += itr_seg->reset();
        }
    }

    return (num_frames > 0);
}

bool MotionPlan::next()
{
    bool n = false;
    if (motion_segments)
    {
        while (current_segment < static_cast<int>(motion_segments->size()))
        {
            if (!(*motion_segments)[current_segment].next())
            {
                current_segment++;
            }
            else
            {
                n = true;
                break;
            }
        }
    }
    return n;
}

void MotionPlan::execute()
{
    (*motion_segments)[current_segment].execute();
    
    // Translation
    if ((*motion_segments)[current_segment].translate)
    {
        motion.compute_incremental_translation(
            (*motion_segments)[current_segment].direction_x, 
            (*motion_segments)[current_segment].direction_y,
            (*motion_segments)[current_segment].direction_z);
    }

    // Rotation
    if ((*motion_segments)[current_segment].rotate)
    {
        motion.compute_incremental_rotation(
            (*motion_segments)[current_segment].direction_rotate_x,
            (*motion_segments)[current_segment].direction_rotate_y,
            (*motion_segments)[current_segment].direction_rotate_z);
    }

    // Scaling
    if ((*motion_segments)[current_segment].scale)
    {
        motion.compute_incremental_scaling((*motion_segments)[current_segment].direction_scale);
    }
}

Motion* MotionPlan::get_motion()
{
    return &motion;
}

void MotionPlan::gotoStart()
{
    motion.set_translation(start_x, start_y, start_z);
    motion.set_rotation(start_angle_x, start_angle_y, start_angle_z);
    motion.set_scaling(start_scale);
}