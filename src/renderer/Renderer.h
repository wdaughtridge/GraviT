//
//  Renderer.h
//  GraviT
//
//  Created by William Daughtridge on 6/4/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#ifndef Renderer_h
#define Renderer_h

#include <GL/glew.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include "Shader.h"
#include "Logger.h"
#include "renderer/ShaderProgram.h"

namespace GraviT {

class Renderer {
private:
    GLFWwindow* m_window;
    unsigned int VAO, VBO, EBO;
    std::unique_ptr<GraviT::Logger> m_logger;
public:
    Renderer() : m_window(nullptr), m_logger(std::make_unique<GraviT::Logger>("Renderer")) {}
    
    int Init();
    int Start();
    int AssignWindow(GLFWwindow* window);
};

}

#endif /* Renderer_h */
