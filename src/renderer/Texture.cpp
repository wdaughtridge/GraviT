//
//  Texture.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/16/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int GraviT::Texture::LoadTextureFromFile(const char *source) {
    stbi_set_flip_vertically_on_load(true);
    unsigned char* textureData = stbi_load(source, &m_textureWidth, &m_textureHeight, &m_nrChannels, 0);
    
    if(textureData != nullptr) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textureWidth, m_textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        stbi_image_free(textureData);
        return -1;
    }
    
    stbi_image_free(textureData);
    
    return 0;
}

int GraviT::Texture::Bind() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    
    return 0;
};
