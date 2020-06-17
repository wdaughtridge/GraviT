//
//  Renderer.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/4/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "Renderer.h"

/*
 Initialize GLEW
 */
int GraviT::Renderer::Init() const {
    glewExperimental = GL_TRUE;
    if(glewInit()) {
        m_logger->ErrorLog(FILELOC, "glew was not initialized.");
        return -1;
    }
    
    return 0;
}

int GraviT::Renderer::Start() const {
    GraviT::Mat4 identity(1.0);
    
    // create program with shaders from files
    GraviT::Shader frag(Shader::Fragment, "shaders/rainbow.frag.shader");
    GraviT::Shader vert(Shader::Vertex, "shaders/rainbow.vert.shader");
    GraviT::ShaderProgram program(vert, frag);
    
    // create program with shaders from files
    GraviT::Shader frag2(Shader::Fragment, "shaders/red.frag.shader");
    GraviT::Shader vert2(Shader::Vertex, "shaders/red.vert.shader");
    GraviT::ShaderProgram program2(vert2, frag2);
    
//    GraviT::Texture tex1("asset/texture.png");
    
    std::vector<std::shared_ptr<GraviT::Object_2D>> drawObj;
    
    GraviT::Object_2D test0(
    {0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0, 1.0,
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0, 0.0,
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0, 0.0,
    -0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0, 1.0},
    {0.5f, 0.5f, 0.0f},
    {0, 1, 3,
     1, 2, 3});
    
    GraviT::Object_2D test1(
    {0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0, 1.0,
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0, 0.0,
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0, 0.0,
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0, 1.0},
    {-0.5f, -0.5f, 0.0f},
    {0, 1, 3,
     1, 2, 3});
    
    drawObj.push_back(std::make_shared<GraviT::Object_2D>(test0));
    drawObj.push_back(std::make_shared<GraviT::Object_2D>(test1));
 
    // unbind the current vao and vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
//    program.Use();
//    program.setUniform1i("texture1", 0);
    
    while (!glfwWindowShouldClose(m_window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        for (auto o : drawObj) {
            program2.Use();
            program2.setUniformMatrix4fv("transformation", 1, GL_FALSE, o->translation.m_mat4.data());
            o->Draw();
        }
        
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    program.Delete();
    
    return 0;
}

int GraviT::Renderer::AssignWindow(GLFWwindow *window) {
    if (window == nullptr) return -1;
    
    this->m_window = window;
    
    return 0;
}

int GraviT::Renderer::Draw(GraviT::VertexArray &vao, GraviT::ElementBuffer &ebo, GraviT::ShaderProgram &program) const {
    vao.Bind();
    ebo.Bind();
    program.Use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    return 0;
}
