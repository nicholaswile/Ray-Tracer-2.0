#include "../headers/camera.h"

Camera::Camera(const vector3 &position, const vector3 &direction, const vector3 &upvector, const float focal_length) : position(position), direction(direction), upvector(upvector), focal_length(focal_length) 
{
    plane.W = (direction*-1).normalize();
    plane.U = (upvector ^ plane.W).normalize();
    plane.V = (plane.W^plane.U).normalize();
}

void Camera::set_mode(MODE mode) 
{
    this->mode = mode;
}