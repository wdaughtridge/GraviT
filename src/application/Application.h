//
//  Application.h
//  GraviT
//
//  Created by William Daughtridge on 6/4/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#ifndef Application_h
#define Application_h

#include <memory>
#include <GL/glew.h>

// disable documentation warnings
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include "Logger.h"
#include "Renderer.h"
#include "Window.h"

namespace GraviT {

class Application {
private:
    std::unique_ptr<GraviT::Window> m_window;
    std::unique_ptr<GraviT::Renderer> m_renderer;
    
public:
    std::unique_ptr<GraviT::Logger> m_logger;
    
    Application() : m_window(std::make_unique<GraviT::Window>("GraviT", 960, 720, false)), m_renderer(std::make_unique<GraviT::Renderer>()), m_logger(std::make_unique<GraviT::Logger>("Application")) {}
    
    virtual int Run();
};

}

#endif /* Application_h */
