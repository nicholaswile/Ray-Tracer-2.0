#include "../headers/triangle.h"

Triangle::Triangle(const vector3 &A, const vector3 &B, const vector3 &C)  
{
    this->verts.push_back(A);
    this->verts.push_back(B);
    this->verts.push_back(C);
}

// Möller–Trumbore intersection algorithm
bool Triangle::hit_ray(const Ray &ray, float t0, float t1, hit_record &rec) const {

    const float EPSILON = 0.0000001;
    vector3 edge1 = verts[1] - verts[0];
    vector3 edge2 = verts[2] - verts[0];

    // This ray is parallel to this triangle.
    vector3 ray_cross_e2 = ray.direction ^ edge2; // Find normal of plane created by the ray and an arbitrary edge
    float determinant = edge1 * ray_cross_e2; // Angle between normal of plane and the other edge of the triangle
    // If the new normal is near parallel to the edge, then the dot product (cosine) approaches 1
    // And if that normal is parallel, that means the original ray is near perpendicular to the triangle
    // Otherwise, if the new normal is near perpendicular to the edge then the cosine approaches 0
    // And if that new normal is perpendicular, that means the original ray is near parallel to the triangle
    // So if the angle between the normal and the other edge is near perpendicular,
    // Then the dot product between them (cosine) is near 0 
    // Meaning the original ray that created the plane/normal with the other edge was near parallel to the triangle
    // Thus we return this is not an intersection
    if (determinant > -EPSILON && determinant < EPSILON)
        return false;    

    // Determinent
    float inv_det = 1.0 / determinant;
    
    // First barycentric coordinate
    vector3 s = ray.origin - verts[0];
    float beta = inv_det * (s * ray_cross_e2);
    if (beta < 0.0 || beta > 1.0)
        return false;

    // Second barycentric coordinate
    vector3 s_cross_e1 = s ^ edge1;
    float gamma = inv_det * (ray.direction * s_cross_e1);
    if (gamma < 0.0 || beta + gamma > 1.0)
        return false;

    //Compute t to find out where the intersection point is on the line.
    float t = inv_det * (edge2 * s_cross_e1);

    if (t > EPSILON && t >= t0 && t <= t1) // ray intersection
    {
        rec.t = t;
        rec.normal = (edge1 ^ edge2).normalize();
        return true;
    }
    else // This means that there is a line intersection but not a ray intersection.
        return false;
}
