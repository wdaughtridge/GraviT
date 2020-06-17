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

namespace GraviT {

class Shader;

class ShaderProgram {
private:
    int m_programID;
    std::unique_ptr<GraviT::Logger> m_logger;
    
    int HandleShaders(GraviT::Shader& vertex, GraviT::Shader& fragment) const;
public:
    ShaderProgram(GraviT::Shader& vertex, GraviT::Shader& fragment) : m_programID(glCreateProgram()), m_logger(std::make_unique<GraviT::Logger>("ShaderProgram")) {
        HandleShaders(vertex, fragment);
    }
    
    int Link() const;
    int Use() const;
    int Delete();
    int GetID() const { return m_programID; }
    
    void setUniform1f(const char* uniName, float v0);
    void setUniform2f(const char* uniName, float v0, float v1);
    void setUniform3f(const char* uniName, float v0, float v1, float v2);
    void setUniform4f(const char* uniName, float v0, float v1, float v2, float v3);
    void setUniform1i(const char* uniName, int v0);
    void setUniform2i(const char* uniName, int v0, int v1);
    void setUniform3i(const char* uniName, int v0, int v1, int v2);
    void setUniform4i(const char* uniName, int v0, int v1, int v2, int v3);
    void setUniform1ui(const char* uniName, unsigned int v0);
    void setUniform2ui(const char* uniName, unsigned int v0, unsigned int v1);
    void setUniform3ui(const char* uniName, unsigned int v0, unsigned int v1, unsigned int v2);
    void setUniform4ui(const char* uniName, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3);
    void setUniform1fv(const char* uniName, GLsizei count, const float *value);
    void setUniform2fv(const char* uniName, GLsizei count, const float *value);
    void setUniform3fv(const char* uniName, GLsizei count, const float *value);
    void setUniform4fv(const char* uniName, GLsizei count, const float *value);
    void setUniform1iv(const char* uniName, GLsizei count, const int *value);
    void setUniform2iv(const char* uniName, GLsizei count, const int *value);
    void setUniform3iv(const char* uniName, GLsizei count, const int *value);
    void setUniform4iv(const char* uniName, GLsizei count, const int *value);
    void setUniform1uiv(const char* uniName, GLsizei count,  const unsigned int *value);
    void setUniform2uiv(const char* uniName, GLsizei count, const unsigned int *value);
    void setUniform3uiv(const char* uniName, GLsizei count, const unsigned int *value);
    void setUniform4uiv(const char* uniName, GLsizei count, const unsigned int *value);
    void setUniformMatrix2fv(const char* uniName, GLsizei count, bool transpose, const float *value);
    void setUniformMatrix3fv(const char* uniName, GLsizei count, bool transpose, const float *value);
    void setUniformMatrix4fv(const char* uniName, GLsizei count, bool transpose, const float *value);
    void setUniformMatrix2x3fv(const char* uniName, GLsizei count, bool transpose, const float *value);
    void setUniformMatrix3x2fv(const char* uniName, GLsizei count, bool transpose, const float *value);
    void setUniformMatrix2x4fv(const char* uniName, GLsizei count, bool transpose, const float *value);
    void setUniformMatrix4x2fv(const char* uniName, GLsizei count, bool transpose, const float *value);
    void setUniformMatrix3x4fv(const char* uniName, GLsizei count, bool transpose, const float *value);
    void setUniformMatrix4x3fv(const char* uniName, GLsizei count, bool transpose, const float *value);
};

}

#endif /* ShaderProgram_h */
