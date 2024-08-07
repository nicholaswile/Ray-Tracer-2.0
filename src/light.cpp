#include "../headers/light.h"

Light::Light(const vector3 &pos, const vector3 &intensity) : pos(pos), intensity(intensity) {}

rgba Light::compute_shading(const Material *mat, const vector3 &n, const vector3 &e, const vector3 &p) {
    rgba I(0, 0, 0);
    vector3 N = n.normalize();
    vector3 L = (this->pos - p).normalize();
    vector3 V = (e - p).normalize();
    vector3 Bi = (V + L).normalize();  // If V x L create a plane, bisector is the diagonal 

    // The angle between the light and the surface determines how bright it is
    float N_dot_L = N * L;
    // If the Bi is close to the surface normal (angle diff close to 0, sine close to 1), the shine is reflecting into our eyes
    float N_dot_B = N * Bi;

    // No break statements because models add to each other top to bottom
    switch (mat->model) {
        default:
        
        case MODEL::BLINN_PHONG: {
            float specular = pow((N_dot_B > 0 ? N_dot_B : 0), mat->phong_exponent);
            I += (mat->specular_color * this->intensity * specular);
        }

        case MODEL::LAMBERT: {
            float lambert = N_dot_L > 0 ? N_dot_L : 0;
            I += (mat->diffuse_color * this->intensity * lambert);
        }

        case MODEL::AMBIENT: {
            I += mat->ambient_color * this->ambient_intensity;
        }
    }

    return I;
}