#pragma once

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp> 

class MotionCurve
{
public:
    MotionCurve();
    ~MotionCurve();

    virtual void initialize(float speed_translate);

    unsigned int reset();
    bool next();

    void compute_position(glm::vec3 & position);
    void compute_rotation_matrix(glm::tmat4x4<float> & rotation_matrix);

protected:
    // Duration
    unsigned int num_frames;
    unsigned int current_frame;

    // Parameter value
    float current_t;

private:
    virtual void map_frame_to_t();
    virtual glm::vec3 compute_position_on_curve();
    virtual glm::vec3 compute_tangent_on_curve();
    virtual glm::vec3 get_starting_orientation();
};

