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
        glm::vec2 textureIndex;
    };
    struct QuadBatch {
        std::vector<Object::VertexData> vertices;
        std::vector<unsigned int> indices;
    };

    Object(const void* vertices, const void* indices, const GLenum dataType, const int numVertices, const int numIndices) {
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
    }
    
    Object(const std::vector<Object::VertexData>& vertices, const std::vector<unsigned int>& indices, const GLenum dataType) : m_numIndices((int)indices.size()) {
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
    }
    
    Object(const int numVertices) {
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
    }
    
    ~Object() {
        m_vao.Delete();
        m_vbo.Delete();
        m_ebo.Delete();
    }
    
    void UpdateVertexBufferData(const std::vector<GraviT::Object::VertexData>& vertices, const int offset = 0) const;
    void UpdateElementBufferData(const std::vector<unsigned int>& indices, const int offset = 0) const;
    
    int Draw(GraviT::ShaderProgram& prog, GraviT::Texture& tex);
    int DrawAtPos(GraviT::ShaderProgram& prog, glm::vec3 pos);
    int DrawAtPos(GraviT::ShaderProgram& prog, GraviT::Texture& tex, glm::vec3 pos);
    int DrawAtPos(GraviT::ShaderProgram& prog, glm::vec3 pos, float degrees);
    
    static glm::vec2 NormalizeTextureCoord(const GraviT::Texture& texture, const glm::vec2 sheetIndex, const glm::vec2 texCoord, const int numPixelsBetweenSprites = 1);
    static std::vector<Object::VertexData> GenerateQuad(const int size, const glm::vec3 pos, const glm::vec3 upOrientation, const glm::vec4 color);
    static std::vector<Object::VertexData> GenerateQuad(const int size, const glm::vec3 pos, const glm::vec3 upOrientation, const GraviT::Texture& tex, const glm::vec2 sheetIndex = glm::vec2());
    static QuadBatch GetQuadBatch(std::vector<std::vector<Object::VertexData>> quadsToBatch);
};

}

#endif /* Object_h */







//    Object (std::initializer_list<float> vertexData, glm::vec3 position, std::initializer_list<unsigned int> indexData, GraviT::Texture& spriteSheet, glm::vec2 spriteIndex = glm::vec2(0, 0), const int vCount = 3, const int cCount = 3, const int tCount = 2)
//    : m_spriteSheet(spriteSheet), m_model(1.0f)
//    {
//        m_attribTotalCount = m_vertexCount + m_colorCount + m_textureCount;
//        int numRows = (int)vertexData.size() / m_attribTotalCount;
//
//        glm::vec2 sheetDimensions = m_spriteSheet.GetDimensions();
//        float spriteSize = 16.0f;
//
//        float x_pixel = ((spriteSize * spriteIndex.x) + spriteIndex.x) / sheetDimensions.x;
//        float y_pixel = ((spriteSize * spriteIndex.y) + spriteIndex.y) / sheetDimensions.y;
//
//        float index;
//        float blockRatioX = 16.0f/sheetDimensions.x;
//        float blockRatioY = 16.0f/sheetDimensions.y;
//
//        for (float i = 0.0f; i < numRows; i++) {
//            index = (i * m_attribTotalCount) + vCount + cCount;
//            m_vertexData[index] = x_pixel + m_vertexData[index]*(blockRatioX);
//            m_vertexData[index + 1] = y_pixel + m_vertexData[index + 1]*(blockRatioY);
//        }
//
//        // go ahead and fill the buffers with the passed in data
//        m_vao.Bind();
//        m_vbo.Bind();
//        m_vbo.BufferData(m_vertexData.data(), (int)(sizeof(float)*m_vertexData.size()), GL_STATIC_DRAW);
//        m_ebo.Bind();
//        m_ebo.BufferData(m_indexData.data(), (int)(sizeof(unsigned int)*m_indexData.size()));
//
//        glVertexAttribPointer(0, m_vertexCount, GL_FLOAT, GL_FALSE, m_attribTotalCount * sizeof(float), (void*)0);
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(1, m_colorCount, GL_FLOAT, GL_FALSE, m_attribTotalCount * sizeof(float), (void*)(m_vertexCount * sizeof(float)));
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer(2, m_textureCount, GL_FLOAT, GL_FALSE, m_attribTotalCount * sizeof(float), (void*)((m_colorCount + m_vertexCount) * sizeof(float)));
//        glEnableVertexAttribArray(2);
//    }
//
//    Object (std::initializer_list<float> vertexData, glm::vec3 position, std::initializer_list<unsigned int> indexData, const int vCount = 3, const int cCount = 3, const int tCount = 2)
//    : m_spriteSheet(nullptr), m_position(position), m_model(1.0f), m_spriteIndex(glm::vec2(0.0f, 0.0f))
//    {
//        m_attribTotalCount = m_vertexCount + m_colorCount + m_textureCount;
//        // go ahead and fill the buffers with the passed in data
//        m_vao.Bind();
//        m_vbo.Bind();
//        m_vbo.BufferData(m_vertexData.data(), (int)(sizeof(float)*m_vertexData.size()));
//        m_ebo.Bind();
//        m_ebo.BufferData(m_indexData.data(), (int)(sizeof(unsigned int)*m_indexData.size()));
//
//        glVertexAttribPointer(0, m_vertexCount, GL_FLOAT, GL_FALSE, m_attribTotalCount * sizeof(float), (void*)0);
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(1, m_colorCount, GL_FLOAT, GL_FALSE, m_attribTotalCount * sizeof(float), (void*)(m_vertexCount * sizeof(float)));
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer(2, m_textureCount, GL_FLOAT, GL_FALSE, m_attribTotalCount * sizeof(float), (void*)((m_colorCount + m_vertexCount) * sizeof(float)));
//        glEnableVertexAttribArray(2);
//    }
//
//    Object ()
//    : m_spriteSheet(nullptr), m_position(position), m_model(1.0f), m_spriteIndex(glm::vec2(0.0f, 0.0f))
//    {
//        m_attribTotalCount = m_vertexCount + m_colorCount + m_textureCount;
//        // go ahead and fill the buffers with the passed in data
//        m_vao.Bind();
//        m_vbo.Bind();
//        m_vbo.BufferData(m_vertexData.data(), (int)(sizeof(float)*m_vertexData.size()), dataType);
//        m_ebo.Bind();
//        m_ebo.BufferData(m_indexData.data(), (int)(sizeof(unsigned int)*m_indexData.size()));
//
//        glVertexAttribPointer(0, m_vertexCount, GL_FLOAT, GL_FALSE, m_attribTotalCount * sizeof(float), (void*)0);
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(1, m_colorCount, GL_FLOAT, GL_FALSE, m_attribTotalCount * sizeof(float), (void*)(m_vertexCount * sizeof(float)));
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer(2, m_textureCount, GL_FLOAT, GL_FALSE, m_attribTotalCount * sizeof(float), (void*)((m_colorCount + m_vertexCount) * sizeof(float)));
//        glEnableVertexAttribArray(2);
//    }
