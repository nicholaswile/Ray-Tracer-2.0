#include "../headers/render.h"

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

            // Ray intersection: find first object and its surface normal
            float t1 = std::numeric_limits<float>::max();
            Surface *hit_object = nullptr;
            bool hit = false;
            for (const auto &object : scene.surfaces) {
                float t = 0; 
                vector3 intersection (0, 0, 0);
                hit_record rec = {t, intersection};
                if (!object->hit_ray(*ray, 0, t1, rec)) 
                    continue;
                hit = true;
                t1 = t;
                hit_object = object;
            }
            if (hit)
                // Shading: set pixel color to value computed from point, light, and normal
                img.set_pixel(x, y, hit_object->material->surface_color);
            else
                img.set_pixel(x, y, scene.background_color);
                
            delete ray;
        }
    }
}