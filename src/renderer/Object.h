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

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Mat4.h"

namespace GraviT {

class Object_2D {
private:
    std::vector<float> m_vertexData;
    std::vector<float> m_position;
    std::vector<unsigned int> m_indexData;
    
    int vertexCount;
    int colorCount;
    int textureCount;
    int attribTotalCount;
    
    GraviT::VertexArray vao;
    GraviT::VertexBuffer vbo;
    GraviT::ElementBuffer ebo;
public:
    GraviT::Mat4 translation;
    
    Object_2D (std::initializer_list<float> vertexData, std::initializer_list<float> position, std::initializer_list<unsigned int> indexData, const int vCount = 3, const int cCount = 3, const int tCount = 2) : translation(position) {
        vertexCount = vCount;
        colorCount = cCount;
        textureCount = tCount;
        attribTotalCount = vertexCount + colorCount + textureCount;
        
        for (auto c : vertexData) {
            m_vertexData.push_back(c);
        }
        for (auto p : position) {
            m_position.push_back(p);
        }
        for (auto i : indexData) {
            m_indexData.push_back(i);
        }
        
        // go ahead and fill the buffers with the passed in data
        vao.Bind();
        vbo.Bind();
        vbo.BufferData(m_vertexData.data(), (int)(sizeof(float)*m_vertexData.size()));
        ebo.Bind();
        ebo.BufferData(m_indexData.data(), (int)(sizeof(unsigned int)*m_indexData.size()));
        
        glVertexAttribPointer(0, vertexCount, GL_FLOAT, GL_FALSE, attribTotalCount * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, colorCount, GL_FLOAT, GL_FALSE, attribTotalCount * sizeof(float), (void*)(vertexCount * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, textureCount, GL_FLOAT, GL_FALSE, attribTotalCount * sizeof(float), (void*)((colorCount + vertexCount) * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    
    ~Object_2D() {
        vao.Delete();
        vbo.Delete();
        ebo.Delete();
    }
    
    int Draw();
};

class Object_3D {
    
};

}

#endif /* Object_h */
