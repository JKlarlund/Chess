#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include "shader.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main(){
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* window = glfwCreateWindow(800, 800, "Jonathan Trying Cool Stuff!", NULL, NULL);
  if (window == NULL){
    printf("Could not create the GLFW window sadge");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    printf("Something failed with glad");
    return -1;
  }
  
  
  Shader ourShader("shaders/shader.vs", "shaders/shader.fs");

  float vertices[] = {
    -0.5f, -0.5f, 0.0, 0.0f, 1.0f, 0.0f,//bottom left, color gradiant at bottom left
    0.0f, 0.5f, 0.0, 0.0f, 0.0f, 1.0f,//top, color gradient at top
    0.5f, -0.5f, 0.0, 1.0f, 0.0f, 0.0f//bottom right, color gradient at bottom right
  };
 
  unsigned int indices[] = {
    0, 2, 1, //Our first triangle!
  };

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  //Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
  glEnableVertexAttribArray(0); 

  //Color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3*sizeof(float)));
  glEnableVertexAttribArray(1);
  
  //glBindBuffer(GL_ARRAY_BUFFER, 0);
  //glBindVertexArray(0);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glViewport(0, 0, 800, 800);

  while(!glfwWindowShouldClose(window)){
    //Registering key presses
    processInput(window);

    //Rendering
    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(ourShader.ID, "ourColor");

    ourShader.use();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    

    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    
    //Don't know what this is.
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0; 
  
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
    glfwSetWindowShouldClose(window, 1);
  }
}


