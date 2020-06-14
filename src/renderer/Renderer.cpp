//
//  Renderer.cpp
//  GraviT
//
//  Created by William Daughtridge on 6/4/20.
//  Copyright © 2020 William Daughtridge. All rights reserved.
//

#include "renderer/Renderer.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/ElementBuffer.h"

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
    const char *src1 = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "out vec3 outColor;\n"
        "uniform mat4 transformation;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = transformation * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "   outColor = aColor;\n"
        "}\0";
    const char *src2 = "#version 330 core\n"
        "in vec3 outColor;"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(outColor, 1.0);\n"
        "}\n\0";
    float vertices[] = {
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -1.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -1.0f, 1.0f, 0.0f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 3,  // first square
        1, 2, 3,
        4, 6, 7,  // first square
        5, 6, 7
    };
    float mat4[] = {
        1.19f, 0.49f, 0.0f, 0.0f,
        -0.21f, 0.49f, 0.0f, 0.0f,
        -0.7f, 0.7f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    GraviT::ShaderProgram program;
    GraviT::Shader frag(Fragment,src2);
    GraviT::Shader vert(Vertex,src1);
    
    frag.AttachTo(program);
    vert.AttachTo(program);
    
    program.Link();
    
    frag.Delete();
    vert.Delete();
    
    GraviT::VertexArray vao;
    GraviT::VertexBuffer vbo;
    GraviT::ElementBuffer ebo;
    
    vao.Bind();
    vbo.Bind();
    
    vbo.BufferData(vertices, sizeof(vertices));

    ebo.Bind();
    ebo.BufferData(indices, sizeof(indices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    while (!glfwWindowShouldClose(m_window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        int transformLoc = glGetUniformLocation(program.GetID(), "transformation");
        program.Use();
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, mat4);
        vao.Bind();
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
