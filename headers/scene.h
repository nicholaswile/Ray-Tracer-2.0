#pragma once

#include "camera.h"
#include "light.h"
#include "group.h"

#include <vector>

class Scene {
public:
    Group surfaces; // All surfaces in scene
    vector3 ambient_intensity = vector3(.33,.33,.33);
    std::vector<Camera> cameras; // Might want multiple cameras in the scene
    std::vector<Light*> lights; // All lights in scene
    bool enable_shadows = true;
    rgba background_color;
    const Camera& main_camera() const;
    Scene(const Camera &c);
};