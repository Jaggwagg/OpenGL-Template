#include "shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

void processInput(GLFWwindow* window);

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

/* Window properties */
const GLuint SCR_WIDTH = 1280;
const GLuint SCR_HEIGHT = 720;

int main() {

    /* Setup GLFW */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /* Create window */
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cout << "ERROR_GLFW:FAILED_TO_CREATE_WINDOW\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    /* Check if GLAD is not initalized */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ERROR_GLAD:FAILED_TO_INIT_GLAD\n";
        return -1;
    }

    /* Create shader */
    Shader shader("res/shaders/shader.vert", "res/shaders/shader.frag");

    /********************** Create rectangle **********************/
    
    /* Vertex array, buffer, and element buffer objects */
    GLuint VAO, VBO, EBO;

    /* Rectangle vertices */
    GLfloat vertices[] = {                
        // Positions(x, y, z)   // Colors           // Texture coords
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
        0.5f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        0.5f, -0.5f, 0.0f,      1.0f, 1.0f, 0.0f,   1.0f, 0.0f
    };

    /* Rectangle indices */
    GLuint indices[] = {
        0, 1, 2,    // First triangle
        0, 2, 3     // Second triangle
    };

    /* Generate array/buffer objects */
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    /* Bind array/buffer objects with corresponding data*/
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /* Position */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /* Color */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    /* Shader coordinates */
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    /* Unbind vertex/buffer arrays/objects */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /********************** Create textures **********************/
    
    /* Flip images */
    stbi_set_flip_vertically_on_load(true);

    /* Texture values */
    GLint width, height, nrChannels;
    const char* imagePath;
    unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);

    /************** Texture 1 **************/
    GLuint texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    /* Texture 1 data */
    imagePath = "res/images/container.jpg";
    data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0 ,GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "ERROR_TEXTURE:FAILED_TO_LOAD_TEXTURE:\n" << imagePath << std::endl;
    }
    stbi_image_free(data);

    /************** Texture 2 **************/
    GLuint texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    /* Texture 2 data */
    imagePath = "res/images/awesomeface.png";
    data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0 ,GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "ERROR_TEXTURE:FAILED_TO_LOAD_TEXTURE:\n" << imagePath << std::endl;
    }
    stbi_image_free(data);

    /* Shader and textures */
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    /********************** Render loop **********************/
    while (!glfwWindowShouldClose(window)) {
        
        /* Process user input */
        processInput(window);

        /* Set background color and clear color buffer */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Bind texture */
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        /* Use shader program */
        shader.use();

        /* Matrix transformations */
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, (GLfloat)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        shader.setMat4("transform", transform);

        /* Draw rectangle */
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap buffer and poll IO events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /* End GLFW */
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}