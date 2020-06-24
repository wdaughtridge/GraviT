//
//  ShaderProgram.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/8/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "ShaderProgram.h"
#include "Shader.h"

void GraviT::ShaderProgram::Link() const {
    glLinkProgram(m_programID);
}

void GraviT::ShaderProgram::Use() const {
    glUseProgram(m_programID);
}

void GraviT::ShaderProgram::Delete() {
    glDeleteProgram(m_programID);
}

void GraviT::ShaderProgram::HandleShaders() {
    m_vert.Attach();
    m_frag.Attach();
    Link();
    m_vert.Delete();
    m_frag.Delete();
}

void GraviT::ShaderProgram::setUniform1f(const char* uniName, float v0) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform1f(uniLocation, v0);
}
void GraviT::ShaderProgram::setUniform2f(const char* uniName, float v0, float v1) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform2f(uniLocation, v0, v1);
}
void GraviT::ShaderProgram::setUniform3f(const char* uniName, float v0, float v1, float v2) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform3f(uniLocation, v0, v1, v2);
}
void GraviT::ShaderProgram::setUniform4f(const char* uniName, float v0, float v1, float v2, float v3) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform4f(uniLocation, v0, v1, v2, v3);
}
void GraviT::ShaderProgram::setUniform1i(const char* uniName, int v0) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform1i(uniLocation, v0);
}
void GraviT::ShaderProgram::setUniform2i(const char* uniName, int v0, int v1) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform2i(uniLocation, v0, v1);
}
void GraviT::ShaderProgram::setUniform3i(const char* uniName, int v0, int v1, int v2) const {
        int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform3i(uniLocation, v0, v1, v2);
}
void GraviT::ShaderProgram::setUniform4i(const char* uniName, int v0, int v1, int v2, int v3) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform4i(uniLocation, v0, v1, v2, v3);
}
void GraviT::ShaderProgram::setUniform1ui(const char* uniName, unsigned int v0) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform1ui(uniLocation, v0);
}
void GraviT::ShaderProgram::setUniform2ui(const char* uniName, unsigned int v0, unsigned int v1) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform2ui(uniLocation, v0, v1);
}
void GraviT::ShaderProgram::setUniform3ui(const char* uniName, unsigned int v0, unsigned int v1, unsigned int v2) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform3ui(uniLocation, v0, v1, v2);
}
void GraviT::ShaderProgram::setUniform4ui(const char* uniName, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform4ui(uniLocation, v0, v1, v2, v3);
}
void GraviT::ShaderProgram::setUniform1fv(const char* uniName, GLsizei count, const float *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform1fv(uniLocation, count, value);
}
void GraviT::ShaderProgram::setUniform2fv(const char* uniName, GLsizei count, const float *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform2fv(uniLocation, count, value);
}
void GraviT::ShaderProgram::setUniform3fv(const char* uniName, GLsizei count, const float *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform3fv(uniLocation, count, value);
}
void GraviT::ShaderProgram::setUniform4fv(const char* uniName, GLsizei count, const float *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform4fv(uniLocation, count, value);
}
void GraviT::ShaderProgram::setUniform1iv(const char* uniName, GLsizei count, const int *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform1iv(uniLocation, count, value);
}
void GraviT::ShaderProgram::setUniform2iv(const char* uniName, GLsizei count, const int *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform2iv(uniLocation, count, value);
}
void GraviT::ShaderProgram::setUniform3iv(const char* uniName, GLsizei count, const int *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform3iv(uniLocation, count, value);
}
void GraviT::ShaderProgram::setUniform4iv(const char* uniName, GLsizei count, const int *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform4iv(uniLocation, count, value);
}
void GraviT::ShaderProgram::setUniform1uiv(const char* uniName, GLsizei count,  const unsigned int *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform1uiv(uniLocation, count, value);
}
void GraviT::ShaderProgram::setUniform2uiv(const char* uniName, GLsizei count, const unsigned int *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform2uiv(uniLocation, count, value);
}
void GraviT::ShaderProgram::setUniform3uiv(const char* uniName, GLsizei count, const unsigned int *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform3uiv(uniLocation, count, value);
}
void GraviT::ShaderProgram::setUniform4uiv(const char* uniName, GLsizei count, const unsigned int *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniform4uiv(uniLocation, count, value);
}
void GraviT::ShaderProgram::setUniformMatrix2fv(const char* uniName, GLsizei count, bool transpose, const float *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniformMatrix2fv(uniLocation, 1, GL_FALSE, value);
}
void GraviT::ShaderProgram::setUniformMatrix3fv(const char* uniName, GLsizei count, bool transpose, const float *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniformMatrix3fv(uniLocation, 1, GL_FALSE, value);
}
void GraviT::ShaderProgram::setUniformMatrix4fv(const char* uniName, GLsizei count, bool transpose, const float *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniformMatrix4fv(uniLocation, 1, GL_FALSE, value);
}
void GraviT::ShaderProgram::setUniformMatrix2x3fv(const char* uniName, GLsizei count, bool transpose, const float *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniformMatrix2x3fv(uniLocation, 1, GL_FALSE, value);
}
void GraviT::ShaderProgram::setUniformMatrix3x2fv(const char* uniName, GLsizei count, bool transpose, const float *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniformMatrix3x2fv(uniLocation, 1, GL_FALSE, value);
}
void GraviT::ShaderProgram::setUniformMatrix2x4fv(const char* uniName, GLsizei count, bool transpose, const float *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniformMatrix2x4fv(uniLocation, 1, GL_FALSE, value);
}
void GraviT::ShaderProgram::setUniformMatrix4x2fv(const char* uniName, GLsizei count, bool transpose, const float *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniformMatrix4x2fv(uniLocation, 1, GL_FALSE, value);
}
void GraviT::ShaderProgram::setUniformMatrix3x4fv(const char* uniName, GLsizei count, bool transpose, const float *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniformMatrix3x4fv(uniLocation, 1, GL_FALSE, value);
}
void GraviT::ShaderProgram::setUniformMatrix4x3fv(const char* uniName, GLsizei count, bool transpose, const float *value) const {
    int uniLocation = glGetUniformLocation(m_programID, uniName);
    
    if (uniLocation != -1)
        glUniformMatrix4x3fv(uniLocation, 1, GL_FALSE, value);
}
