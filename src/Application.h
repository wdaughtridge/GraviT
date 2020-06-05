//
//  Application.h
//  GraviT
//
//  Created by William Daughtridge on 6/4/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#ifndef Application_h
#define Application_h

#include "Logger.h"
#include "Renderer.h"
#include <memory>
#include <GLFW/glfw3.h>

namespace GraviT {
    class Application {
    private:
        GLFWwindow* window;
        std::unique_ptr<GraviT::Renderer> renderer;
    public:
        std::unique_ptr<GraviT::Logger> logger;
        
        Application() : window(nullptr), renderer(std::make_unique<GraviT::Renderer>()), logger(std::make_unique<GraviT::Logger>()) {}
        int initWindow();
        int Run();
        GLFWwindow* getWindowId() const { return window; }
    };
}

#endif /* Application_h */
