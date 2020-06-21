//
//  VertexBuffer.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/13/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "VertexBuffer.h"

void GraviT::VertexBuffer::Bind() const {
    glBindBuffer(m_target, m_bufferID);
}

void GraviT::VertexBuffer::BufferData(const void* vertices, const int size, const GLenum dataType) const {
    glBufferData(m_target, size, vertices, dataType);
}

void GraviT::VertexBuffer::Delete() {
    glDeleteBuffers(1, &m_bufferID);
}
