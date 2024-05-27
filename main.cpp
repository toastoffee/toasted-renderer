#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <shader.h>
#include <path_helper.h>
#include <render_window.h>
#include <camera.h>
#include <input_system.h>
#include <components/model.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// 设置
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera mainCamera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main() {

    RenderWindow mainWindow = RenderWindow(&mainCamera, "toasted-renderer", SCR_WIDTH, SCR_HEIGHT);
    GLFWwindow *window = mainWindow.GetWindow();

    InputSystem::Instance()->Init(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    mainWindow.EnableDepthTest();



    Shader myShader(PathHelper::constructFilePath("shaders/texture.vert"),
                    PathHelper::constructFilePath("shaders/texture.frag"));

    Model nanosuitModel(PathHelper::constructFilePath("resources/models/nanosuit/nanosuit.obj"));

    myShader.Use();

    glm::mat4 view          = glm::mat4(1.0f);
    glm::mat4 projection    = glm::mat4(1.0f);

//    view                    = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
//    projection              = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT,0.1f, 100.0f);


    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {

        if (InputSystem::Instance()->GetKey(GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, true);

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        mainCamera.Update(deltaTime);

        // render
        // ------
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view                    = mainCamera.GetViewMatrix();
        projection              = mainCamera.GetProjectionMatrix((float)SCR_WIDTH / (float)SCR_HEIGHT,0.1f, 100.0f);

        myShader.SetMat4("view", view);
        myShader.SetMat4("projection", projection);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f,-10.0f,-30.f));

        float angle = 100.0f;
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
        myShader.SetMat4("model", model);


        nanosuitModel.Draw(myShader);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;

}


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    mainCamera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    mainCamera.ProcessMouseScroll(static_cast<float>(yoffset));
}