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
int GraviT::Renderer::Init() const {
    glewExperimental = GL_TRUE;
    if(glewInit()) {
        m_logger->ErrorLog(FILELOC, "glew was not initialized.");
        return -1;
    }
    
    return 0;
}

float vertices[] = {
     0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
     1.0f,  1.0f, 0.0f,     0.0f, 0.0f, 1.0f,
     1.0f,  0.0f, 0.0f,     1.0f, 1.0f, 0.0f,
     0.0f,  0.0f, 0.0f,     0.0f, 1.0f, 1.0f,
     0.0f,  1.0f, 0.0f,     1.0f, 0.0f, 1.0f
};
unsigned int indices[] = {
    0, 1, 3,  // first square
    1, 2, 3
};
unsigned int indices2[] = {
    4, 5, 7,  // second square
    5, 6, 7
};

int GraviT::Renderer::Start() const {
    // create program with shaders from files
    GraviT::Shader frag(Shader::Fragment, "/Users/wdaughtridge/GraviT/GraviT/src/shaders/rainbow.frag.shader");
    GraviT::Shader vert(Shader::Vertex, "/Users/wdaughtridge/GraviT/GraviT/src/shaders/rainbow.vert.shader");
    GraviT::ShaderProgram program(vert, frag);
    
    // create program with shaders from files
    GraviT::Shader frag2(Shader::Fragment, "/Users/wdaughtridge/GraviT/GraviT/src/shaders/red.frag.shader");
    GraviT::Shader vert2(Shader::Vertex, "/Users/wdaughtridge/GraviT/GraviT/src/shaders/red.vert.shader");
    GraviT::ShaderProgram program2(vert, frag);
    
    // generate vao, vbo, and ebo's for a set of vertices
    GraviT::VertexArray vao;
    GraviT::VertexBuffer vbo;
    GraviT::ElementBuffer ebo;
    GraviT::ElementBuffer ebo2;
    
    vao.Bind();
    
    // give the buffer some vertex data
    vbo.Bind();
    vbo.BufferData(vertices, sizeof(vertices));

    // how the vertices should be drawn
    ebo.Bind();
    ebo.BufferData(indices, sizeof(indices));
    ebo2.Bind();
    ebo.BufferData(indices2, sizeof(indices2));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // unbind the current vao and vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    GraviT::Mat4 identity(1.0);
    
    while (!glfwWindowShouldClose(m_window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        Draw(vao, ebo, program2, "transformation", identity.m_mat4);
        
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    ebo2.Delete();
    program.Delete();
    
    return 0;
}

int GraviT::Renderer::AssignWindow(GLFWwindow *window) {
    if (window == nullptr) return -1;
    
    this->m_window = window;
    
    return 0;
}

int GraviT::Renderer::Draw(GraviT::VertexArray &vao, GraviT::ElementBuffer &ebo, GraviT::ShaderProgram &program, const char* name, const float *mat4) const {
    vao.Bind();
    ebo.Bind();
    program.Use();
    int transformLoc = glGetUniformLocation(program.GetID(), name);
    if (transformLoc != -1)
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, mat4);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    return 0;
}
