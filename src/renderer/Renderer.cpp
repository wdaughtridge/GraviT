//
//  Renderer.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/4/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "Renderer.h"

/*
 Initialize GLEW
 */
int GraviT::Renderer::Init() {
    glewExperimental = GL_TRUE;
    if(glewInit()) {
        m_logger->ErrorLog(FILELOC, "glew was not initialized.");
        return -1;
    }
    
    return 0;
}

int GraviT::Renderer::Start() {
    float vertices[] = {
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         1.0f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
         0.0f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
         0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f
    };
    unsigned int indices[] = {
        0, 1, 3,  // first square
        1, 2, 3
    };
    unsigned int indices2[] = {
        4, 5, 7,  // second square
        5, 6, 7
    };
    float rotate[] = {
        1.19f, 0.49f, 0.0f, 0.0f,
        -0.21f, 0.49f, 0.0f, 0.0f,
        -0.7f, 0.7f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    float transpose[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f,
    };
    float identity[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };
    float rot45[] = {
        0.7f, 0.7f, 0.0f, 0.0f,
       -0.7f, 0.7f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f,
    };
    
    GraviT::ShaderProgram program;
    
    //TODO:: FIX TO RELATIVE PATH
    GraviT::Shader frag(Fragment, "/Users/wdaughtridge/GraviT/GraviT/src/shaders/Fragment.shader", program);
    GraviT::Shader vert(Vertex, "/Users/wdaughtridge/GraviT/GraviT/src/shaders/Vertex.shader", program);
    
    program.Link();
    
    frag.Delete();
    vert.Delete();
    
    GraviT::VertexArray vao;
    GraviT::VertexBuffer vbo;
    GraviT::ElementBuffer ebo;
    GraviT::ElementBuffer ebo2;
    
    vao.Bind();
    vbo.Bind();
    
    vbo.BufferData(vertices, sizeof(vertices));

    ebo.Bind();
    ebo.BufferData(indices, sizeof(indices));
    
    ebo2.Bind();
    ebo.BufferData(indices2, sizeof(indices2));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    while (!glfwWindowShouldClose(m_window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        int transformLoc = glGetUniformLocation(program.GetID(), "transformation");
        program.Use();
        vao.Bind();
        ebo.Bind();
        
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, identity);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        ebo2.Bind();
        
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, identity);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    vao.Delete();
    vbo.Delete();
    glDeleteBuffers(1, &EBO);
    program.Delete();
    
    return 0;
}

int GraviT::Renderer::AssignWindow(GLFWwindow *window) {
    if (window == nullptr) return -1;
    
    this->m_window = window;
    
    return 0;
}
