//
//  Logger.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/4/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "Logger.h"

//
//  WITH FILE LOCATION INFO
//
void GraviT::Logger::ConsoleLog(const char* file, int line, const std::string& msg) {
    if (m_currentLevel == ALL) std::cout << '[' << m_instanceName << ']' << ' ' << msg
        << "\n\tFILE:[" << file << "]\n\tLINE:[" << line << "]" << std::endl;
    
    m_errorLocs.push_back(file);
}

void GraviT::Logger::FatalLog(const char* file, int line, const std::string& fatal) {
    if (m_currentLevel <= FATAL) std::cout << '[' << m_instanceName << ']' << " FATAL: " << fatal
        << "\n\tFILE:[" << file << "]\n\tLINE:[" << line << "]" << std::endl;
    
    m_errorLocs.push_back(file);
}

void GraviT::Logger::ErrorLog(const char* file, int line, const std::string& error) {
    if (m_currentLevel <= ERROR) std::cout << '[' << m_instanceName << ']' << " ERROR: " << error
        << "\n\tFILE:[" << file << "]\n\tLINE:[" << line << "]" << std::endl;
    
    m_errorLocs.push_back(file);
}

void GraviT::Logger::WarningLog(const char* file, int line, const std::string& warn) {
    if (m_currentLevel <= WARNING) std::cout << '[' << m_instanceName << ']' << " WARNING: " << warn
        << "\n\tFILE:[" << file << "]\n\tLINE:[" << line << "]" << std::endl;
    
    m_errorLocs.push_back(file);
}


//
//  WITHOUT FILE LOCATION INFO
//
void GraviT::Logger::ConsoleLog(const std::string& msg) {
    if (m_currentLevel == ALL) std::cout << '[' << m_instanceName << ']' << ' ' << msg << std::endl;
}

void GraviT::Logger::FatalLog(const std::string& fatal) {
    if (m_currentLevel <= FATAL) std::cout << '[' << m_instanceName << ']' << " FATAL: " << fatal << std::endl;
}

void GraviT::Logger::ErrorLog(const std::string& error) {
    if (m_currentLevel <= ERROR) std::cout << '[' << m_instanceName << ']' << " ERROR: " << error << std::endl;
}

void GraviT::Logger::WarningLog(const std::string& warn) {
    if (m_currentLevel <= WARNING) std::cout << '[' << m_instanceName << ']' << " WARNING: " << warn << std::endl;
}

void GraviT::Logger::SetLevel(LogLevel newLevel) {
    m_currentLevel = newLevel;
}

void GraviT::Logger::PrintErrorLocs() const {
    std::vector<std::string>::const_iterator it = m_errorLocs.cbegin();
    std::cout << '[' << m_instanceName << "] ~ERROR LOCATIONS~" << std::endl;
    
    while (it != m_errorLocs.end()) {
        std::cout << "\t - " << *it << std::endl;
        it++;
    }
}
