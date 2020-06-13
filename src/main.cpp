//
//  main.cpp
//  cpp
//
//      Created by William Daughtridge on 5/30/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "Application.h"
        
int main(int argc, const char * argv[]) {
    GraviT::Application* app = new GraviT::Application;
    app->Run();
    delete app;
}
