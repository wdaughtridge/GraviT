//
//  ElementBuffer.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/13/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "ElementBuffer.h"

int GraviT::ElementBuffer::Bind() const {
    glBindBuffer(target, m_bufferID);
    
    return 0;
}

int GraviT::ElementBuffer::BufferData(const void* vertices, const int size) const {
    glBufferData(target, size, vertices, GL_STATIC_DRAW);
    
    return 0;
}
