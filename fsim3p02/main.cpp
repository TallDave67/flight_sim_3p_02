#include <stdio.h>
#include <string.h>
#include <memory>
#include <vector>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Constants.h"
#include "DrawingWindow.h"
#include "EntityManager.h"
#include "LightManager.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Shader.h"
#include "Motion.h"
#include "Camera.h"
#include "FrameRate.h"
#include "VideoStreamer.h"
#include "Utility.h"

// Entity Manager
EntityManager entityManager;

// Meshes
std::vector<std::unique_ptr<Mesh>> meshList;

// Ground Mesh
GLfloat ground_vertices[] = {
    //   x       y      z        u       v    nx    ny    nz
    -12.0f,  -6.0f,  12.0f,  0.00f,  0.00f, 0.0f, 1.0f, 0.0f, //corner bottom left
     12.0f,  -6.0f,  12.0f,  0.00f,  1.00f, 0.0f, 1.0f, 0.0f, //corner bottom right
     12.0f,  -6.0f, -12.0f,  1.00f,  1.00f, 0.0f, 1.0f, 0.0f, //corner top right
    -12.0f,  -6.0f, -12.0f,  1.00f,  0.00f, 0.0f, 1.0f, 0.0f, //corner top left
};
unsigned int num_ground_vertices = 32;
unsigned int ground_indices[] = {
    0, 2, 3,
    0, 1, 2
};
unsigned int num_ground_indices = 6;

// Textures
Texture groundTexture;
std::string texture_ground_path = std::string(PATH_INPUT) + std::string(PATH_TEXTURES) + std::string("ground.png");

void CreateObjects()
{
    // Create Objects without Models
    meshList.push_back(std::make_unique<Mesh>());
    meshList[0]->CreateMesh(ground_vertices, ground_indices, num_ground_vertices, num_ground_indices);
    groundTexture.initialize(texture_ground_path.c_str());
    groundTexture.LoadTexture(GL_RGBA);
}

// Lights
LightManager lightManager;

// Shaders
std::string vertex_code_path =  std::string(PATH_INPUT) + std::string(PATH_SHADERS) + std::string("shader.vert");
std::string fragment_code_path =  std::string(PATH_INPUT) + std::string(PATH_SHADERS) + std::string("shader.frag");
std::vector<std::unique_ptr<Shader>> shaderList;

void CreateShaders()
{
    shaderList.push_back(std::make_unique<Shader>());
    shaderList[0]->CreateFromFile(vertex_code_path.c_str() , fragment_code_path.c_str());
}

// Camera
Camera camera;

int main()
{
    // Our main drawing window
    DrawingWindow mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    int ret = mainWindow.initialize();
    if (ret != 0)
    {
        return ret;
    }

    // Create Entities
    entityManager.initialize();

    // Objects to draw and how to draw them
    CreateObjects();
    CreateShaders();

    // Initiliaze our camera
    camera.initialize(&mainWindow, glm::vec3(0.0f, 0.0f, TRANSLATION_MAX_OFFSET), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 
        static_cast<GLfloat>(CAMERA_TRANSLATION_INCREMENT), static_cast<GLfloat>(CAMERA_ROTATION_INCREMENT));

    // Create Lights
    lightManager.initialize();

    // Create a perspective projection so we can live in a 3d world
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), static_cast<GLfloat>(mainWindow.getBufferWidth())/static_cast<GLfloat>(mainWindow.getBufferHeight()), 0.1f, 150.0f);

    // Set a reasonable frame rate
    FrameRate fr(FPS_WINDOW);

    // Video Streaming
    VideoStreamer video_streamer(FPS_MP4);
    video_streamer.prepare(mainWindow.getWidth(), mainWindow.getHeight());

    // Loop until window closed
    while (!mainWindow.shouldClose())
    {
        // Do we render to the screen?
        if (!fr.is_frame_due())
        {
            continue;
        }

        // Get + Handle user input events
        glfwPollEvents();
        camera.handleKeyEvent();

        // Motion
        entityManager.moveEntities();
        lightManager.moveLights();

        // Clear window
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0]->UseShader();
    
        // Lights
        lightManager.setLights(shaderList[0]);

        // Projection
        glUniformMatrix4fv(shaderList[0]->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projection));

        // Camera (View)
        glUniformMatrix4fv(shaderList[0]->GetViewLocation(), 1, GL_FALSE, glm::value_ptr(camera.getView()));

        // Eye
        glUniform3f(shaderList[0]->GetEyeLocation(), camera.getCameraEye().x, camera.getCameraEye().y, camera.getCameraEye().z);
        
        // Render
        entityManager.renderEntities(shaderList[0]);
        //
        glm::mat4 model(1.0f);
        glUniformMatrix4fv(shaderList[0]->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));;
        groundTexture.UseTexture();
        Material* dullMaterial = entityManager.getMaterial(1);
        if (dullMaterial)
        {
            dullMaterial->UseMaterial(shaderList[0]->GetSpecularIntensityLocation(), shaderList[0]->GetShininessLocation());
        }
        meshList[0]->RenderMesh();

        glUseProgram(0);

        // stream before rendering
        video_streamer.stream();

        // render
        mainWindow.swapBuffers();
    }

    // finish streaming
    video_streamer.finish();

    // report the number of frames rendered
    printf("rendered %u frames\n", fr.get_next_frame() - 1);

    return 0;
}