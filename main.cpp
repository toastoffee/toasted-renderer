#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <shader.h>
#include <path_helper.h>
#include <render_window.h>
#include <camera.h>
#include <components/model.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// 设置
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {


    Camera mainCamera = Camera();

    RenderWindow mainWindow = RenderWindow(&mainCamera, "toasted-renderer", SCR_WIDTH, SCR_HEIGHT);
    GLFWwindow *window = mainWindow.GetWindow();

    mainWindow.EnableDepthTest();


//    float vertices[] = {
//            -0.5f, -0.5f, -0.5f,
//            0.5f, -0.5f, -0.5f,
//            -0.5f,  0.5f, -0.5f,
//            0.5f,  0.5f, -0.5f,
//            0.5f, 0.5f, 0.5f,
//            0.5f, -0.5f, 0.5f,
//            -0.5f, 0.5f, 0.5f,
//            -0.5f, -0.5f, 0.5f,
//    };
//
//    unsigned int indiecs[] = {
//            0, 1, 2,
//            1, 3, 2,
//            1, 4, 3,
//            1, 5,4,
//            2, 3, 6,
//            3, 4, 6,
//            0, 1,7,
//            1, 5, 7,
//            2, 0, 6,
//            0, 7, 6,
//            4, 5, 6,
//            6, 5, 7
//    };
//
//    unsigned int VBO, VAO, EBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//
//    // 首先绑定顶点数组对象(Vertex Array Object, VAO)
//    // 接着绑定并设置顶点缓冲对象(Vertex Buffer Object, VBO)
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indiecs), indiecs, GL_STATIC_DRAW);
//
//    // position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);

    Shader myShader(PathHelper::constructFilePath("shaders/texture.vert"),
                    PathHelper::constructFilePath("shaders/texture.frag"));

    Model nanosuitModel(PathHelper::constructFilePath("resources/models/nanosuit/nanosuit.obj"));

    myShader.Use();

    glm::mat4 view          = glm::mat4(1.0f);
    glm::mat4 projection    = glm::mat4(1.0f);

    view                    = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
    projection              = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT,0.1f, 100.0f);

    myShader.SetMat4("view", view);
    myShader.SetMat4("projection", projection);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // render
        // ------
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myShader.Use();

//        glBindVertexArray(VAO);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f,-10.0f,-30.f));

        float angle = 100.0f;
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
        myShader.SetMat4("model", model);

//        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        nanosuitModel.Draw(myShader);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;

}
