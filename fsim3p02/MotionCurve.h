#pragma once

#include <glm/glm.hpp>

class MotionCurve
{
public:
    MotionCurve();
    ~MotionCurve();

    unsigned int reset();
    bool next();

    void compute_position(float speed_translate, glm::vec3& position);
    void compute_tangent(glm::vec3& tangent);

protected:
    // Duration
    unsigned int num_frames;
    unsigned int current_frame;

    // Parameter value
    float current_t;

private:
    virtual void map_frame_to_t(float speed_translate);
    virtual glm::vec3 compute_position_on_curve();
    virtual glm::vec3 compute_tangent_on_curve();
};

