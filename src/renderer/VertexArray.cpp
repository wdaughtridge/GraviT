//
//  VertexArray.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/13/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "VertexArray.h"

void GraviT::VertexArray::Bind() const {
    glBindVertexArray(m_arrayID);
}

void GraviT::VertexArray::Delete() const {
    glDeleteVertexArrays(1, &m_arrayID);
}
