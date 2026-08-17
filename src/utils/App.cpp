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

float triangle[] = {
    -0.5f, -0.5f, 0.0f, 0.3, 0.5, 0.0,
    0.5f, -0.5f, 0.0f, 0.3, 0.5, 0.0,
    0.0f, 0.5f, 0.0f, 0.4, 0.6, 0.1
};

float ground[] = {
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f
};


float skyboxVertices[] = {
    -1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    -1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f
};

App::App() : triangleShader("../shaders/default.vert", "../shaders/default.frag"),
             groundShader("../shaders/ground.vert", "../shaders/ground.frag"),
             skyboxShader("../shaders/skybox.vert", "../shaders/skybox.frag") {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    // Triangle
    triangleVao.Bind();
    triangleVbo.Bind();
    triangleVbo.Data(sizeof(triangle), triangle, GL_STATIC_DRAW);

    triangleVao.LinkAttrib(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    triangleVao.LinkAttrib(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));


    // Ground
    groundVao.Bind();
    groundVbo.Bind();
    groundVbo.Data(sizeof(ground), ground, GL_STATIC_DRAW);

    groundVao.LinkAttrib(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);

    // Skybox
    skyboxVao.Bind();
    skyboxVbo.Bind();
    skyboxVbo.Data(sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

    skyboxVao.LinkAttrib(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    cubemapTexture = skybox.loadCubemap(faces);
}

void App::Run() {
    while (!window.ShouldClose()) {
        window.PollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
                                                (float) WIDTH / (float) HEIGHT, 0.1f, 100.0f);

        // Render Skybox
        glDepthFunc(GL_LEQUAL);
        skyboxShader.use();
        skyboxShader.setMat4("view", glm::mat4(glm::mat3(view)));
        skyboxShader.setMat4("projection", projection);

        skyboxVao.Bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthFunc(GL_LESS);


        // Render Ground
        groundShader.use();
        glm::mat4 model(1.0f);
        model = glm::scale(model, glm::vec3(100.0f, 1.0f, 100.0f));
        groundShader.setMat4("model", model);
        groundShader.setMat4("view", view);
        groundShader.setMat4("projection", projection);

        groundVao.Bind();
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


        // Render triangle
        triangleShader.use();
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.1f, 1.0f, 1.0f));
        triangleShader.setMat4("model", model);
        triangleShader.setMat4("view", view);
        triangleShader.setMat4("projection", projection);

        triangleVao.Bind();
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

    if (window.IsKeyPressed(GLFW_KEY_F)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    camera.ProcessMouseMovement(window.GetMouseOffsetX(), window.GetMouseOffsetY());
}
