//
//  ElementBuffer.h
//  GraviT
//
//  Created by William Daughtridge on 6/13/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#ifndef ElementBuffer_h
#define ElementBuffer_h

#include <GL/glew.h>

namespace GraviT {

class ElementBuffer {
private:
    unsigned int m_bufferID;
    GLenum target;
public:
    ElementBuffer() : target(GL_ELEMENT_ARRAY_BUFFER) { glGenBuffers(1, &m_bufferID); }
    
    void Bind() const;
    void Delete();
    void BufferData(const void* vertices, const int size, const GLenum dataType) const;
    void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
};

}

#endif /* ElementBuffer_h */
