#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // 1. Initialize SDL2 Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 2. Set OpenGL attributes (Request OpenGL 2.1 compatibility context)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // 3. Create the Window with the OpenGL flag
    SDL_Window* window = SDL_CreateWindow(
        "SDL2 OpenGL Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // 4. Create the OpenGL Context bound to the window
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Use VSync (1 = enable, 0 = disable)
    SDL_GL_SetSwapInterval(1);

    // 5. Main Game Loop Variable
    bool running = true;
    SDL_Event event;
    float rotation = 0.0f;

    // 6. Main Loop
    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            }
        }

        // Rendering setup
        glViewport(0, 0, 800, 600);
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // Dark blue background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw a spinning triangle
        glLoadIdentity();
        glRotatef(rotation, 0.0f, 0.0f, 1.0f); // Rotate around Z axis

        glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f); glVertex2f( 0.0f,  0.5f); // Red Top
            glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(-0.5f, -0.5f); // Green Bottom Left
            glColor3f(0.0f, 0.0f, 1.0f); glVertex2f( 0.5f, -0.5f); // Blue Bottom Right
        glEnd();

        // Increment rotation angle
        rotation += 1.0f;

        // Swap buffers to display the frame
        SDL_GL_SwapWindow(window);
    }

    // 7. Clean up resources
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
