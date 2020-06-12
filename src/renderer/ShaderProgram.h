//
//  ShaderProgram.h
//  GraviT
//
//  Created by William Daughtridge on 6/8/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#ifndef ShaderProgram_h
#define ShaderProgram_h

#include <GL/glew.h>
#include "renderer/Shader.h"

namespace GraviT {

class ShaderProgram {
private:
    int m_programID;
public:
    ShaderProgram() : m_programID(glCreateProgram()) {}
    
    int Link();
    int Get() const { return m_programID; }
};

}

#endif /* ShaderProgram_h */
