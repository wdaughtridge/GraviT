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
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include "Logger.h"
#include "Window.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Object.h"
#include "Mat4.h"
#include "Camera.h"

namespace GraviT {

class Renderer {
private:
    std::shared_ptr<GraviT::Window> m_window;
    std::unique_ptr<GraviT::Logger> m_logger;
    
    double x_pos;
    double y_pos;
public:
    Renderer(std::shared_ptr<GraviT::Window> window) : m_window(window), m_logger(std::make_unique<GraviT::Logger>("Renderer")) {}
    
    int Init() const;
    int Start() const;
    void UnbindCurrent() const;
    int Draw(GraviT::VertexArray& vao, GraviT::ElementBuffer& ebo, GraviT::ShaderProgram& program) const;
};

}

#endif /* Renderer_h */
