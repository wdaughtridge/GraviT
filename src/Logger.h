//
//  Logger.h
//  GraviT
//
//  Created by William Daughtridge on 6/4/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#ifndef Logger_h
#define Logger_h

#include <iostream>
#include <memory>

namespace GraviT {
    class Logger {
    private:
        std::unique_ptr<unsigned int> m_numUsed;
    public:
        Logger() : m_numUsed(std::make_unique<unsigned int>(0)) {}
        
        virtual void ConsoleLog(const char* msg);
        virtual void FatalLog(const char* fatal);
        virtual void ErrorLog(const char* error);
        virtual void WarningLog(const char* warn);
        
        unsigned int GetNumUsed() const { return *m_numUsed; }
    };
}

#endif /* Logger_h */
