//
//  Object.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/16/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "Object.h"

// TRANSFORMATION ----------------------------------------------------------

void GraviT::Object::SetRotation(const float deg, const glm::vec3 axis) {
    float rad = deg * 3.14159f / 180.0f;
    
    m_model = glm::rotate(m_model, rad, axis);
}

void GraviT::Object::ResetModel() {
    m_model = glm::mat4(1.0f);
}

void GraviT::Object::SetPos(const glm::vec3 newPosition) {
    m_model = glm::translate(m_model, newPosition);
}

// -------------------------------------------------------------------------

// DRAW --------------------------------------------------------------------

void GraviT::Object::Draw(const GraviT::ShaderProgram& prog, const GraviT::Texture& tex) const {
    tex.Bind();
    
    prog.setUniformMatrix4fv("transformation", 1, GL_FALSE, glm::value_ptr(m_model));
    
    m_vao.Bind();
    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
}

void GraviT::Object::Draw(const GraviT::ShaderProgram& prog) const {
    prog.setUniformMatrix4fv("transformation", 1, GL_FALSE, glm::value_ptr(m_model));
    
    m_vao.Bind();
    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
}

void GraviT::Object::DrawAtPos(const GraviT::ShaderProgram& prog, glm::vec3 pos) const {
    glm::mat4 newPos = glm::mat4(1.0);
    newPos = glm::translate(newPos, pos);
    prog.setUniformMatrix4fv("transformation", 1, GL_FALSE, glm::value_ptr(newPos));
    
    m_vao.Bind();
    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
}
// -------------------------------------------------------------------------

// DYNAMIC DATA ------------------------------------------------------------

void GraviT::Object::UpdateVertexBufferData(const std::vector<GraviT::Object::VertexData>& vertices, const int offset) const {
    m_vbo.Bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(VertexData) * vertices.size(), vertices.data());
}

void GraviT::Object::UpdateElementBufferData(const std::vector<unsigned int>& indices, const int offset) const {
    m_vbo.Bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, sizeof(unsigned int) * indices.size(), indices.data());
}

// -------------------------------------------------------------------------

// UTILITY -----------------------------------------------------------------

glm::vec2 GraviT::Object::NormalizeTextureCoord(const GraviT::Texture& texture, const glm::vec2 sheetIndex, const glm::vec2 texCoord, const int numPixelsBetweenSprites) {
    glm::vec2 textureDimensions = texture.GetDimensions();
    int spriteSizePx = texture.GetSubTexSize();
    
    return glm::vec2(((sheetIndex.x+texCoord.x) * spriteSizePx + (sheetIndex.x*numPixelsBetweenSprites))/textureDimensions.x,
                     ((sheetIndex.y+texCoord.y) * spriteSizePx + (sheetIndex.y*numPixelsBetweenSprites))/textureDimensions.y);
}

std::vector<GraviT::Object::VertexData> GraviT::Object::GenerateQuadVertices(const int size, const glm::vec3 pos, const glm::vec4 color) {
    Object::VertexData vertex0;
    vertex0.position = glm::vec3(0.0f + pos.x, 0.0f + pos.y, 0.0f + pos.z);
    vertex0.color = color;
    vertex0.textureCoord = glm::vec2(0.0f, 0.0f);
    vertex0.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex0.textureNum = 0.0f;
    vertex0.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    
    Object::VertexData vertex1;
    vertex1.position = glm::vec3(1.0f * size + pos.x, 0.0f + pos.y, 0.0f + pos.z);
    vertex1.color = color;
    vertex1.textureCoord = glm::vec2(0.0f, 0.0f);
    vertex1.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex1.textureNum = 0.0f;
    vertex1.normal = glm::vec3(0.0f, 0.0f, 1.0f);

    Object::VertexData vertex2;
    vertex2.position = glm::vec3(0.0f + pos.x, 1.0f * size + pos.y, 0.0f + pos.z);
    vertex2.color = color;
    vertex2.textureCoord = glm::vec2(0.0f, 0.0f);
    vertex2.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex2.textureNum = 0.0f;
    vertex2.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    
    Object::VertexData vertex3;
    vertex3.position = glm::vec3(1.0f * size + pos.x, 1.0f * size + pos.y, 0.0f + pos.z);
    vertex3.color = color;
    vertex3.textureCoord = glm::vec2(0.0f, 0.0f);
    vertex3.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex3.textureNum = 0.0f;
    vertex3.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    
    return std::vector<GraviT::Object::VertexData>{vertex0, vertex1, vertex2, vertex3};
}

