#include "nikomath.h"
#include "material.h"
// This acts as a point light for now
// TODO: incorporate subclasses for different light types

class Light {
public:
    vector3 pos;
    rgba intensity;
    Light(const vector3 &pos=vector3(0, 0, 0), const rgba &intensity=rgba(1, 1, 1));
    // N is the surface normal, V is the ray direction, P is the point of intersection on the surface
    rgba compute_shading(const Material *mat, const vector3 &N, const vector3 &V, const vector3 &intersection);
};