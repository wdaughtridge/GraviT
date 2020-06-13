//
//  ShaderProgram.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/8/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "renderer/ShaderProgram.h"

int GraviT::ShaderProgram::Link() {
    glLinkProgram(m_programID);
    
    return 0;
}
