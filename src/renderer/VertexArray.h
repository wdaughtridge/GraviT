//
//  VertexArray.h
//  GraviT
//
//  Created by William Daughtridge on 6/7/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#ifndef VertexArray_h
#define VertexArray_h

#include <GL/glew.h>

namespace GraviT {

class VertexArray {
private:
    unsigned int m_arrayID;
public:
    VertexArray() { glGenVertexArrays(1, &m_arrayID); }
    int Bind() const;
    int Delete();
    //int GetID() const { return m_arrayID; }
};

}

#endif /* VertexArray_h */
