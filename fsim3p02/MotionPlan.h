#pragma once
#include<vector>

#include <glm/glm.hpp>

#include "Motion.h"
#include "MotionSegment.h"
#include "MotionCurve.h"

static const unsigned int MOTION_PLAN_TYPE_NONE     = 0x00000000;
static const unsigned int MOTION_PLAN_TYPE_INFINITE = 0x00000001;
static const unsigned int MOTION_PLAN_TYPE_FINITE   = 0x00000002;
static const unsigned int MOTION_PLAN_TYPE_REPEAT   = 0x00000004;

class MotionPlan
{
public:
    MotionPlan();
    ~MotionPlan();

    void initialize(
        float _start_x, float _start_y, float _start_z,
        float _start_angle_x, float _start_angle_y, float _start_angle_z, float _start_scale,
        float _speed_translate_x, float _speed_translate_y, float _speed_translate_z,
        float _speed_rotate_x, float _speed_rotate_y, float _speed_rotate_z, float _speed_scale,
        unsigned int _type, std::vector<MotionSegment> *_motion_segments, std::vector<MotionCurve*> *_motion_curves
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
    unsigned int type;
    int current;
    std::vector<MotionSegment> *motion_segments;
    std::vector<MotionCurve*> *motion_curves;

private:
    void gotoStart();
    void setSpeed();
};

