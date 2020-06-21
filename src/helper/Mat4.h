//
//  Mat4.h
//  GraviT
//
//  Created by William Daughtridge on 6/15/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#ifndef Mat4_h
#define Mat4_h

#include <array>

namespace GraviT {

class Mat4 {
private:
    
public:
    std::array<float, 16> m_mat4;
    
    Mat4(const float initVal) {
        m_mat4 = {
            initVal, 0.0, 0.0, 0.0,
            0.0, initVal, 0.0, 0.0,
            0.0, 0.0, initVal, 0.0,
            0.0, 0.0, 0.0, initVal
        };
    }
    
    Mat4(std::initializer_list<float> position) {
        m_mat4 = {
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        };
        int i(0);
        for (auto p : position) {
            if (i < 3)
                m_mat4[12+i] = p;
            i++;
        }
    }
};

}

#endif /* Mat4_h */
