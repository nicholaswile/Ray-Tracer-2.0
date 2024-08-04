#pragma once

#include "camera.h"
#include "surface.h"

#include <vector>

class Scene {
public:
    std::vector<Camera> cameras; // Might want multiple cameras in the scene
    std::vector<Surface*> surfaces; // All surfaces in scene, could be sphere, triangle, etc    
    rgba background_color;
    Camera& main_camera();
    Scene(const Camera &c);
};