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

namespace GraviT {

class Texture {
private:
    unsigned int m_textureID;
public:
    Texture(const char* source) {
        if (source) return;
        
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        LoadTextureFromFile(source);
    }
    
    int LoadTextureFromFile(const char* source) const;
    int Bind() const;
};

}


#endif /* Texture_h */
