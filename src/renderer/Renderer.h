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
#include <vector>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include "Logger.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Mat4.h"

namespace GraviT {

class Renderer {
private:
    GLFWwindow* m_window;
    std::unique_ptr<GraviT::Logger> m_logger;
public:
    Renderer() : m_window(nullptr), m_logger(std::make_unique<GraviT::Logger>("Renderer")) {}
    
    int Init() const;
    int Start() const;
    int Draw(GraviT::VertexArray& vao, GraviT::ElementBuffer& ebo, GraviT::ShaderProgram& program, const char* name, const float *mat4) const;
    int AssignWindow(GLFWwindow* window);
};

}

#endif /* Renderer_h */
