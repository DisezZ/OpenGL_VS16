#include <glx.h>
#include <util.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "imgui\imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <window.h>
#include <shader.h>
#include <camera.h>
#include <cube.h>
#include <mesh.h>
#include <model.h>

const unsigned int SRC_WIDTH = 1280;
const unsigned int SRC_HEIGHT = 720;
const unsigned int chunk_x = 1;
const unsigned int chunk_y = 1;
const unsigned int chunk_z = 1;

//int createWindow(GLFWwindow** window, const char* title);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(Window window);
//void mouse_callback(GLFWwindow *window, double xpos, double ypos);
//void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

//Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
// float lastX = 400;
// float lastY = 300;
// bool firstMouse = true;

//float deltaTime = 0.0f; // Time between current frame and last frame
//float lastFrame = 0.0f; // Time of last frame

glm::vec3 objectPositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

int main()
{
    // initialize glfw
    glxSetup();
    // create window
    Window window;
    if (!window.Create())
        return -1;

    // create shader
    Shader shader_cube("resource/shader/shader.vs", "resource/shader/object.fs");
    Shader shader_cubeLight("resource/shader/shader.vs", "resource/shader/light.fs");

    // create model
    //Model myModel("resource/object/backpack/backpack.obj");
    Model lightCube("resource/object/cube/Cube.obj");
    Model myBackpack("resource/object/backpack/backpack.obj");
    
    //// render loop
    bool show_demo_window = true;
    while (!glfwWindowShouldClose(window.window))
    {
        // input managing
        window.process_input();

        // -- render frame --
        // set frame color
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
        };
        glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        glm::mat4 transform = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        view = window.camera.getViewMatrix();
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(window.camera.fov), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::vec3 lightPos = glm::vec3(sin(glfwGetTime()) * 3, 1.0f, cos(glfwGetTime()) * 3);
        shader_cubeLight.use();
        shader_cubeLight.setMat4("projection", projection);
        shader_cubeLight.setMat4("view", view);
        shader_cubeLight.setMat4("transform", transform);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        shader_cubeLight.setMat4("model", model);
        for (unsigned int i = 0; i < 4; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]*glm::vec3(3.0f));
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader_cubeLight.setMat4("model", model);

            lightCube.Draw(shader_cubeLight);
        }
        shader_cube.use();
        shader_cube.setMat4("projection", projection);
        shader_cube.setMat4("view", view);
        shader_cube.setMat4("transform", transform);
        model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        //shader_cube.setMat4("model", model);
        shader_cube.setVec3("viewPos", window.camera.position);
        shader_cube.setFloat("material.shininess", 32.0f);
        shader_cube.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        shader_cube.setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        shader_cube.setVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
        shader_cube.setVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
        for (int i = 0; i < 4; i++)
        {
            char buffer[64];

            sprintf_s(buffer, sizeof(buffer), "pointLight[%i].position", i);
            shader_cube.setVec3(buffer, pointLightPositions[i]*glm::vec3(3.0f));

            sprintf_s(buffer, sizeof(buffer), "pointLight[%i].ambient", i);
            shader_cube.setVec3(buffer, glm::vec3(0.05f));

            sprintf_s(buffer, sizeof(buffer), "pointLight[%i].diffuse", i);
            shader_cube.setVec3(buffer, glm::vec3(0.8f));

            sprintf_s(buffer, sizeof(buffer), "pointLight[%i].specular", i);
            shader_cube.setVec3(buffer, glm::vec3(1.0f));

            sprintf_s(buffer, sizeof(buffer), "pointLight[%i].constant", i);
            shader_cube.setFloat(buffer, 1.0f);

            sprintf_s(buffer, sizeof(buffer), "pointLight[%i].linear", i);
            shader_cube.setFloat(buffer, 0.09f);

            sprintf_s(buffer, sizeof(buffer), "pointLight[%i].quadratic", i);
            shader_cube.setFloat(buffer, 0.032f);
        }
        shader_cube.setVec3("spotLight.position", window.camera.position);
        shader_cube.setVec3("spotLight.direction", window.camera.front);
        shader_cube.setVec3("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
        shader_cube.setVec3("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        shader_cube.setVec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shader_cube.setFloat("spotLight.constant", 1.0f);
        shader_cube.setFloat("spotLight.linear", 0.09);
        shader_cube.setFloat("spotLight.quadratic", 0.032);
        shader_cube.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        shader_cube.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        shader_cube.setVec3("light.position", window.camera.position);
        shader_cube.setVec3("light.direction", window.camera.getViewDir());
        shader_cube.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
        shader_cube.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
        shader_cube.setVec3("light.ambient", glm::vec3(0.1f));
        shader_cube.setVec3("light.diffuse", glm::vec3(1.0f));
        shader_cube.setVec3("light.specular", glm::vec3(1.0f));
        shader_cube.setFloat("light.constant", 1.0f);
        shader_cube.setFloat("light.linear", 0.09f);
        shader_cube.setFloat("light.quadratic", 0.032f);
        for (unsigned int i = 0; i < 10; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader_cube.setMat4("model", model);
            myBackpack.Draw(shader_cube);
        }
        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        // check and call events and swap buffer
        glfwPollEvents();
        glfwSwapBuffers(window.window);
    }

    // terminate action
    window.Destroy();
    glxTerminate();
    return 0;
}

