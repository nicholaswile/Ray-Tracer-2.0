#include "../headers/light.h"

Light::Light(const vector3 &pos, const rgba &intensity) : pos(pos), intensity(intensity) {}

rgba Light::compute_shading(const Material *mat, const vector3 &N, const vector3 &V, const vector3 &intersection) {
    rgba L(0, 0, 0);
    vector3 l = intersection - pos;
    float angle = N.normalize() * l.normalize();
    // No break statements because models add to each other top to bottom
    switch (mat->model) {
        case MODEL::AMBIENT:
        L += rgba(0,0,0);
        case MODEL::BLINN_PHONG:
        L += rgba(0,0,0);
        case MODEL::LAMBERT:
        L += (mat->surface_color * this->intensity * (angle > 0 ? angle : 0));
    }
    // Clamp
    if (L.r > 255) L.r = 255;
    else if (L.r < 0) L.r = 0;
    if (L.g > 255) L.g = 255;
    else if (L.g < 0) L.g = 0;
    if (L.b > 255) L.b = 255;
    else if (L.b < 0) L.b = 0;

    return L;
}