#include "Game.h"
#include <iostream>

Game::Game() : window(nullptr), glContext(nullptr), running(false),
               playerX(1.5f), playerY(1.5f), playerAngle(0.0f) {
}

Game::~Game() {
    cleanup();
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window = SDL_CreateWindow("Doom Clone",
                             SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED,
                             800, 600,
                             SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "OpenGL context creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize OpenGL
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    // Load textures and map
    loadTextures();
    loadMap("assets/maps/level1.map");

    running = true;
    return true;
}

void Game::run() {
    while (running) {
        handleEvents();
        update();
        render();
        SDL_GL_SwapWindow(window);
    }
}

void Game::cleanup() {
    if (glContext) {
        SDL_GL_DeleteContext(glContext);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_LEFT:
                    playerAngle -= 0.1f;
                    break;
                case SDLK_RIGHT:
                    playerAngle += 0.1f;
                    break;
                case SDLK_w:
                    playerX += cos(playerAngle) * 0.1f;
                    playerY += sin(playerAngle) * 0.1f;
                    break;
                case SDLK_s:
                    playerX -= cos(playerAngle) * 0.1f;
                    playerY -= sin(playerAngle) * 0.1f;
                    break;
            }
        }
    }
}

void Game::update() {
    // Update game state
}

void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Basic raycasting implementation
    for (int x = 0; x < 800; x++) {
        float rayAngle = (playerAngle - 0.5f) + (float)x / 800.0f;
        float rayX = playerX;
        float rayY = playerY;
        
        float rayDirX = cos(rayAngle);
        float rayDirY = sin(rayAngle);
        
        float distance = 0;
        bool hitWall = false;
        
        while (!hitWall && distance < 20) {
            distance += 0.1f;
            rayX = playerX + rayDirX * distance;
            rayY = playerY + rayDirY * distance;
            
            int mapX = (int)rayX;
            int mapY = (int)rayY;
            
            if (mapX < 0 || mapX >= map[0].size() || mapY < 0 || mapY >= map.size()) {
                hitWall = true;
            }
            else if (map[mapY][mapX] > 0) {
                hitWall = true;
            }
        }
        
        // Draw wall slice
        int wallHeight = (int)(600 / distance);
        int wallTop = (600 - wallHeight) / 2;
        
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);
        glVertex2i(x, wallTop);
        glVertex2i(x, wallTop + wallHeight);
        glEnd();
    }
}

void Game::loadTextures() {
    // Load wall textures
    // TODO: Implement texture loading
}

void Game::loadMap(const std::string& filename) {
    // Simple test map
    map = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };
} 