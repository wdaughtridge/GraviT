//
//  Logger.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/4/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "Logger.h"

void GraviT::Logger::ConsoleLog(const char* msg) {
    std::cout << msg << std::endl;
    (*m_numUsed)++;
}

void GraviT::Logger::FatalLog(const char* fatal) {
    std::cout << "FATAL: " << fatal << std::endl;
    (*m_numUsed)++;
    exit(EXIT_FAILURE);
}

void GraviT::Logger::ErrorLog(const char* error) {
    std::cout << "ERROR: " << error << std::endl;
    (*m_numUsed)++;
}

void GraviT::Logger::WarningLog(const char* warn) {
    std::cout << "WARNING: " << warn << std::endl;
    (*m_numUsed)++;
}
