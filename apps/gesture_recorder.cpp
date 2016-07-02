#include <iostream>
#include <map>
#include <vector>

#include <Eigen/Core>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLImage.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Exception.hh>
#include <SDL2pp/Point.hh>
#include <yaml-cpp/yaml.h>

#include "eigen_yaml.h"
#include "resource_path.h"

std::vector<Eigen::Matrix2Xi> recorded_gestures;

void add_gesture(const std::vector<SDL2pp::Point>& gesture)
{
    recorded_gestures.push_back(Eigen::Matrix2Xi{2, gesture.size()});
    auto& mat = recorded_gestures.back();
    for(int i = 0; i < static_cast<int>(gesture.size()); i++)
    {
        const SDL2pp::Point& point = gesture[i];
        mat(0, i) = point.GetX();
        mat(1, i) = point.GetY();
    }
}

int main(int argc, char *argv[])
{
    try
    {
        SDL2pp::SDL sdl_init(SDL_INIT_VIDEO);
        SDL2pp::SDLImage sdl_image_init(IMG_INIT_PNG);
        const std::string dataPath = util::getResourcePath();

        SDL2pp::Window window("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

        SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        std::vector<SDL2pp::Point> mouse_positions;
        bool mouse_left_pressed = false;
        SDL_Event event;
        bool run = true;
        while(run)
        {
            while (SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                case SDL_QUIT:
                    run = false;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q)
                        run = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch(event.button.button)
                    {
                    case SDL_BUTTON_LEFT:
                        mouse_left_pressed = true;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    switch(event.button.button)
                    {
                    case SDL_BUTTON_LEFT:
                        mouse_left_pressed = false;
                        add_gesture(mouse_positions);
                        mouse_positions.clear();
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (mouse_left_pressed)
                        mouse_positions.push_back(SDL2pp::Point(event.motion.x, event.motion.y));

                }
            }
            //First clear the renderer
            renderer.SetDrawColor(255, 255, 255);
            renderer.Clear();
            renderer.SetDrawColor(255, 0, 0);
            if(mouse_positions.size() > 0)
                renderer.DrawPoints(mouse_positions.data(), static_cast<int>(mouse_positions.size()));
            //Update the screen
            renderer.Present();

            SDL_Delay(1);
        }
    } catch (SDL2pp::Exception& e)
    {
        std::cerr << "Error in: " << e.GetSDLFunction() << std::endl;
        std::cerr << "  Reason: " << e.GetSDLError() << std::endl;
    }

    YAML::Node node;
    node = recorded_gestures;

    YAML::Emitter out;
    out << node;
    std::cout << out.c_str() << std::endl;

    return 0;
}

