#pragma once

#include "camera.h"
#include "surface.h"
#include "light.h"

#include <vector>

class Scene {
public:
    std::vector<Camera> cameras; // Might want multiple cameras in the scene
    std::vector<Surface*> surfaces; // All surfaces in scene, could be sphere, triangle, etc    
    std::vector<Light*> lights; // All lights in scene
    rgba background_color;
    const Camera& main_camera() const;
    Scene(const Camera &c);
};