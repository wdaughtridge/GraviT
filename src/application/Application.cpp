//
//  Application.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/4/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "Application.h"

int GraviT::Application::Run() const {
    if (m_window->Init()) m_logger->ErrorLog(FILELOC, "Application window not initialized.");
    
    m_renderer->Init();
    m_renderer->Start();

    glfwTerminate();
    
    return 0;
}
