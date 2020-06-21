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
    
    prog.setUniformMatrix4fv("transformation", 1, GL_FALSE, glm::value_ptr(m_model));
    
    m_vao.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    return 0;
}

void GraviT::Object::UpdateVertexBufferData(const std::vector<GraviT::Object::VertexData>& vertices, const int offset) const {
    m_vbo.Bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(VertexData) * vertices.size(), vertices.data());
}

void GraviT::Object::UpdateElementBufferData(const std::vector<unsigned int>& indices, const int offset) const {
    m_vbo.Bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(VertexData) * indices.size(), indices.data());
}

glm::vec2 GraviT::Object::NormalizeTextureCoord(const GraviT::Texture& texture, const glm::vec2 sheetIndex, const glm::vec2 texCoord, const int numPixelsBetweenSprites) {
    glm::vec2 textureDimensions = texture.GetDimensions();
    int spriteSizePx = texture.GetSubTexSize();
    
    return glm::vec2(((sheetIndex.x+texCoord.x) * spriteSizePx + (sheetIndex.x*numPixelsBetweenSprites))/textureDimensions.x,
                     ((sheetIndex.y+texCoord.y) * spriteSizePx + (sheetIndex.y*numPixelsBetweenSprites))/textureDimensions.y);
}
