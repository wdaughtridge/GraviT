//
//  Shader.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/7/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "Shader.h"
#include "ShaderProgram.h"

int GraviT::Shader::GetSourceFromFile(const std::string& path) {
    std::string line;
    std::ifstream file(path, std::ifstream::in);
    
    if (!file.is_open())
        m_logger->ErrorLog(FILELOC, "Shader source file not open.");
    
    while (std::getline(file, line))
        m_source += line + '\n';
    
    file.close();
    
    return 0;
}

int GraviT::Shader::Create() {
    if (m_type == Vertex)
        m_shaderID = glCreateShader(GL_VERTEX_SHADER);
    else if (m_type == Fragment)
        m_shaderID = glCreateShader(GL_FRAGMENT_SHADER);
    
    const char* shadersrc = m_source.c_str();
    
    glShaderSource(m_shaderID, 1, &shadersrc, NULL);
    glCompileShader(m_shaderID);
    
    int res;
    char error[256];
    glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &res);
    if (!res) {
        glGetShaderInfoLog(m_shaderID, 256, NULL, error);
        m_logger->ErrorLog(FILELOC, "Shader compilation failed! \n" + std::string(error));
    }
    
    return 0;
}

int GraviT::Shader::Delete() {
    glDeleteShader(m_shaderID);
    
    return 0;
}

int GraviT::Shader::AttachTo(const int programID) const {
    glAttachShader(programID, m_shaderID);
    
    return 0;
}
