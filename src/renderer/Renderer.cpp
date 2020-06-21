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
void GraviT::Renderer::Init() const {
    glewExperimental = GL_TRUE;
    if(glewInit()) {
        m_logger->ErrorLog(FILELOC, "glew was not initialized.");
    }
}

void GraviT::Renderer::Start() const {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    
    GraviT::ShaderProgram program("shaders/texture.vert", "shaders/texture.frag");
    GraviT::ShaderProgram program2("shaders/red.vert", "shaders/red.frag");
    
    GraviT::Texture cobblestone("asset/cobblestone.jpg");
    GraviT::Texture diamond("asset/texture.jpg");
    GraviT::Texture sprsht("asset/spritesheet.jpg", 16);
    
    Object::VertexData vertex0;
    vertex0.position = glm::vec3(0.0f, 0.0f, 0.0f);
    vertex0.color = glm::vec4();
    vertex0.textureCoord = Object::NormalizeTextureCoord(sprsht, glm::vec2(9.0f, 9.0f), glm::vec2(0.0f, 0.0f));
    vertex0.textureIndex = glm::vec2(0.0f, 0.0f);
    
    Object::VertexData vertex1;
    vertex1.position = glm::vec3(1.0f, 0.0f, 0.0f);
    vertex1.color = glm::vec4();
    vertex1.textureCoord = Object::NormalizeTextureCoord(sprsht, glm::vec2(9.0f, 9.0f), glm::vec2(1.0f, 0.0f));
    vertex1.textureIndex = glm::vec2(0.0f, 0.0f);
    
    Object::VertexData vertex2;
    vertex2.position = glm::vec3(0.0f, 1.0f, 0.0f);
    vertex2.color = glm::vec4();
    vertex2.textureCoord = Object::NormalizeTextureCoord(sprsht, glm::vec2(9.0f, 9.0f), glm::vec2(0.0f, 1.0f));
    vertex2.textureIndex = glm::vec2(0.0f, 0.0f);
    
    Object::VertexData vertex3;
    vertex3.position = glm::vec3(1.0f, 1.0f, 0.0f);
    vertex3.color = glm::vec4();
    vertex3.textureCoord = Object::NormalizeTextureCoord(sprsht, glm::vec2(9.0f, 9.0f), glm::vec2(1.0f, 1.0f));
    vertex3.textureIndex = glm::vec2(0.0f, 0.0f);
    
    std::vector<Object::VertexData> vertices{vertex0, vertex1, vertex2, vertex3};
    
    std::vector<unsigned int> indices{
        3, 1, 0,
        2, 3, 0
    };
    
    GraviT::Object stone(vertices, indices, GL_DYNAMIC_DRAW);
 
    // unbind the current vao and vbo
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    program.Use();
    program.setUniform1i("ourTexture", 0);
    
    GraviT::Camera cam(m_window, &program, false, glm::vec3(0.0f, 0.0f, 6.0f));
    
    program.setUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(glm::perspective(glm::radians(45.0f), (float)m_window->windowDimensions.m_width / (float)m_window->windowDimensions.m_height, 0.1f, 100.0f)));
    
    while (!m_window->ShouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cam.HandleInput();
        
        stone.Draw(program, sprsht);

        m_window->SwapBuffers();
        glfwPollEvents();
    }

    program.Delete();
}

void GraviT::Renderer::UnbindCurrent() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GraviT::Renderer::Draw(const GraviT::VertexArray &vao, const GraviT::ElementBuffer &ebo, const GraviT::ShaderProgram &program) const {
    vao.Bind();
    ebo.Bind();
    program.Use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
