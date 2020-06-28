//
//  Window.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/5/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//
#define GL_SILENCE_DEPRECATION

#include "Window.h"

void GraviT::Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void GraviT::Window::HandleInput() {
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) && !m_isPaused) {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        m_isPaused = true;
    }
    
    else if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) && m_isPaused) {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        m_isPaused = false;
    }
}

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
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    m_window = glfwCreateWindow(windowDimensions.m_width, windowDimensions.m_height, "GraviT", NULL, NULL);
    if (!m_window) {
        glfwTerminate();
        m_logger->ErrorLog(FILELOC, "GLFW window not created.");
        return 1;
    }
    
    glEnable(GL_MULTISAMPLE);

    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
    
    return 0;
}

int GraviT::Window::ShouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void GraviT::Window::SwapBuffers() const {
    glfwSwapBuffers(m_window);
}
