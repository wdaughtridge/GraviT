//
//  Object.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/16/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "Object.h"

int GraviT::Object_2D::Draw() {
    vao.Bind();
    glDrawElements(GL_TRIANGLES, (int)m_indexData.size(), GL_UNSIGNED_INT, 0);
    
    return 0;
}