std::vector<GraviT::Object::VertexData> GraviT::Object::GenerateQuadVertices(const int size, const glm::vec3 pos, const GraviT::Texture& tex, const bool normalize, const float textureNum, const glm::vec2 sheetIndex, const int numPixelsBetweenSprts) {
    Object::VertexData vertex0;
    vertex0.position = glm::vec3(0.0f + pos.x, 0.0f + pos.y, 0.0f + pos.z);
    vertex0.color = glm::vec4();
    if (normalize)
        vertex0.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(0.0f, 0.0f), numPixelsBetweenSprts);
    else
        vertex0.textureCoord = glm::vec2();
    vertex0.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex0.textureNum = textureNum;
    vertex0.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    
    Object::VertexData vertex1;
    vertex1.position = glm::vec3(1.0f * size + pos.x, 0.0f + pos.y, 0.0f + pos.z);
    vertex1.color = glm::vec4();
    if (normalize)
        vertex1.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(1.0f, 0.0f), numPixelsBetweenSprts);
    else
        vertex1.textureCoord = glm::vec2(1.0f, 0.0f);
    vertex1.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex1.textureNum = textureNum;
    vertex1.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    
    Object::VertexData vertex2;
    vertex2.position = glm::vec3(0.0f + pos.x, 1.0f * size + pos.y, 0.0f + pos.z);
    vertex2.color = glm::vec4();
    if (normalize)
        vertex2.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(0.0f, 1.0f), numPixelsBetweenSprts);
    else
        vertex2.textureCoord = glm::vec2(0.0f, 1.0f);
    vertex2.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex2.textureNum = textureNum;
    vertex2.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    
    Object::VertexData vertex3;
    vertex3.position = glm::vec3(1.0f * size + pos.x, 1.0f * size + pos.y, 0.0f + pos.z);
    vertex3.color = glm::vec4();
    if (normalize)
        vertex3.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(1.0f, 1.0f), numPixelsBetweenSprts);
    else
        vertex3.textureCoord = glm::vec2(1.0f, 1.0f);
    vertex3.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex3.textureNum = textureNum;
    vertex3.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    
    return std::vector<GraviT::Object::VertexData>{vertex0, vertex1, vertex2, vertex3};
}

