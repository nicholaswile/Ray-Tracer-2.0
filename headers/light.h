#include "nikomath.h"
#include "material.h"
// This acts as a point light for now
// TODO: incorporate subclasses for different light types

class Light {
public:
    vector3 pos;
    vector3 intensity;
    Light(const vector3 &pos=vector3(0, 0, 0), const vector3 &intensity=vector3(1, 1, 1));
    // n is the surface normal, e is the position of the viewer, p is the point of intersection on the surface
    rgba compute_shading(const Material *mat, const vector3 &n, const vector3 &e, const vector3 &p);
};