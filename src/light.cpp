#include "../headers/light.h"

Light::Light(const vector3 &pos, const rgba &intensity) : pos(pos), intensity(intensity) {}

rgba Light::compute_shading(const Material *mat, const vector3 &N, const vector3 &V, const vector3 &intersection) {
    rgba L(0, 0, 0);
    vector3 l = intersection - pos;
    vector3 bisector = (V.normalize()+l.normalize()); // If V x l create a plane, bisector is the diagonal 
    float angle;

    // No break statements because models add to each other top to bottom
    switch (mat->model) {
        case MODEL::AMBIENT: {
            L += rgba(0,0,0);
        }

        case MODEL::BLINN_PHONG: {
            // If the bisector is close to the surface normal (angle diff close to 0, sine close to 1), the shine is reflecting into our eyes
            angle = N.normalize() * bisector; 
            float phong = (angle > 0 ? angle : 0);
            // L += (mat->specular_color * this->intensity * pow(phong, mat->phong_exponent));
            L += (mat->specular_color * this->intensity * phong);
        }

        case MODEL::LAMBERT: {
            // The angle between the light and the surface determines how bright it is
            angle = N.normalize() * l.normalize(); 
            L += (mat->diffuse_color * this->intensity * (angle > 0 ? angle : 0));
        }
    }

    return L;
}