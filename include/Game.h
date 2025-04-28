#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <GL/gl.h>
#include <vector>
#include <string>
#include <memory>

class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();
    void cleanup();

private:
    SDL_Window* window;
    SDL_GLContext glContext;
    bool running;
    
    // Game state
    float playerX, playerY;
    float playerAngle;
    
    // Map data
    std::vector<std::vector<int>> map;
    
    // Textures
    std::vector<GLuint> wallTextures;
    
    void handleEvents();
    void update();
    void render();
    void loadTextures();
    void loadMap(const std::string& filename);
}; 