/*int createWindow(GLFWwindow** window, const char* title)
{

    // create window object
    *window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, title, NULL, NULL);
    if (*window == NULL)
    {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return 0;
    }
    // initialize glad
    glfwMakeContextCurrent(*window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 0;
    }
    // set view port of opengl
    glViewport(0, 0, SRC_WIDTH, SRC_HEIGHT);
    // set frame resize callback
    glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);
    glfwSetCursorPosCallback(*window, mouse_callback);
    glfwSetScrollCallback(*window, scroll_callback);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(*window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    return 1;
}*/

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//void process_input(Window window)
//{
//    float currentFrame = glfwGetTime();
//    deltaTime = currentFrame - lastFrame;
//    lastFrame = currentFrame;
//    if (glfwGetKey(window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window.window, true);
//    if (glfwGetKey(window.window, GLFW_KEY_W) == GLFW_PRESS)
//        window.camera.processKeyboard(CAM_FORWARD, deltaTime);
//    if (glfwGetKey(window.window, GLFW_KEY_S) == GLFW_PRESS)
//        window.camera.processKeyboard(CAM_BACKWARD, deltaTime);
//    if (glfwGetKey(window.window, GLFW_KEY_A) == GLFW_PRESS)
//        window.camera.processKeyboard(CAM_LEFT, deltaTime);
//    if (glfwGetKey(window.window, GLFW_KEY_D) == GLFW_PRESS)
//        window.camera.processKeyboard(CAM_RIGHT, deltaTime);
//    if (glfwGetKey(window.window, GLFW_KEY_SPACE) == GLFW_PRESS)
//        window.camera.processKeyboard(CAM_UP, deltaTime);
//    if (glfwGetKey(window.window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//        window.camera.processKeyboard(CAM_DOWN, deltaTime);
//    if (glfwGetKey(window.window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
//        window.camera.processKeyboard(CAM_SPEED_UP, deltaTime);
//    if (glfwGetKey(window.window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
//        window.camera.processKeyboard(CAM_SPEED_DOWN, deltaTime);
//    if (glfwGetKey(window.window, GLFW_KEY_P) == GLFW_PRESS)
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    if (glfwGetKey(window.window, GLFW_KEY_L) == GLFW_PRESS)
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
//    if (glfwGetKey(window.window, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS)
//    {
//        int mode = glfwGetInputMode(window.window, GLFW_CURSOR);
//        if (mode == GLFW_CURSOR_DISABLED)
//            glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//        if (mode == GLFW_CURSOR_NORMAL)
//            glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//    }
//}   

//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//    if (firstMouse) // initially set to true
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//    float offsetX = xpos - lastX;
//    float offsetY = ypos - lastY;
//    lastX = xpos;
//    lastY = ypos;
//    camera.processMouseMovement(offsetX, offsetY, true);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.processMouseScroll(yoffset);
//}
