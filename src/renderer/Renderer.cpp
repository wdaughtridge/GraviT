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
    
    std::vector<Object::VertexData> vertices = GraviT::Object::GenerateQuad(4, glm::vec3(), glm::vec4(), sprsht, glm::vec2(9,9));
    std::vector<unsigned int> indices{3, 1, 0, 2, 3, 0};
    
    std::vector<std::vector<Object::VertexData>> wall;
    
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            wall.push_back(GraviT::Object::GenerateQuad(4, glm::vec3(i * 4, j * 4, 0.0f), glm::vec4(), sprsht, glm::vec2()));
        }
    }
    
    Object::QuadBatch wallBatch = Object::GetQuadBatch(wall);
    
    GraviT::Object blueWall(wallBatch.vertices, wallBatch.indices, GL_DYNAMIC_DRAW);
 
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
        
        blueWall.Draw(program, sprsht);

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
