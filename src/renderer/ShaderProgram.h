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

namespace GraviT {

class Shader;

class ShaderProgram {
private:
    int m_programID;
    
    int HandleShaders(GraviT::Shader& vertex, GraviT::Shader& fragment) const;
public:
    ShaderProgram(GraviT::Shader& vertex, GraviT::Shader& fragment) : m_programID(glCreateProgram()) {
        HandleShaders(vertex, fragment);
    }
    
    int Link() const;
    int Use() const;
    int Delete();
    int GetID() const { return m_programID; }
};

}

#endif /* ShaderProgram_h */
