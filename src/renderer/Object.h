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
    std::vector<float> m_vertexData;
    std::vector<unsigned int> m_indexData;
    
    int m_vertexCount;
    int m_colorCount;
    int m_textureCount;
    int m_attribTotalCount;
    
    GraviT::VertexArray m_vao;
    GraviT::VertexBuffer m_vbo;
    GraviT::ElementBuffer m_ebo;
    GraviT::Texture m_spriteSheet;
    
    glm::mat4 m_model;
    glm::vec3 m_position;
    glm::vec2 m_spriteIndex;
public:
    
    Object (std::initializer_list<float> vertexData, glm::vec3 position, std::initializer_list<unsigned int> indexData, GraviT::Texture& spriteSheet, glm::vec2 spriteIndex = glm::vec2(0, 0), const int vCount = 3, const int cCount = 3, const int tCount = 2)
    : m_vertexData(vertexData), m_indexData(indexData), m_vertexCount(vCount), m_colorCount(cCount), m_textureCount(tCount), m_spriteSheet(spriteSheet), m_position(position), m_model(1.0f), m_spriteIndex(spriteIndex)
    {
        m_attribTotalCount = m_vertexCount + m_colorCount + m_textureCount;
        int numRows = (int)vertexData.size() / m_attribTotalCount;
        
        glm::vec2 sheetDimensions = m_spriteSheet.GetDimensions();
        float spriteSize = 16.0f;
        
        float x_pixel = ((spriteSize * spriteIndex.x) + spriteIndex.x) / sheetDimensions.x;
        float y_pixel = ((spriteSize * spriteIndex.y) + spriteIndex.y) / sheetDimensions.y;
        
        float index;
        float blockRatioX = 16.0f/sheetDimensions.x;
        float blockRatioY = 16.0f/sheetDimensions.y;
        
        for (float i = 0.0f; i < numRows; i++) {
            index = (i * m_attribTotalCount) + vCount + cCount;
            m_vertexData[index] = x_pixel + m_vertexData[index]*(blockRatioX);
            m_vertexData[index + 1] = y_pixel + m_vertexData[index + 1]*(blockRatioY);
        }
        
        // go ahead and fill the buffers with the passed in data
        m_vao.Bind();
        m_vbo.Bind();
        m_vbo.BufferData(m_vertexData.data(), (int)(sizeof(float)*m_vertexData.size()));
        m_ebo.Bind();
        m_ebo.BufferData(m_indexData.data(), (int)(sizeof(unsigned int)*m_indexData.size()));
        
        glVertexAttribPointer(0, m_vertexCount, GL_FLOAT, GL_FALSE, m_attribTotalCount * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, m_colorCount, GL_FLOAT, GL_FALSE, m_attribTotalCount * sizeof(float), (void*)(m_vertexCount * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, m_textureCount, GL_FLOAT, GL_FALSE, m_attribTotalCount * sizeof(float), (void*)((m_colorCount + m_vertexCount) * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    
    Object (std::initializer_list<float> vertexData, glm::vec3 position, std::initializer_list<unsigned int> indexData, const int vCount = 3, const int cCount = 3, const int tCount = 2)
    : m_vertexData(vertexData), m_indexData(indexData), m_vertexCount(vCount), m_colorCount(cCount), m_textureCount(tCount), m_spriteSheet(nullptr), m_position(position), m_model(1.0f), m_spriteIndex(glm::vec2(0.0f, 0.0f))
    {
        m_attribTotalCount = m_vertexCount + m_colorCount + m_textureCount;
        // go ahead and fill the buffers with the passed in data
        m_vao.Bind();
        m_vbo.Bind();
        m_vbo.BufferData(m_vertexData.data(), (int)(sizeof(float)*m_vertexData.size()));
        m_ebo.Bind();
        m_ebo.BufferData(m_indexData.data(), (int)(sizeof(unsigned int)*m_indexData.size()));
        
        glVertexAttribPointer(0, m_vertexCount, GL_FLOAT, GL_FALSE, m_attribTotalCount * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, m_colorCount, GL_FLOAT, GL_FALSE, m_attribTotalCount * sizeof(float), (void*)(m_vertexCount * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, m_textureCount, GL_FLOAT, GL_FALSE, m_attribTotalCount * sizeof(float), (void*)((m_colorCount + m_vertexCount) * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    
    ~Object() {
        m_vao.Delete();
        m_vbo.Delete();
        m_ebo.Delete();
    }
    
    int Draw(GraviT::ShaderProgram& prog, GraviT::Texture& tex);
    int DrawAtPos(GraviT::ShaderProgram& prog, glm::vec3 pos);
    int DrawAtPos(GraviT::ShaderProgram& prog, GraviT::Texture& tex, glm::vec3 pos);
};

}

#endif /* Object_h */
