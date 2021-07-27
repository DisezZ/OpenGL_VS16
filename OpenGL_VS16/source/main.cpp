#include <glx.h>
#include <util.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <shader.h>
#include <camera.h>
#include <cube.h>
#include <mesh.h>
#include <model.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const unsigned int chunk_x = 1;
const unsigned int chunk_y = 1;
const unsigned int chunk_z = 1;

int createWindow(GLFWwindow **window, const char *title);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window, Shader program);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));
float lastX = 400;
float lastY = 300;
bool firstMouse = true;

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float mixValue = 0.2f;

std::vector<Vertex> vertice = {
    Vertex {
        glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)
    },
    Vertex {
        glm::vec3(0.5f,  -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)
    },
    Vertex {
        glm::vec3(-0.5f,  -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)
    }
};

unsigned int indice[] = {
    0, 1, 2
};

int main()
{
    // create window
    GLFWwindow* window = NULL;
    if (!createWindow(&window, "Hello World Windowed"))
        return -1;

    // create shader
    Shader myShader("resource/shader/shader.vs", "resource/shader/shader.fs");

    // create model
    //Model myModel("resource/object/backpack/backpack.obj");
    Model myModel("resource/object/cube/Cube.obj");
    stbi_set_flip_vertically_on_load(true);

    float vertices[] = {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    };
    /*unsigned int VAO, VBO;
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // vertex normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    // vertex texture coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(myModel.meshes[0].textures[0].id, "texture_diffuse0"), 0);
    glBindTexture(GL_TEXTURE_2D, myModel.meshes[0].textures[0].id);*/
    /*unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    /// create image
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *img = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    if (img)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(img);
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    /// create image
    img = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
    if (img)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(img);*/
    //myShader.use();

    glm::vec3 cubePosition[chunk_x][chunk_y][chunk_z];
    for (int i = 0; i < chunk_x; ++i)
        for (int j = 0; j < chunk_y; ++j)
            for (int k = 0; k < chunk_z; ++k)
            {
                cubePosition[i][j][k] = glm::vec3((float)i,(float)j,(float)k); 
            }
    unsigned int transformLoc = glGetUniformLocation(myShader.programID, "transform");
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //// render loop
    while (!glfwWindowShouldClose(window))
    {
        // input managing
        process_input(window, myShader);

        // -- render frame --
        // set frame color
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        /*glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);*/
        /*myShader.setFloat("visibility", mixValue); */
        glm::mat4 transform = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        view = camera.getViewMatrix();
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.fov), 800.0f / 600.0f, 0.1f, 100.0f);
        
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        unsigned int projectionLoc = glGetUniformLocation(myShader.programID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        unsigned int viewLoc = glGetUniformLocation(myShader.programID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        for (int i = 0; i < chunk_x; ++i)
            for (int j = 0; j < chunk_y; ++j)
                for (int k = 0; k < chunk_z; ++k)
                {
                    myShader.use();
                    model = glm::mat4(1.0f);
                    model = glm::translate(model, cubePosition[i][j][k]);
                    unsigned int modelLoc = glGetUniformLocation(myShader.programID, "model");
                    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                    //myCube.Draw();
                    //myMesh.Draw(myShader);
                    myModel.Draw(myShader);
                    //glBindVertexArray(VAO);
                    //glDrawArrays(GL_TRIANGLES, 0, 3);
                }
        unsigned int modelLoc = glGetUniformLocation(myShader.programID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        myModel.Draw(myShader);
        // check and call events and swap buffer
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // terminate action
    glfwTerminate();
    return 0;
}

int createWindow(GLFWwindow **window, const char *title)
{
    // initialize glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window object
    *window = glfwCreateWindow(800, 600, title, NULL, NULL);
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
    glViewport(0, 0, 800, 600);
    // set frame resize callback
    glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);
    glfwSetCursorPosCallback(*window, mouse_callback);
    glfwSetScrollCallback(*window, scroll_callback);
    return 1;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window, Shader program)
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        mixValue += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
        if (mixValue >= 1.0f)
            mixValue = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mixValue -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
        if (mixValue <= 0.0f)
            mixValue = 0.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(CAM_FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(CAM_BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(CAM_LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(CAM_RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.processKeyboard(CAM_UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.processKeyboard(CAM_DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse) // initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float offsetX = xpos - lastX;
    float offsetY = ypos - lastY;
    lastX = xpos;
    lastY = ypos;
    camera.processMouseMovement(offsetX, offsetY, true);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.processMouseScroll(yoffset);
}