#pragma once
#include<vector>

#include <glm/glm.hpp>

#include "Motion.h"
#include "MotionSegment.h"

static const unsigned int MOTION_PLAN_TYPE_NONE = 0x00000000;
static const unsigned int MOTION_PLAN_TYPE_INFINITE = 0x00000001;
static const unsigned int MOTION_PLAN_TYPE_FINITE = 0x00000002;
static const unsigned int MOTION_PLAN_TYPE_REPEAT = 0x00000004;

class MotionPlan
{
public:
    MotionPlan();
    ~MotionPlan();

    void initialize(
        float _start_x, float _start_y, float _start_z,
        float _start_angle_x, float _start_angle_y, float _start_angle_z, float _start_scale,
        std::vector<MotionSegment> *_motion_segments, unsigned int _type,
        float _speed_translate_x, float _speed_translate_y, float _speed_translate_z,
        float _speed_rotate_x, float _speed_rotate_y, float _speed_rotate_z, float _speed_scale
    );

    void move();

    bool reset();
    bool next();
    void execute();

    Motion* get_motion();

private:
    float start_x;
    float start_y;
    float start_z;
    float start_angle_x;
    float start_angle_y;
    float start_angle_z;
    float start_scale;
    //
    Motion motion;
    std::vector<MotionSegment> *motion_segments;
    int current_segment;
    unsigned int type;

private:
    void gotoStart();
};

