#include "../headers/render.h"

const float POS_INFINITY = std::numeric_limits<float>::max();
const float EPSILON = .001;

void RayTracer::traceray(image &img, const Scene &scene) {
    // View frustrum
    float height = img.height;
    float width = img.width;
    float aspect_ratio = width/height;
    float viewport_height = 10.0f; // [-5, 5] This is arbitray, just determines where we have to position items in main.cpp 
    float viewport_width = aspect_ratio * viewport_height;
    float r = viewport_width/2;
    float l = -r;
    float t = viewport_height/2;
    float b = -t;

    const Camera &cam = scene.main_camera();
    const vector3 &U = cam.plane.U;
    const vector3 &V = cam.plane.V;
    const vector3 &W = cam.plane.W;

    // For each pixel 
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            // Compute screen coordinates
            float u = l + (r-l)*(x+.5f)/width;
            float v = b + (t-b)*(y+.5f)/height;

            // Compute viewing ray direction from camera's origin
            Ray *ray = nullptr;
            switch(cam.mode) {
                case (MODE::PERSPECTIVE):
                ray = new Ray (cam.position, vector3(W*(-cam.focal_length)+U*u+V*v));
                break;

                case (MODE::ORTHOGRAPHIC):
                ray = new Ray (vector3(cam.position+U*u+V*v), vector3(W*-1));
                break;
            }

            // Ray intersection: find first hit object and its surface normal (saved in hit_record)
            hit_record rec = {0, vector3(0, 0, 0), nullptr};
            if (!scene.surfaces.hit_ray(*ray, 0, POS_INFINITY, rec)) {
                img.set_pixel(x, y, scene.background_color);
                continue;
            }

            // Shading: set pixel color to value computed from point, light, and normal
            vector3 intersection = ray->origin + ray->direction * rec.t;
            rgba I(0,0,0);

            I += rec.mat->ambient_color * scene.ambient_intensity;
            for (const auto &light : scene.lights) {
                
                // Check if this point is in shadow
                hit_record srec = {0, vector3(0, 0, 0)};
                vector3 shadow_dir = (light->pos - intersection).normalize();
                Ray shadow_ray(intersection+shadow_dir*EPSILON, shadow_dir);
                if (!scene.enable_shadows || !scene.surfaces.hit_ray(shadow_ray, EPSILON, POS_INFINITY, srec))
                    I += light->compute_shading(rec.mat, rec.normal, ray->origin, intersection); 
            }

            img.set_pixel(x, y, I);
            delete ray;
        }
    }
}