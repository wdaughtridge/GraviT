//
//  VertexBuffer.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/13/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "VertexBuffer.h"

int GraviT::VertexBuffer::Bind() const {
    glBindBuffer(m_target, m_bufferID);
    
    return 0;
}

int GraviT::VertexBuffer::BufferData(const void* vertices, const int size) const {
    //TODO: gl_static_draw
    glBufferData(m_target, size, vertices, GL_STATIC_DRAW);
    
    return 0;
}

int GraviT::VertexBuffer::Delete() {
    glDeleteBuffers(1, &m_bufferID);
    
    return 0;
}
