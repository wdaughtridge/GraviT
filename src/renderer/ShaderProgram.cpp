//
//  ShaderProgram.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/8/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "ShaderProgram.h"

int GraviT::ShaderProgram::Link() const {
    glLinkProgram(m_programID);
    
    return 0;
}

int GraviT::ShaderProgram::Use() const {
    glUseProgram(m_programID);
    
    return 0;
}

int GraviT::ShaderProgram::Delete() {
    glDeleteProgram(m_programID);
    
    return 0;
}
