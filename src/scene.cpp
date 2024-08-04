#include "../headers/scene.h"

Scene::Scene(const Camera &c) {
    cameras.push_back(c);
    background_color = rgba(0, 0, 0, 255);
}

Camera& Scene::main_camera() {
    return this->cameras[0];
}