//
//  VertexArray.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/13/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "VertexArray.h"

int GraviT::VertexArray::Bind() const {
    glBindVertexArray(m_arrayID);
    
    return 0;
}

int GraviT::VertexArray::Delete() {
    glDeleteVertexArrays(1, &m_arrayID);
    
    return 0;
}
