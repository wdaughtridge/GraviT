//
//  main.cpp
//  cpp
//
//      Created by William Daughtridge on 5/30/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "Logger.h"
#include "Application.h"
        
int main(int argc, const char * argv[]) {
    std::unique_ptr<GraviT::Application> app = std::make_unique<GraviT::Application>();
    
    app->logger->WarningLog("Testing logging on application layer..");
    
    app->Run();
}
