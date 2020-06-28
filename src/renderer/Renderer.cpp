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
void GraviT::Renderer::Init() const {
    glewExperimental = GL_TRUE;
    if(glewInit()) {
        m_logger->ErrorLog(FILELOC, "glew was not initialized.");
    }
    
    std::cout << "Current OpenGL version: " << glGetString(GL_VERSION) << std::endl;
}

void GraviT::Renderer::Start() const {
    glEnable(GL_DEPTH_TEST);
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    const char* glsl_version = "#version 330 core";
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(m_window->m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    
    if (m_enableCulling)
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
    
    GraviT::ShaderProgram program("shaders/texture.vert", "shaders/texture.frag");
    
    GraviT::Texture minecraft("asset/minecraftTex.jpg", 64);
    GraviT::Texture diamond("asset/texture.jpg");
    GraviT::Texture sprsht("asset/spritesheet.jpg", 16);
    
    program.Use();
    
    glActiveTexture(GL_TEXTURE0);
    minecraft.Bind();
    glActiveTexture(GL_TEXTURE1);
    sprsht.Bind();
    glActiveTexture(GL_TEXTURE1);
    diamond.Bind();
    
    GraviT::Object::Batch batch = GraviT::Renderer::ParseLevelFile3D("asset/levelTest.txt", minecraft);
    GraviT::Object scene(batch.vertices, batch.indices, GL_STATIC_DRAW);
    
    std::vector<std::vector<Object::VertexData>> floor;
    std::vector<std::vector<Object::VertexData>> ceil;
    std::vector<std::vector<Object::VertexData>> wall;
    
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            floor.push_back(GraviT::Object::GenerateQuadVertices(4, glm::vec3(i * 4, j * 4, 0.0f), minecraft, true, 0.0f, glm::vec2(2.0f, 15.0f), 0));
            ceil.push_back(GraviT::Object::GenerateQuadVertices(4, glm::vec3(i * 4, j * 4, 0.0f), minecraft, true, 0.0f, glm::vec2(4.0f, 15.0f), 0));
            if (j < 25)
                wall.push_back(GraviT::Object::GenerateQuadVertices(4, glm::vec3(i * 4, j * 4, 0.0f), minecraft, true, 0.0f, glm::vec2(0.0f, 14.0f), 0));
        }
    }
    
    Object::Batch floorBatch = Object::GetQuadBatch(floor, false);
    Object::Batch ceilBatch = Object::GetQuadBatch(ceil, true);
    
    GraviT::Object texFloor(floorBatch.vertices, floorBatch.indices, GL_STATIC_DRAW);
    GraviT::Object texCeil(ceilBatch.vertices, ceilBatch.indices, GL_STATIC_DRAW);
    
    Object::Batch wallBatch0 = Object::GetQuadBatch(wall, true);
    Object::Batch wallBatch1 = Object::GetQuadBatch(wall, true);
    Object::Batch wallBatch2 = Object::GetQuadBatch(wall, true);
    Object::Batch wallBatch3 = Object::GetQuadBatch(wall, true);
    
    GraviT::Object texWall0(wallBatch0.vertices, wallBatch0.indices, GL_STATIC_DRAW);
    GraviT::Object texWall1(wallBatch1.vertices, wallBatch1.indices, GL_STATIC_DRAW);
    GraviT::Object texWall2(wallBatch2.vertices, wallBatch2.indices, GL_STATIC_DRAW);
    GraviT::Object texWall3(wallBatch3.vertices, wallBatch3.indices, GL_STATIC_DRAW);
    
    texFloor.SetPos(glm::vec3(0.0f, 0.0f, 200.0f));
    texFloor.SetRotation(-90, glm::vec3(1.0f, 0.0f, 0.0f));
    texCeil.SetPos(glm::vec3(0.0f, 100.0f, 0.0f));
    texCeil.SetRotation(90, glm::vec3(1.0f, 0.0f, 0.0f));
    
    texWall0.SetPos(glm::vec3(200.0f, 0.0f, 200.0f));
    texWall0.SetRotation(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    
    texWall1.SetPos(glm::vec3(200.0f, 0.0f, 0.0f));
    texWall1.SetRotation(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    
    texWall3.SetPos(glm::vec3(0.0f, 0.0f, 200.0f));
    texWall3.SetRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    
    std::vector<Object::VertexData> blockVertices = GraviT::Object::GenerateCubeVertices(4, glm::vec3(10.0f, 10.0f, 10.0f), minecraft, true, 0.0f, glm::vec2(8.0f, 15.0f), 0.0f);
    std::vector<unsigned int> blockIndices = GraviT::Object::GenerateCubeIndices(1, true);
    GraviT::Object block(blockVertices, blockIndices, GL_DYNAMIC_DRAW);
 
    // unbind the current vao and vbo
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    int samplers[3] = {0, 1, 2};
    program.setUniform1iv("uTexture", 3, samplers);
    
    GraviT::Camera cam(m_window, &program, false, glm::vec3(0.0f, 2.0f, 6.0f));
    
    program.setUniform3f("lightPos", 100.0f, 50.0F, 100.0f);
    program.setUniform3f("lightColor", 0.8f, 0.8f, 0.8f);
    
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    
    while (!m_window->ShouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_window->HandleInput();
        
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        if (!m_window->m_isPaused) {
            cam.HandleInput();
        
            program.setUniform3f("viewPos", cam.m_cameraPosition.x, cam.m_cameraPosition.y, cam.m_cameraPosition.z);
            
            texWall0.Draw(program);
            texWall1.Draw(program);
            texWall2.Draw(program);
            texWall3.Draw(program);
            texFloor.Draw(program);
            texCeil.Draw(program);

            block.Draw(program);
            scene.Draw(program);
        }
        
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        m_window->SwapBuffers();
        glfwPollEvents();
    }
    
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    program.Delete();
}

GraviT::Object::Batch GraviT::Renderer::ParseLevelFile3D(const std::string& path, const GraviT::Texture& tex) {
    std::string line;
    std::ifstream file(path, std::ifstream::in);
    std::string level;
    
    while (std::getline(file, line))
        level += line + '\n';
    
    file.close();
    
    float x = 0.0f;
    float y = 0.0f;
    std::vector<std::vector<GraviT::Object::VertexData>> vertices;
    
    for (auto c : level) {
        vertices.push_back(GraviT::Object::GenerateCubeVertices(4, glm::vec3(x * 4.0f, y * 4.0f, -20.0f), tex, true, 0.0f, glm::vec2(8.0f, 15.0f)));
        
        if (c == '\n') {
            x = 0.0f;
            y += 1.0f;;
        }
        else
            x += 1.0f;
    }
    
    return GraviT::Object::GetCubeBatch(vertices, true);
}

GraviT::Object::Batch GraviT::Renderer::ParseLevelFile2D(const std::string& path, const GraviT::Texture& tex) {
    std::string line;
    std::ifstream file(path, std::ifstream::in);
    std::string level;
    
    while (std::getline(file, line))
        level += line + '\n';
    
    file.close();
    
    float x = 0.0f;
    float y = 0.0f;
    std::vector<std::vector<GraviT::Object::VertexData>> vertices;
    
    for (auto c : level) {
        vertices.push_back(GraviT::Object::GenerateQuadVertices(4, glm::vec3(x * 4.0f, y * 4.0f, -20.0f), tex, true, 0.0f, glm::vec2(8.0f, 15.0f)));
        
        if (c == '\n') {
            x = 0.0f;
            y += 1.0f;;
        }
        else
            x += 1.0f;
    }
    
    return GraviT::Object::GetQuadBatch(vertices, true);
}
