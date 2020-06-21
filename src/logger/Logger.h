//
//  Logger.h
//  GraviT
//
//  Created by William Daughtridge on 6/4/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#ifndef Logger_h
#define Logger_h

#ifndef FILELOC
#define FILELOC __FILE__, __LINE__
#endif

#include <iostream>
#include <string>
#include <vector>

namespace GraviT {

class Logger {
private:
    enum LogLevel {ALL, WARNING, ERROR, FATAL};
    std::string m_instanceName;
    LogLevel m_currentLevel;
    std::vector<std::string> m_errorLocs;
public:
    Logger(const std::string& name) : m_instanceName(name), m_currentLevel(ALL) {}
    
    //  use FILELOC macro to fill in file location info
    void ConsoleLog(const char* file, int line, const std::string& msg);
    void WarningLog(const char* file, int line, const std::string& warn);
    void ErrorLog(const char* file, int line, const std::string& error);
    void FatalLog(const char* file, int line, const std::string& fatal);
    
    void ConsoleLog(const std::string& msg);
    void WarningLog(const std::string& warn);
    void ErrorLog(const std::string& error);
    void FatalLog(const std::string& fatal);
    
    void SetLevel(LogLevel newLevel);
    void PrintErrorLocs() const;
};

}

#endif /* Logger_h */
