//
// Created by dan on 8/14/26.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Buffers.h"
#include "Shader.h"
#include "App.h"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};

App::App() : shader("../shaders/default.vert", "../shaders/default.frag") {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    vao.Bind();
    vbo.Bind();
    vbo.Data(sizeof(vertices), vertices, GL_STATIC_DRAW);

    vao.LinkAttrib(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
}

void App::Run() {
    while (!window.ShouldClose()) {
        window.PollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        // Camera stuff
        glm::mat4 model(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
                                                (float) WIDTH / (float) HEIGHT, 0.1f, 100.0f);

        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);


        glDrawArrays(GL_TRIANGLES, 0, 3);
        ProcessInput();
        window.SwapBuffers();
    }
}

void App::ProcessInput() {
    if (window.IsKeyPressed(GLFW_KEY_ESCAPE)) {
        window.Close();
    }
    if (window.IsKeyPressed(GLFW_KEY_W)) {
        camera.ProcessKeyboard(FORWARD);
    }
    if (window.IsKeyPressed(GLFW_KEY_A)) {
        camera.ProcessKeyboard(LEFT);
    }
    if (window.IsKeyPressed(GLFW_KEY_S)) {
        camera.ProcessKeyboard(BACKWARD);
    }
    if (window.IsKeyPressed(GLFW_KEY_D)) {
        camera.ProcessKeyboard(RIGHT);
    }

    camera.ProcessMouseMovement(window.GetMouseOffsetX(), window.GetMouseOffsetY());
}
