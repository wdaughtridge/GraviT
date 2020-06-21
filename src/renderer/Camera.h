//
//  Camera.h
//  GraviT
//
//  Created by William Daughtridge on 6/17/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

namespace GraviT {

class Camera {
private:
    glm::vec3 m_cameraPosition;
    glm::vec3 m_cameraFront;
    glm::vec3 m_cameraUp;
    glm::mat4 m_view;
    
    bool m_movement_2d_active;
    double m_last_x_pos, m_last_y_pos;
    float m_yaw, m_pitch;
    
    std::shared_ptr<GraviT::Window> m_window;
    GraviT::ShaderProgram* m_program;
    
    const float m_cameraSpeed = 0.07f;
    const float m_mouse_sensitivity = 0.1f;
    bool m_sprinting = false;
public:
    Camera(std::shared_ptr<GraviT::Window> window, GraviT::ShaderProgram* program, bool movement_2d_active, glm::vec3 position = glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f)
    : m_cameraPosition(position), m_cameraFront(front), m_cameraUp(up), m_view(glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraFront, m_cameraUp)), m_movement_2d_active(movement_2d_active), m_window(window), m_program(program), m_yaw(yaw), m_pitch(pitch)
    {
        glfwGetCursorPos(m_window->m_window, &m_last_x_pos, &m_last_y_pos);
    }
    
    void MoveForward() {
        if (m_sprinting)
            m_cameraPosition += m_cameraSpeed * m_cameraFront * 2.0f;
        else
            m_cameraPosition += m_cameraSpeed * m_cameraFront;
    }
    void MoveBackward() {
        if (m_sprinting)
            m_cameraPosition -= m_cameraSpeed * m_cameraFront * 2.0f;
        else
            m_cameraPosition -= m_cameraSpeed * m_cameraFront;
    }
    void MoveLeft() {
        if (m_sprinting)
            m_cameraPosition -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraSpeed * 2.0f;
        else
            m_cameraPosition -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraSpeed;
    }
    void MoveRight() {
        if (m_sprinting)
            m_cameraPosition += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraSpeed * 2.0f;
        else
            m_cameraPosition += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraSpeed;
    }
    void MoveUp() {
        if (m_sprinting)
            m_cameraPosition += m_cameraUp * m_cameraSpeed * 2.0f;
        else
            m_cameraPosition += m_cameraUp * m_cameraSpeed;
    }
    void MoveDown() {
        if (m_sprinting)
            m_cameraPosition -= m_cameraUp * m_cameraSpeed * 2.0f;
        else
            m_cameraPosition -= m_cameraUp * m_cameraSpeed;
    }
    
    int HandleInput() {
        if (!m_movement_2d_active) {
            double current_x_pos, current_y_pos;
            double deltaX = 0, deltaY = 0;
            glfwGetCursorPos(m_window->m_window, &current_x_pos, &current_y_pos);
            
            if (current_x_pos!=m_last_x_pos || current_y_pos!=m_last_y_pos) {
                deltaX = current_x_pos-m_last_x_pos;
                deltaY = current_y_pos-m_last_y_pos;
                
                deltaX *= m_mouse_sensitivity;
                deltaY *= m_mouse_sensitivity;
                
                m_last_x_pos = current_x_pos;
                m_last_y_pos = current_y_pos;
                
                m_yaw += deltaX;
                m_pitch -= deltaY;
                
                if(m_pitch > 89.0f)
                    m_pitch = 89.0f;
                if(m_pitch < -89.0f)
                    m_pitch = -89.0f;
                
                glm::vec3 direction;
                direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
                direction.y = sin(glm::radians(m_pitch));
                direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
                m_cameraFront = glm::normalize(direction);
            }
        }
        
        if (glfwGetKey(m_window->m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            m_sprinting = true;
        }
        else {
            m_sprinting = false;
        }
        
        if (glfwGetKey(m_window->m_window, GLFW_KEY_W) == GLFW_PRESS) {
            if (!m_movement_2d_active) {
                MoveForward();
            }
            else {
                MoveUp();
            }
        }
        if (glfwGetKey(m_window->m_window, GLFW_KEY_S) == GLFW_PRESS) {
            if (!m_movement_2d_active) {
                MoveBackward();
            }
            else {
                MoveDown();
            }
        }
        
        
        if (glfwGetKey(m_window->m_window, GLFW_KEY_A) == GLFW_PRESS) {
            MoveLeft();
        }
        if (glfwGetKey(m_window->m_window, GLFW_KEY_D) == GLFW_PRESS) {
            MoveRight();
        }
        
        m_view = glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraFront, m_cameraUp);
        m_program->setUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(m_view));
        
        return 0;
    }
};

}

#endif /* Camera_h */
