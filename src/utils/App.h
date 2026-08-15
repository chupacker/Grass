//
// Created by dan on 8/14/26.
//

#ifndef GRASS_APP_H
#define GRASS_APP_H


#include "Buffers.h"
#include "Shader.h"
#include "Window.h"

class App {
public:
    App();

    void Run();

    void ProcessInput();

private:
    // Window
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 800;
    static constexpr const char *TITLE = "Grassy";
    Window window{WIDTH, HEIGHT, TITLE};

    // Objects
    Vao vao;
    Vbo vbo;

    //Shader
    Shader shader; // MUST BE AFTER WINDOW INITIALIZATION!!! because gladLoadGL must be called before any actual opengl function
};


#endif //GRASS_APP_H
