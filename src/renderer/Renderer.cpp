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
    
    if (m_enableCulling)
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
    
    GraviT::ShaderProgram program("shaders/texture.vert", "shaders/texture.frag");
    
    std::cout << "Current OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    
    GraviT::Texture cobblestone("asset/cobblestone.jpg");
    GraviT::Texture diamond("asset/texture.jpg");
    GraviT::Texture sprsht("asset/spritesheet.jpg", 16);
    
    std::vector<std::vector<Object::VertexData>> floor;
    std::vector<std::vector<Object::VertexData>> ceil;
    std::vector<std::vector<Object::VertexData>> wall;
    
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            floor.push_back(GraviT::Object::GenerateQuad(4, glm::vec3(i * 4, j * 4, 0.0f), sprsht, true, 1.0f, glm::vec2(8.0f, 10.0f)));
            ceil.push_back(GraviT::Object::GenerateQuad(4, glm::vec3(i * 4, j * 4, 0.0f), sprsht, true, 1.0f, glm::vec2(1.0f, 1.0f)));
            if (j < 50)
                wall.push_back(GraviT::Object::GenerateQuad(4, glm::vec3(i * 4, j * 4, 0.0f), sprsht, true, 1.0f, glm::vec2(16.0f, 7.0f)));
        }
    }
    
    Object::QuadBatch floorBatch = Object::GetQuadBatch(floor, false);
    Object::QuadBatch ceilBatch = Object::GetQuadBatch(ceil, true);
    
    GraviT::Object texFloor(floorBatch.vertices, floorBatch.indices, GL_STATIC_DRAW);
    GraviT::Object texCeil(ceilBatch.vertices, ceilBatch.indices, GL_STATIC_DRAW);
    
    texFloor.SetPos(glm::vec3(0.0f, 0.0f, 400.0f));
    texFloor.SetRotation(-90, glm::vec3(1.0f, 0.0f, 0.0f));
    texCeil.SetPos(glm::vec3(0.0f, 200.0f, 0.0f));
    texCeil.SetRotation(90, glm::vec3(1.0f, 0.0f, 0.0f));
    
    Object::QuadBatch wallBatch0 = Object::GetQuadBatch(wall, true);
    Object::QuadBatch wallBatch1 = Object::GetQuadBatch(wall, true);
    Object::QuadBatch wallBatch2 = Object::GetQuadBatch(wall, true);
    Object::QuadBatch wallBatch3 = Object::GetQuadBatch(wall, true);
    
    GraviT::Object texWall0(wallBatch0.vertices, wallBatch0.indices, GL_STATIC_DRAW);
    GraviT::Object texWall1(wallBatch1.vertices, wallBatch1.indices, GL_STATIC_DRAW);
    GraviT::Object texWall2(wallBatch2.vertices, wallBatch2.indices, GL_STATIC_DRAW);
    GraviT::Object texWall3(wallBatch3.vertices, wallBatch3.indices, GL_STATIC_DRAW);
    
    texWall0.SetPos(glm::vec3(400.0f, 0.0f, 400.0f));
    texWall0.SetRotation(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    
    texWall1.SetPos(glm::vec3(400.0f, 0.0f, 0.0f));
    texWall1.SetRotation(-90, glm::vec3(0.0f, 1.0f, 0.0f));
    
    texWall3.SetPos(glm::vec3(0.0f, 0.0f, 400.0f));
    texWall3.SetRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
 
    // unbind the current vao and vbo
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    program.Use();
    
    glActiveTexture(GL_TEXTURE0);
    cobblestone.Bind();
    glActiveTexture(GL_TEXTURE1);
    sprsht.Bind();
    glActiveTexture(GL_TEXTURE2);
    diamond.Bind();
    
    int samplers[3] = {0, 1, 2};
    program.setUniform1iv("uTexture", 3, samplers);
    
    GraviT::Camera cam(m_window, &program, false, glm::vec3(0.0f, 2.0f, 6.0f));
    
    while (!m_window->ShouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cam.HandleInput();
        
        program.setUniform3f("lightColor", 0.8f, 0.8f, 0.8f);
        program.setUniform3f("viewPos", cam.m_cameraPosition.x, cam.m_cameraPosition.y, cam.m_cameraPosition.z);
        program.setUniform3f("lightPos", cam.m_cameraPosition.x, cam.m_cameraPosition.y, cam.m_cameraPosition.z);
        
        texWall0.Draw(program);
        texWall1.Draw(program);
        texWall2.Draw(program);
        texWall3.Draw(program);
        texFloor.Draw(program);
        texCeil.Draw(program);
        
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
