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
#include "Logger.h"
#include "Shader.h"

namespace GraviT {

class ShaderProgram {
private:
    int m_programID;
    std::unique_ptr<GraviT::Logger> m_logger;
    
    void HandleShaders();
    
    GraviT::Shader m_vert;
    GraviT::Shader m_frag;
public:
    ShaderProgram(const char* vertsrc, const char* fragsrc)
    : m_programID(glCreateProgram()), m_logger(std::make_unique<GraviT::Logger>("ShaderProgram")), m_vert(Shader::Vertex, vertsrc, m_programID), m_frag(Shader::Fragment, fragsrc, m_programID)
    {
        HandleShaders();
    }
    
    void Link() const;
    void Use() const;
    void Delete();
    int GetID() const { return m_programID; }
    
    void setUniform1f(const char* uniName, float v0) const;
    void setUniform2f(const char* uniName, float v0, float v1) const;
    void setUniform3f(const char* uniName, float v0, float v1, float v2) const;
    void setUniform4f(const char* uniName, float v0, float v1, float v2, float v3) const;
    void setUniform1i(const char* uniName, int v0) const;
    void setUniform2i(const char* uniName, int v0, int v1) const;
    void setUniform3i(const char* uniName, int v0, int v1, int v2) const;
    void setUniform4i(const char* uniName, int v0, int v1, int v2, int v3) const;
    void setUniform1ui(const char* uniName, unsigned int v0) const;
    void setUniform2ui(const char* uniName, unsigned int v0, unsigned int v1) const;
    void setUniform3ui(const char* uniName, unsigned int v0, unsigned int v1, unsigned int v2) const;
    void setUniform4ui(const char* uniName, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3) const;
    void setUniform1fv(const char* uniName, GLsizei count, const float *value) const;
    void setUniform2fv(const char* uniName, GLsizei count, const float *value) const;
    void setUniform3fv(const char* uniName, GLsizei count, const float *value) const;
    void setUniform4fv(const char* uniName, GLsizei count, const float *value) const;
    void setUniform1iv(const char* uniName, GLsizei count, const int *value) const;
    void setUniform2iv(const char* uniName, GLsizei count, const int *value) const;
    void setUniform3iv(const char* uniName, GLsizei count, const int *value) const;
    void setUniform4iv(const char* uniName, GLsizei count, const int *value) const;
    void setUniform1uiv(const char* uniName, GLsizei count,  const unsigned int *value) const;
    void setUniform2uiv(const char* uniName, GLsizei count, const unsigned int *value) const;
    void setUniform3uiv(const char* uniName, GLsizei count, const unsigned int *value) const;
    void setUniform4uiv(const char* uniName, GLsizei count, const unsigned int *value) const;
    void setUniformMatrix2fv(const char* uniName, GLsizei count, bool transpose, const float *value) const;
    void setUniformMatrix3fv(const char* uniName, GLsizei count, bool transpose, const float *value) const;
    void setUniformMatrix4fv(const char* uniName, GLsizei count, bool transpose, const float *value) const;
    void setUniformMatrix2x3fv(const char* uniName, GLsizei count, bool transpose, const float *value) const;
    void setUniformMatrix3x2fv(const char* uniName, GLsizei count, bool transpose, const float *value) const;
    void setUniformMatrix2x4fv(const char* uniName, GLsizei count, bool transpose, const float *value) const;
    void setUniformMatrix4x2fv(const char* uniName, GLsizei count, bool transpose, const float *value) const;
    void setUniformMatrix3x4fv(const char* uniName, GLsizei count, bool transpose, const float *value) const;
    void setUniformMatrix4x3fv(const char* uniName, GLsizei count, bool transpose, const float *value) const;
};

}

#endif /* ShaderProgram_h */