std::vector<GraviT::Object::VertexData> GraviT::Object::GenerateCubeVertices(const int size, const glm::vec3 pos, const GraviT::Texture& tex, const bool normalize, const float textureNum, const glm::vec2 sheetIndex, const int numPixelsBetweenSprts) {
    std::vector<GraviT::Object::VertexData> vertices;
    Object::VertexData vertex;
    
    // FIRST QUAD -----------------------------------------------------------------
    // ----------------------------------------------------------------------------
    vertex.position = glm::vec3(0.0f + pos.x, 0.0f + pos.y, 0.0f + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(0.0f, 0.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2();
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    vertex.position = glm::vec3(1.0f * size + pos.x, 0.0f + pos.y, 0.0f + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(1.0f, 0.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2(1.0f, 0.0f);
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    vertex.position = glm::vec3(0.0f + pos.x, 1.0f * size + pos.y, 0.0f + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(0.0f, 1.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2(0.0f, 1.0f);
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    vertex.position = glm::vec3(1.0f * size + pos.x, 1.0f * size + pos.y, 0.0f + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(1.0f, 1.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2(1.0f, 1.0f);
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    // SECOND QUAD -----------------------------------------------------------------
    // ----------------------------------------------------------------------------
    vertex.position = glm::vec3(1.0f * size + pos.x, 0.0f + pos.y, 1.0f * size + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(0.0f, 0.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2();
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    vertex.position = glm::vec3(0.0f + pos.x, 0.0f + pos.y, 1.0f * size + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(1.0f, 0.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2(1.0f, 0.0f);
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    vertex.position = glm::vec3(1.0f * size + pos.x, 1.0f * size + pos.y, 1.0f * size + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(0.0f, 1.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2(0.0f, 1.0f);
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    vertex.position = glm::vec3(0.0f + pos.x, 1.0f * size + pos.y, 1.0f * size + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(1.0f, 1.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2(1.0f, 1.0f);
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    // THIRD QUAD -----------------------------------------------------------------
    // ----------------------------------------------------------------------------
    vertex.position = glm::vec3(1.0f * size + pos.x, 0.0f + pos.y, 0.0f + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(0.0f, 0.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2();
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    vertex.position = glm::vec3(1.0f * size + pos.x, 0.0f + pos.y, 1.0f * size + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(1.0f, 0.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2(1.0f, 0.0f);
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    vertex.position = glm::vec3(1.0f * size + pos.x, 1.0f * size + pos.y, 0.0f + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(0.0f, 1.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2(0.0f, 1.0f);
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    vertex.position = glm::vec3(1.0f * size + pos.x, 1.0f * size + pos.y, 1.0f * size + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(1.0f, 1.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2(1.0f, 1.0f);
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    // FOURTH QUAD -----------------------------------------------------------------
    // ----------------------------------------------------------------------------
    vertex.position = glm::vec3(0.0f + pos.x, 0.0f + pos.y, 1.0f * size + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(0.0f, 0.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2();
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    vertex.position = glm::vec3(0.0f + pos.x, 0.0f + pos.y, 0.0f + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(1.0f, 0.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2(1.0f, 0.0f);
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    vertex.position = glm::vec3(0.0f + pos.x, 1.0f * size + pos.y, 1.0f * size + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(0.0f, 1.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2(0.0f, 1.0f);
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    vertex.position = glm::vec3(0.0f + pos.x, 1.0f * size + pos.y, 0.0f + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(1.0f, 1.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2(1.0f, 1.0f);
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    // FIFTH QUAD -----------------------------------------------------------------
    // ----------------------------------------------------------------------------
    vertex.position = glm::vec3(0.0f + pos.x, 1.0f * size + pos.y, 0.0f + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(0.0f, 0.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2();
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    vertex.position = glm::vec3(1.0f * size + pos.x, 1.0f * size + pos.y, 0.0f + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(1.0f, 0.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2(1.0f, 0.0f);
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    vertex.position = glm::vec3(0.0f + pos.x, 1.0f * size + pos.y, 1.0f * size + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(0.0f, 1.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2(0.0f, 1.0f);
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    vertex.position = glm::vec3(1.0f * size + pos.x, 1.0f * size + pos.y, 1.0f * size + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(1.0f, 1.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2(1.0f, 1.0f);
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    // SIXTH QUAD -----------------------------------------------------------------
    // ----------------------------------------------------------------------------
    vertex.position = glm::vec3(0.0f + pos.x, 0.0f + pos.y, 1.0f * size + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(0.0f, 0.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2();
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    vertex.position = glm::vec3(1.0f * size + pos.x, 0.0f + pos.y, 1.0f * size + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(1.0f, 0.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2(1.0f, 0.0f);
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    vertex.position = glm::vec3(0.0f + pos.x, 0.0f + pos.y, 0.0f + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(0.0f, 1.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2(0.0f, 1.0f);
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    vertex.position = glm::vec3(1.0f * size + pos.x, 0.0f + pos.y, 0.0f + pos.z);
    vertex.color = glm::vec4();
    if (normalize)
        vertex.textureCoord = Object::NormalizeTextureCoord(tex, sheetIndex, glm::vec2(1.0f, 1.0f), numPixelsBetweenSprts);
    else
        vertex.textureCoord = glm::vec2(1.0f, 1.0f);
    vertex.sheetIndex = glm::vec2(0.0f, 0.0f);
    vertex.textureNum = textureNum;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(vertex);
    
    return vertices;
}

std::vector<unsigned int> GraviT::Object::GenerateQuadIndices(const int numQuads, const bool frontCulling) {
    std::vector<unsigned int> indices;
    
    if (frontCulling) {
        for (int i = 0; i < numQuads; i++) {
            indices.push_back(3 + i*4);
            indices.push_back(1 + i*4);
            indices.push_back(0 + i*4);
            indices.push_back(2 + i*4);
            indices.push_back(3 + i*4);
            indices.push_back(0 + i*4);
        }
    }
    else {
        for (int i = 0; i < numQuads; i++) {
            indices.push_back(0 + i*4);
            indices.push_back(1 + i*4);
            indices.push_back(3 + i*4);
            indices.push_back(0 + i*4);
            indices.push_back(3 + i*4);
            indices.push_back(2 + i*4);
        }
    }
    
    return indices;
}

std::vector<unsigned int> GraviT::Object::GenerateCubeIndices(const int numCubes, const bool frontCulling) {
    std::vector<unsigned int> indices;
    
    if (frontCulling) {
        for (int i = 0; i < numCubes * 6; i++) {
            indices.push_back(3 + i*4);
            indices.push_back(1 + i*4);
            indices.push_back(0 + i*4);
            indices.push_back(2 + i*4);
            indices.push_back(3 + i*4);
            indices.push_back(0 + i*4);
        }
    }
    else {
        for (int i = 0; i < numCubes * 6; i++) {
            indices.push_back(0 + i*4);
            indices.push_back(1 + i*4);
            indices.push_back(2 + i*4);
            indices.push_back(0 + i*4);
            indices.push_back(3 + i*4);
            indices.push_back(2 + i*4);
        }
    }
    
    return indices;
}

// -------------------------------------------------------------------------

// BATCHING ----------------------------------------------------------------

GraviT::Object::Batch GraviT::Object::GetQuadBatch(std::vector<std::vector<Object::VertexData>> quadsToBatch, const bool frontCulling) {
    std::vector<Object::VertexData> vertices;
    std::vector<unsigned int> indices;
    
    for (auto q : quadsToBatch) {
        for (auto r : q) {
            vertices.push_back(r);
        }
    }
    
    indices = GraviT::Object::GenerateQuadIndices((int)quadsToBatch.size(), frontCulling);
    
    return {vertices, indices};
}

GraviT::Object::Batch GraviT::Object::GetCubeBatch(std::vector<std::vector<Object::VertexData>> cubesToBatch, const bool frontCulling) {
    std::vector<Object::VertexData> vertices;
    std::vector<unsigned int> indices;
    
    for (auto q : cubesToBatch) {
        for (auto r : q) {
            vertices.push_back(r);
        }
    }
    
    indices = GraviT::Object::GenerateCubeIndices((int)cubesToBatch.size(), frontCulling);
    
    return {vertices, indices};
}
// -------------------------------------------------------------------------
