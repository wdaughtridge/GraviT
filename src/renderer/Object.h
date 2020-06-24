//
//  Object.h
//  GraviT
//
//  Created by William Daughtridge on 6/16/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#ifndef Object_h
#define Object_h

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Mat4.h"
#include "ShaderProgram.h"
#include "Texture.h"

namespace GraviT {

class Object {
private:
    GraviT::VertexArray m_vao;
    GraviT::VertexBuffer m_vbo;
    GraviT::ElementBuffer m_ebo;
    int m_numIndices;
    
    glm::mat4 m_model;
public:
    struct VertexData {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 textureCoord;
        glm::vec2 sheetIndex;
        float textureNum;
        glm::vec3 normal;
    };
    struct QuadBatch {
        std::vector<Object::VertexData> vertices;
        std::vector<unsigned int> indices;
    };

    Object(const void* vertices, const void* indices, const GLenum dataType, const int numVertices, const int numIndices) : m_model(1.0f) {
        m_vao.Bind();
        m_vbo.Bind();
        m_vbo.BufferData(vertices, sizeof(VertexData) * numVertices, dataType);
        m_ebo.Bind();
        m_ebo.BufferData(indices, sizeof(unsigned int) * numIndices, dataType);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(glm::vec3)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(glm::vec3) + sizeof(glm::vec4)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec2) + sizeof(glm::vec2)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec2) + sizeof(glm::vec2) + sizeof(float)));
        glEnableVertexAttribArray(4);
    }
    
    Object(const std::vector<Object::VertexData>& vertices, const std::vector<unsigned int>& indices, const GLenum dataType) : m_model(1.0f),  m_numIndices((int)indices.size()) {
        m_vao.Bind();
        m_vbo.Bind();
        m_vbo.BufferData(vertices.data(), sizeof(VertexData) * (int)vertices.size(), dataType);
        m_ebo.Bind();
        m_ebo.BufferData(indices.data(), sizeof(unsigned int) * (int)indices.size(), dataType);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(glm::vec3)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(glm::vec3) + sizeof(glm::vec4)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec2) + sizeof(glm::vec2)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec2) + sizeof(glm::vec2) + sizeof(float)));
        glEnableVertexAttribArray(4);
    }
    
    Object(const int numVertices) : m_model(1.0f) {
        m_vao.Bind();
        m_vbo.Bind();
        m_vbo.BufferData(nullptr, numVertices * sizeof(VertexData), GL_DYNAMIC_DRAW);
        m_ebo.Bind();
        //TODO: very hacky
        m_ebo.BufferData(nullptr, sizeof(unsigned int) * (numVertices/4) * 6, GL_DYNAMIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(glm::vec3)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(glm::vec3) + sizeof(glm::vec4)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec2) + sizeof(glm::vec2)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec2) + sizeof(glm::vec2) + sizeof(float)));
        glEnableVertexAttribArray(4);
    }
    
    ~Object() {
        m_vao.Delete();
        m_vbo.Delete();
        m_ebo.Delete();
    }
    
    void UpdateVertexBufferData(const std::vector<GraviT::Object::VertexData>& vertices, const int offset = 0) const;
    void UpdateElementBufferData(const std::vector<unsigned int>& indices, const int offset = 0) const;
    
    void Draw(const GraviT::ShaderProgram& prog, const GraviT::Texture& tex) const;
    void Draw(const GraviT::ShaderProgram& prog) const;
    void SetPos(const glm::vec3 newPosition);
    void SetRotation(const float deg, const glm::vec3 axis);
    void ResetModel();
    
    static glm::vec2 NormalizeTextureCoord(const GraviT::Texture& texture, const glm::vec2 sheetIndex, const glm::vec2 texCoord, const int numPixelsBetweenSprites = 1);
    static std::vector<Object::VertexData> GenerateQuad(const int size, const glm::vec3 pos, const glm::vec4 color);
    static std::vector<Object::VertexData> GenerateQuad(const int size, const glm::vec3 pos, const GraviT::Texture& tex, const bool normalize, const float textureNum, const glm::vec2 sheetIndex);
    static QuadBatch GetQuadBatch(std::vector<std::vector<Object::VertexData>> quadsToBatch, const bool frontCulling);
};

}

#endif /* Object_h */
