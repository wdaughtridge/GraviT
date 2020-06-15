//
//  Shader.h
//  GraviT
//
//  Created by William Daughtridge on 6/7/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//
#ifndef Shader_h
#define Shader_h

#include <GL/glew.h>
#include <string>
#include <fstream>

#include "Logger.h"

namespace GraviT {

class ShaderProgram;

class Shader {
public:
    enum ShaderType { Vertex, Fragment };
private:
    const Shader::ShaderType m_type;
    int m_count;
    std::unique_ptr<GraviT::Logger> m_logger;
    std::string m_source;
    int m_shaderID;
    int m_programID;
    
    int GetSourceFromFile(const std::string& path);
    int Create();
public:
    Shader(const Shader::ShaderType& type, const std::string& src)
        : m_type(type), m_count(1), m_logger(std::make_unique<GraviT::Logger>("Shader"))
    {
        GetSourceFromFile(src);
        Create();
    }
    
    Shader(const Shader::ShaderType& type, const std::string& src, const GraviT::ShaderProgram& program)
        : m_type(type), m_count(1), m_logger(std::make_unique<GraviT::Logger>("Shader"))
    {
        GetSourceFromFile(src);
        Create();
    }
    
    int Delete();
    int AttachTo(const int programID) const;
};

}

#endif /* Shader_h */
