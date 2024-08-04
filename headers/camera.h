#pragma once

#include "nikomath.h"

enum class MODE {PERSPECTIVE=0, ORTHOGRAPHIC};

class Camera {
public:
    vector3 position;
    vector3 direction; 
    vector3 upvector; 

    float focal_length;

    // Used to create the orthonormal basis
    struct frame {
        vector3 W = vector3(0, 0, -1); // -Direction vector
        vector3 V = vector3(0, 1, 0); // Up vector
        vector3 U = vector3(1, 0, 0); // Right vector
    };
    frame plane;
    
    MODE mode = MODE::PERSPECTIVE;
    Camera(const vector3 &position=vector3(0, 0, 0), const vector3 &direction=vector3(0,0,1), const vector3 &upvector=vector3(0,1,0), const float focal_length=50);
    void set_mode(MODE mode);
};