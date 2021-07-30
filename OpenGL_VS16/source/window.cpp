#include <window.h>

Window::Window()
{
    camera = Camera(glm::vec3(0.0f, 0.0f, -3.0f));
}

Window::~Window()
{
}

int Window::Create()
{
    // create window
    window = glfwCreateWindow(wndSize.x, wndSize.y, "Learn OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);

    // initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 0;
    }

    // set view port of opengl
    glViewport(0, 0, wndSize.x, wndSize.y);

    // set callback
    auto set_scroll_callback = [](GLFWwindow* w, double x, double y)
    {
        static_cast<Window*>(glfwGetWindowUserPointer(w))->scroll_callback(w, x, y);
    };
    auto set_cursor_pos_callback = [](GLFWwindow* w, double x, double y)
    {
        static_cast<Window*>(glfwGetWindowUserPointer(w))->mouse_callback(w, x, y);
    };
    glfwSetScrollCallback(window, set_scroll_callback);
    glfwSetCursorPosCallback(window, set_cursor_pos_callback);

    // setting glfw etc.
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
    
    return 1;
}

void Window::Destroy()
{
    glfwDestroyWindow(window);
}

void Window::mainLoop()
{
    
}

void Window::process_input()
{
    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.processKeyboard(CAM_SPEED_UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
        camera.processKeyboard(CAM_SPEED_DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS)
    {
        int mode = glfwGetInputMode(window, GLFW_CURSOR);
        if (mode == GLFW_CURSOR_DISABLED)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        if (mode == GLFW_CURSOR_NORMAL)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

void Window::mouse_callback(GLFWwindow* window, double xpos, double ypos)
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

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.processMouseScroll(yoffset);
}