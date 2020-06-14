//
//  Window.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/5/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "Window.h"

int GraviT::Window::Init() {
    if (!glfwInit()) {
        m_logger->ErrorLog(FILELOC, "GLFW not initialized.");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    m_window = glfwCreateWindow(windowDimensions.m_width, windowDimensions.m_height, "GraviT", NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        m_logger->ErrorLog(FILELOC, "GLFW window not created.");
        return 1;
    }

    glViewport(0, 0, windowDimensions.m_width, windowDimensions.m_height);
    glfwMakeContextCurrent(m_window);
    
    return 0;
}
