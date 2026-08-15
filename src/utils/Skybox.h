//
// Created by dan on 8/16/26.
//

#pragma once

#ifndef GRASS_SKYBOX_H
#define GRASS_SKYBOX_H
#include <string>
#include <vector>
#include <glad/gl.h>


class Skybox {
public:
    GLuint loadCubemap(std::vector<std::string> faces);
};


#endif //GRASS_SKYBOX_H
