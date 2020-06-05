//
//  Application.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/4/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "Application.h"

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

int GraviT::Application::initWindow() {
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "GraviT", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    return 0;
}

int GraviT::Application::Run() {
    if (initWindow()) return -1;
    
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}
