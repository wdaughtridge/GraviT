//
//  ElementBuffer.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/13/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "ElementBuffer.h"

void GraviT::ElementBuffer::Bind() const {
    glBindBuffer(target, m_bufferID);
}

void GraviT::ElementBuffer::BufferData(const void* vertices, const int size) const {
    glBufferData(target, size, vertices, GL_STATIC_DRAW);
}

void GraviT::ElementBuffer::Delete() {
    glDeleteBuffers(1, &m_bufferID);
}
