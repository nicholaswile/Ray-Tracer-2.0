#include <SDL.h>
#include <SDL_image.h>

#include "../headers/render.h"
#include "../headers/sphere.h"
#include "../headers/triangle.h"

#include <iostream>
#include <string> 
#include <cstdlib> // srand()
#include <ctime> // time()

const int WIDTH = 800, HEIGHT = 600;
const int SCALE_X = 1, SCALE_Y = 1;
const char* TITLE = "Niko's Ray Tracer";

const int FPS = 60;
const float FRAME_LIMIT = 1000.f/FPS;

void take_screenshot(SDL_Renderer *renderer);
void set_buffer (image &img);
void display_renderer (SDL_Renderer *renderer, image &img);

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, SCALE_X, SCALE_Y);
    SDL_SetWindowTitle(window, TITLE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

#define DEBUG
    // Seed RNG
#ifdef DEBUG
    srand(0);
#else
    srand(time(0));
#endif

    RayTracer rt;
    image img(WIDTH, HEIGHT);

    Camera main_cam;
    // main_cam.set_mode(MODE::ORTHOGRAPHIC);
    main_cam.focal_length = 50.f;
    main_cam.position = vector3(0, 0, -50);
    Scene scene(main_cam);
    scene.background_color = rgba(135, 206, 235);
    Material mat1, mat2, mat3, mat4, mat5;
    
    Surface *s1 = new Sphere(vector3(0, 2, -4.5), 1);
    mat1.diffuse_color = rgba(0, 218, 0);
    mat1.ambient_color = mat1.diffuse_color;
    mat1.reflectivity = .20f;
    mat1.phong_exponent = 100;
    mat1.model = MODEL::BLINN_PHONG;
    s1->material = &mat1;
    scene.surfaces.push_back(s1);

    Surface *s2 = new Sphere(vector3(3.5, 1.5, -2), 1);
    mat2.diffuse_color = rgba(218, 0, 0);
    mat2.ambient_color = mat2.diffuse_color;
    mat2.reflectivity = .10f;
    mat2.phong_exponent = 10;
    mat2.model = MODEL::BLINN_PHONG;
    s2->material = &mat2;
    scene.surfaces.push_back(s2);

    Surface *s3 = new Sphere(vector3(-3.5, 1.5, -2), 1);
    mat3.diffuse_color = rgba(128, 0, 218);
    mat3.ambient_color = mat3.diffuse_color;
    mat3.reflectivity = .10f;
    mat3.phong_exponent = 1000;
    mat3.model = MODEL::BLINN_PHONG;
    s3->material = &mat3;
    scene.surfaces.push_back(s3);

    // Surface *s4 = new Sphere(vector3(0, 100, 20), 100);
    // mat4.diffuse_color = rgba(163, 163, 163);
    // mat4.ambient_color = mat4.diffuse_color;
    // mat4.reflectivity = .25f;
    // mat4.phong_exponent = 10;
    // mat4.model = MODEL::BLINN_PHONG;
    // s4->material = &mat4;
    // scene.surfaces.push_back(s4);

    Surface *s5 = new Sphere(vector3(0, 0, 5.5), 6);
    mat5.diffuse_color = rgba(163, 163, 163);
    mat5.ambient_color = mat5.diffuse_color;
    mat5.reflectivity = .75f;
    mat5.phong_exponent = 10000;
    mat5.model = MODEL::BLINN_PHONG;
    s5->material = &mat5;
    scene.surfaces.push_back(s5);

    const vector3 ORIGIN (-10, 2.5, -10);
    const int BOARD_LEN = 20;
    const int NSQ = 20;
    Group chessboard;
    const int SQ_LEN = NSQ/BOARD_LEN;
    Material m1, m2;
    m1.diffuse_color = rgba(0, 0, 0);
    m1.ambient_color = m1.diffuse_color;
    m1.reflectivity = .02f;
    m1.phong_exponent = 10;
    m1.model = MODEL::BLINN_PHONG;
    m2.diffuse_color = rgba(255, 255, 255);
    m2.ambient_color = m2.diffuse_color;
    m2.reflectivity = .02f;
    m2.phong_exponent = 10;
    m2.model = MODEL::BLINN_PHONG;
    std::vector<Material*> pattern = {&m1, &m2};
    int i = 0;
    for (int y = ORIGIN.z; y < ORIGIN.z + BOARD_LEN; y += SQ_LEN)
        for (int x = ORIGIN.x; x < ORIGIN.x + BOARD_LEN; x += SQ_LEN) {
            Surface *tri1 = new Triangle(vector3(x, ORIGIN.y, y), vector3(x+SQ_LEN, ORIGIN.y, y), vector3(x, ORIGIN.y, y+SQ_LEN));
            Surface *tri2 = new Triangle(vector3(x+SQ_LEN, ORIGIN.y, y), vector3(x+SQ_LEN, ORIGIN.y, y+SQ_LEN), vector3(x, ORIGIN.y, y+SQ_LEN));
            tri1->material = pattern[i%2];
            tri2->material = pattern[i%2];
            i++;
            chessboard.push_back(tri1);
            chessboard.push_back(tri2);
        }   
    
    scene.surfaces.push_back(&chessboard);

    Light *l1 = new Light(vector3(-10, -10, -20));
    scene.lights.push_back(l1);

    Light *l2 = new Light(vector3(10, -20, -40));
    l2->intensity = vector3(.15, .15, .15);
    scene.lights.push_back(l2);

    Light *l3 = new Light(vector3(10, -20, 20));
    l3->intensity = vector3(.05, .05, .05);
    scene.lights.push_back(l3);

    // Ray Tracer function
    rt.traceray(img, scene);

    while (true) {
        // Start frame time
        int start_time = SDL_GetTicks();

        // Display 
        display_renderer(renderer, img);

        // Process input
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_s:    take_screenshot(renderer);   break;
                }
            }
        }

        // End frame time
        int delta_time = SDL_GetTicks() - start_time;
        if (delta_time < FRAME_LIMIT) {
            SDL_Delay(FRAME_LIMIT - delta_time);
        }
    }
    
    return 0;
}

void set_buffer (image &img) {
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            img.set_pixel(x, y, rgba(rand()%256, rand()%256, rand()%256)); 
}

void display_renderer (SDL_Renderer *renderer, image &img){
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++) {
            rgba color = img.get_pixel(x, y);
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    SDL_RenderPresent(renderer);
}

void take_screenshot(SDL_Renderer *renderer) {
    SDL_Surface *sshot = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
    std::string saveas = "screenshots/screenshot-"+std::to_string(time(0))+".png";
    IMG_SavePNG(sshot, saveas.c_str());
    SDL_FreeSurface(sshot);
}