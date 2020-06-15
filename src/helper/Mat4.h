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
    std::array m_mat4<float, 16>;
    
    Mat4(const float initVal) {
        m_mat4<float, 16> {
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0
        };
    }
};

}

#endif /* Mat4_h */
