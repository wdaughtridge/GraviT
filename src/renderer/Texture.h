//
//  Texture.h
//  GraviT
//
//  Created by William Daughtridge on 6/16/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#ifndef Texture_h
#define Texture_h

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace GraviT {

class Texture {
private:
    unsigned int m_textureID;
    int m_textureHeight;
    int m_textureWidth;
    int m_nrChannels;
    int m_subTextureSizePx;
    
public:
    Texture(const char* source) : m_subTextureSizePx(0) {
        if (!source) return;
        glBindVertexArray(1);
        
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        LoadTextureFromFile(source);
    }
    
    Texture(const char* source, int subTextureSizePx) : m_subTextureSizePx(subTextureSizePx) {
        if (!source) return;
        glBindVertexArray(1);
        
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        LoadTextureFromFile(source);
    }
    
    glm::vec2 GetDimensions() const { return glm::vec2(m_textureWidth, m_textureHeight); }
    int GetSubTexSize() const { return m_subTextureSizePx; }
    int LoadTextureFromFile(const char* source);
    int Bind() const;
};

}


#endif /* Texture_h */
