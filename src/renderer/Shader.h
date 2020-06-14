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
#include <memory>

#include "Logger.h"
#include "ShaderProgram.h"

namespace GraviT {

enum ShaderType { Vertex, Fragment };

class Shader {
private:
    const ShaderType m_type;
    int m_count;
    std::unique_ptr<GraviT::Logger> m_logger;
    std::string m_source;
    int m_shaderID;
    int m_programID;
    
    int GetSourceFromFile(const std::string& path);
    int Create();
public:
    Shader(const ShaderType& type, const std::string& src)
        : m_type(type), m_count(1), m_logger(std::make_unique<GraviT::Logger>("Shader"))
    {
        GetSourceFromFile(src);
        Create();
    }
    
    Shader(const ShaderType& type, const std::string& src, const GraviT::ShaderProgram& program)
        : m_type(type), m_count(1), m_logger(std::make_unique<GraviT::Logger>("Shader"))
    {
        GetSourceFromFile(src);
        Create();
        AttachTo(program);
    }
    
    int Delete();
    int AttachTo(const GraviT::ShaderProgram& program) const;
};

}

#endif /* Shader_h */
