#include "MotionPlan.h"

#include "Constants.h"

MotionPlan::MotionPlan() :
    start_x(0.0f), start_y(0.0f), start_z(0.0f), 
    start_angle_x(0.0f), start_angle_y(0.0f), start_angle_z(0.0f), start_scale(0.0f),
    motion(nullptr), type(MOTION_PLAN_TYPE_NONE), current(0), 
    motion_segments(nullptr), motion_curves(nullptr)
{
}

MotionPlan::~MotionPlan()
{
}

void MotionPlan::initialize(
        float _start_x, float _start_y, float _start_z,
        float _start_angle_x, float _start_angle_y, float _start_angle_z, float _start_scale,
        float _speed_translate_x, float _speed_translate_y, float _speed_translate_z,
        float _speed_rotate_x, float _speed_rotate_y, float _speed_rotate_z, float _speed_scale,
        unsigned int _type, std::vector<MotionSegment> *_motion_segments, std::vector<MotionCurve*> *_motion_curves
)
{
    start_x = _start_x;
    start_y = _start_y;
    start_z = _start_z;
    start_angle_x = _start_angle_x;
    start_angle_y = _start_angle_y;
    start_angle_z = _start_angle_z;
    start_scale = _start_scale;

    motion = std::make_shared<Motion>();
    if (motion)
    {
        motion->initialize(
            _speed_translate_x, _speed_translate_y, _speed_translate_z, 
            _speed_rotate_x, _speed_rotate_y, _speed_rotate_z, _speed_scale
        );
    }
    gotoStart();

    type =_type;
    motion_segments = _motion_segments;
    motion_curves = _motion_curves;
    setSpeed();
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
    if (motion)
    {
        motion->reset_motion();
    }
    gotoStart();

    current = 0;
    unsigned int num_frames = 0;
    if (motion_segments)
    {
        std::vector<MotionSegment>::iterator itr_seg = motion_segments->begin();
        for (; itr_seg != motion_segments->end(); itr_seg++)
        {
            num_frames += itr_seg->reset();
        }
    }
    else if (motion_curves)
    {
        std::vector<MotionCurve*>::iterator itr_curve = motion_curves->begin();
        for (; itr_curve != motion_curves->end(); itr_curve++)
        {
            num_frames += (*itr_curve)->reset();
        }
    }

    return (num_frames > 0);
}

bool MotionPlan::next()
{
    bool n = false;
    if (motion_segments)
    {
        while (current < static_cast<int>(motion_segments->size()))
        {
            if (!(*motion_segments)[current].next())
            {
                current++;
            }
            else
            {
                n = true;
                break;
            }
        }
    }
    else if (motion_curves)
    {
        while (current < static_cast<int>(motion_curves->size()))
        {
            if (!(*motion_curves)[current]->next())
            {
                current++;
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
    if (!motion)
    {
        return;
    }

    if (motion_segments)
    {
        (*motion_segments)[current].execute();

        // Translation
        if ((*motion_segments)[current].translate)
        {
            motion->compute_incremental_translation(
                (*motion_segments)[current].direction_x,
                (*motion_segments)[current].direction_y,
                (*motion_segments)[current].direction_z);
        }

        // Rotation
        if ((*motion_segments)[current].rotate)
        {
            motion->compute_incremental_rotation(
                (*motion_segments)[current].direction_rotate_x,
                (*motion_segments)[current].direction_rotate_y,
                (*motion_segments)[current].direction_rotate_z);
        }

        // Scaling
        if ((*motion_segments)[current].scale)
        {
            motion->compute_incremental_scaling((*motion_segments)[current].direction_scale);
        }
    }
    else if (motion_curves)
    {

        glm::vec3 position;
        glm::tmat4x4<float> rotation_matrix;
        (*motion_curves)[current]->compute_position(position);
        (*motion_curves)[current]->compute_rotation_matrix(position, rotation_matrix);
        motion->setPosition(position);
        motion->setRotationMatrix(rotation_matrix);
    }
}

std::shared_ptr<Motion> MotionPlan::get_motion()
{
    return motion;
}

void MotionPlan::gotoStart()
{
    if (motion)
    {
        motion->set_translation(start_x, start_y, start_z);
        motion->set_rotation(start_angle_x, start_angle_y, start_angle_z);
        motion->set_scaling(start_scale);
    }
}

void MotionPlan::setSpeed()
{
    if (motion && motion_curves)
    {
        float speed_translate = motion->get_speed_translate_average();
        std::vector<MotionCurve*>::iterator itr_curve = motion_curves->begin();
        for (; itr_curve != motion_curves->end(); itr_curve++)
        {
            (*itr_curve)->initialize(speed_translate);
        }
    }
}