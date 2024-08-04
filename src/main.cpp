#include <SDL.h>
#include <SDL_image.h>

#include "../headers/render.h"
#include "../headers/sphere.h"

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
    //main_cam.set_mode(MODE::ORTHOGRAPHIC);
    main_cam.focal_length = 50.f;
    main_cam.position = vector3(0, 0, -50);
    Scene scene(main_cam);
    Material mat1, mat2, mat3, mat4;
    
    Surface *s1 = new Sphere(vector3(0, 0, 1), 1);
    mat1.surface_color = rgba(255, 255, 255);
    s1->material = &mat1;
    scene.surfaces.push_back(s1);

    Surface *s2 = new Sphere(vector3(2.5, 0, 1), 1);
    mat2.surface_color = rgba(163, 163, 163);
    s2->material = &mat2;
    scene.surfaces.push_back(s2);

    Surface *s3 = new Sphere(vector3(-2.5, 0, 1), 1);
    mat3.surface_color = rgba(128, 0, 218);
    s3->material = &mat3;
    scene.surfaces.push_back(s3);



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