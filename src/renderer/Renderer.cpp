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
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    
    // create program with shaders from files
    GraviT::Shader frag(Shader::Fragment, "shaders/rainbow.frag");
    GraviT::Shader vert(Shader::Vertex, "shaders/rainbow.vert");
    GraviT::ShaderProgram program(vert, frag);
    
    // create program with shaders from files
    GraviT::Shader frag2(Shader::Fragment, "shaders/red.frag");
    GraviT::Shader vert2(Shader::Vertex, "shaders/red.vert");
    GraviT::ShaderProgram program2(vert2, frag2);
    
    GraviT::Texture cobblestone("asset/cobblestone.jpg");
    GraviT::Texture diamond("asset/texture.jpg");
    GraviT::Texture sprsht("asset/spritesheet.jpg");
    
    GraviT::Object dirt(
    {
        1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 1.0f,    1.0, 1.0,
        1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0, 0.0,
        0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0, 0.0,
        0.0f, 1.0f, 0.0f,    1.0f, 0.0f, 1.0f,    0.0, 1.0
    }, glm::vec3(0.0f, 0.0f, 0.0f),
    {
        0, 1, 3,
        1, 2, 3
    }, sprsht, glm::vec2(9.0f, 9.0f));
    GraviT::Object stone(
    {
        1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 1.0f,    1.0, 1.0,
        1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0, 0.0,
        0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0, 0.0,
        0.0f, 1.0f, 0.0f,    1.0f, 0.0f, 1.0f,    0.0, 1.0
    }, glm::vec3(0.0f, 0.0f, 0.0f),
    {
        0, 1, 3,
        1, 2, 3
    }, sprsht, glm::vec2(14.0f, 14.0f));
    
    GraviT::Object block3d(
    {
        1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 1.0f,    1.0, 1.0,
        1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0, 0.0,
        0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0, 0.0,
        0.0f, 1.0f, 0.0f,    1.0f, 0.0f, 1.0f,    0.0, 1.0,
        1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f,    1.0, 1.0,
        1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 0.0f,    1.0, 0.0,
        0.0f, 0.0f, 1.0f,    1.0f, 0.0f, 0.0f,    0.0, 0.0,
        0.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f,    0.0, 1.0,

        1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f,    1.0, 1.0,
        1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0, 0.0,
        0.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0, 0.0,
        0.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f,    0.0, 1.0,
        1.0f, 0.0f, 1.0f,    1.0f, 0.0f, 1.0f,    1.0, 1.0,
        1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0, 0.0,
        0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0, 0.0,
        0.0f, 0.0f, 1.0f,    1.0f, 0.0f, 1.0f,    0.0, 1.0,

        1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f,    1.0, 1.0,
        1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 0.0f,    0.0, 1.0,
        1.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0, 0.0,
        1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 1.0f,    1.0, 0.0,
        0.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f,    1.0, 1.0,
        0.0f, 0.0f, 1.0f,    1.0f, 1.0f, 0.0f,    0.0, 1.0,
        0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0, 0.0,
        0.0f, 1.0f, 0.0f,    1.0f, 0.0f, 1.0f,    1.0, 0.0
    }, glm::vec3(0.0f, 0.0f, 0.0f),
    {
        3, 1, 0,
        3, 2, 1,
        4, 5, 7,
        5, 6, 7,
        
        11, 9, 8,
        11, 10, 9,
        12, 13, 15,
        13, 14, 15,

        19, 17, 16,
        19, 18, 17,
        20, 21, 23,
        21, 22, 23
    }, sprsht, glm::vec2(3.0f, 2.0f));
 
    // unbind the current vao and vbo
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    program.Use();
    program.setUniform1i("ourTexture", 0);
    
    GraviT::Camera cam(m_window, &program, true, glm::vec3(0.0f, 0.0f, 4.0f));
    
    program.setUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(glm::perspective(glm::radians(45.0f), (float)m_window->windowDimensions.m_width / (float)m_window->windowDimensions.m_height, 0.1f, 100.0f)));
    
    while (!m_window->ShouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        cam.HandleInput();
        
        for (float i = 0.0f; i < 100.0f; i++) {
            for (float j = 0.0f; j < 100.0f; j++) {
                int test = ((int)j) %2;
                if (test)
                    dirt.DrawAtPos(program, glm::vec3(j, i, 0.0f));
                else
                    stone.DrawAtPos(program, glm::vec3(j, i, 0.0f));
            }
        }
        
        m_window->SwapBuffers();
        glfwPollEvents();
    }

    program.Delete();
    
    return 0;
}

void GraviT::Renderer::UnbindCurrent() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

int GraviT::Renderer::Draw(GraviT::VertexArray &vao, GraviT::ElementBuffer &ebo, GraviT::ShaderProgram &program) const {
    vao.Bind();
    ebo.Bind();
    program.Use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    return 0;
}
