//
//  Object.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/16/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "Object.h"

int GraviT::Object::Draw(GraviT::ShaderProgram& prog, GraviT::Texture& tex) {
    tex.Bind();
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, m_position);
    
    prog.setUniformMatrix4fv("transformation", 1, GL_FALSE, glm::value_ptr(m_model));
    
    m_vao.Bind();
    glDrawElements(GL_TRIANGLES, (int)m_indexData.size(), GL_UNSIGNED_INT, 0);
    
    return 0;
}

int GraviT::Object::DrawAtPos(GraviT::ShaderProgram& prog, glm::vec3 pos) {
    m_spriteSheet.Bind();
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, pos);
    
    prog.setUniformMatrix4fv("transformation", 1, GL_FALSE, glm::value_ptr(m_model));
    
    m_vao.Bind();
    glDrawElements(GL_TRIANGLES, (int)m_indexData.size(), GL_UNSIGNED_INT, 0);
    
    return 0;
}

int GraviT::Object::DrawAtPos(GraviT::ShaderProgram& prog, GraviT::Texture& tex, glm::vec3 pos) {
    tex.Bind();
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, pos);
    
    prog.setUniformMatrix4fv("transformation", 1, GL_FALSE, glm::value_ptr(m_model));
    
    m_vao.Bind();
    glDrawElements(GL_TRIANGLES, (int)m_indexData.size(), GL_UNSIGNED_INT, 0);
    
    return 0;
}
