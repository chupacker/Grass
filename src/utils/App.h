//
// Created by dan on 8/14/26.
//

#ifndef GRASS_APP_H
#define GRASS_APP_H


#include "Skybox.h"
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
    static constexpr int WIDTH = 100*16;
    static constexpr int HEIGHT = 100*9;
    static constexpr const char *TITLE = "Grassy";
    Window window{WIDTH, HEIGHT, TITLE};

    // Objects
    Vao triangleVao;
    Vbo triangleVbo;

    Vao groundVao;
    Vbo groundVbo;

    Vao skyboxVao;
    Vbo skyboxVbo;

    //Shader
    Shader triangleShader; // MUST BE AFTER WINDOW INITIALIZATION!!! because gladLoadGL must be called before any actual opengl function
    Shader groundShader;
    Shader skyboxShader;

    //Skybox
    Skybox skybox;

    GLuint cubemapTexture;
    std::vector<std::string> faces
    {
        "../resources/textures/skybox/right.jpg",
        "../resources/textures/skybox/left.jpg",
        "../resources/textures/skybox/top.jpg",
        "../resources/textures/skybox/bottom.jpg",
        "../resources/textures/skybox/front.jpg",
        "../resources/textures/skybox/back.jpg",
    };

};


#endif //GRASS_APP_H
