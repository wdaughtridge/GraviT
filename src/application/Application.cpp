//
//  Application.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/4/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "Application.h"

int GraviT::Application::Run() {
    if (m_window->Init()) m_logger->ErrorLog(FILELOC, "Application window not initialized.");
    
    m_renderer->AssignWindow(m_window->getWindowLoc());
    
    if (m_renderer->Init()) m_logger->ErrorLog(FILELOC, "Renderer not initialized.");
    
    if (m_renderer->Start()) m_logger->ErrorLog(FILELOC, "Renderer not started.");

    glfwTerminate();
    
    return 0;
}
