//
//  Window.h
//  GraviT
//
//  Created by William Daughtridge on 6/5/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#ifndef Window_h
#define Window_h

#include <string>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include "Logger.h"

namespace GraviT {

struct dimensions {
    dimensions(unsigned int x, unsigned int y) { m_width = x; m_height = y; }
    unsigned int m_width;
    unsigned int m_height;
};

class Window {
private:
    std::string m_title;
    bool m_isFullScreen;
    GLFWwindow* m_window;
    std::unique_ptr<GraviT::Logger> m_logger;
public:
    dimensions windowDimensions;
    
    Window(std::string winTitle, unsigned int winWidth, unsigned int winHeight, bool fullScreen)
         : m_title(winTitle), windowDimensions(winWidth, winHeight), m_isFullScreen(fullScreen), m_window(nullptr), m_logger(std::make_unique<GraviT::Logger>(m_title + " window")) {}
    
    // creates window on screen and context for rendering
    virtual int Init();
    GLFWwindow* getWindowLoc() const { return m_window; }
};

}

#endif /* Window_h */
