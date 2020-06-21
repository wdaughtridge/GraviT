//
//  VertexBuffer.h
//  GraviT
//
//  Created by William Daughtridge on 6/7/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#ifndef VertexBuffer_h
#define VertexBuffer_h

#include <GL/glew.h>

namespace GraviT {

class VertexBuffer {
private:
    unsigned int m_bufferID;
    GLenum m_target;
public:
    VertexBuffer() : m_target(GL_ARRAY_BUFFER) { glGenBuffers(1, &m_bufferID); }
    
    void Bind() const;
    void Delete();
    void BufferData(const void* vertices, const int size, const GLenum dataType) const;
    void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
};

}

#endif /* VertexBuffer_h */
