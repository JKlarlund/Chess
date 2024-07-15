#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
//Launch with gcc -I. main.c glad.c -o main.exe libglfw3.a -lopengl32 -lgdi32 -luser32
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
const char *vertexShaderSource = "#version 330 core\n"

  "layout (location = 0) in vec3 aPos;\n"
  "layout (location = 1) in vec3 aColor;\n"
  
  "out vec3 ourColor;\n"

  "void main(){\n"
  "gl_Position = vec4(aPos, 1.0);\n"
  "ourColor = aColor;\n"
  "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "in vec3 ourColor;\n"
  "void main(){\n"
  "FragColor = vec4(ourColor, 1.0);\n"
  "}\n\0";


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

  unsigned int vertexShader;
  unsigned int fragmentShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  
  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success){
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    printf("Fragment shader did not compile accurately %s\n", infoLog);
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  
  float vertices[] = {
    -0.5f, -0.5f, 0.0, 0.0f, 1.0f, 0.0f,//bottom left
    0.0f, 0.5f, 0.0, 0.0f, 0.0f, 1.0f,//top
    0.5f, -0.5f, 0.0, 1.0f, 0.0f, 0.0f//bottom right
  };
 
  unsigned int indices[] = {
    0, 2, 1, //Our first triangle!
  };

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
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    glBindVertexArray(VAO);

    //Check and call events, swap buffers (something to do with rendering,
    //I have no idea what it is.)
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


