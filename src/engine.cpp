#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Engine{

    public:
        GLFWwindow* window;
        unsigned int VBO, VAO, EBO;

        Engine(int width, int height){
            glfwInit();
            window = setupWindow(width, height);
            glfwMakeContextCurrent(window);
            loadGlad();
            Shader ourShader("shaders/shader.vs", "shaders/shader.fs");
            setupBuffers();
            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
            glViewport(0, 0, width, height);

            render(ourShader);

        }

        void setupBuffers(){
            float vertices[] = {
                -0.5f, -0.5f, 0.0, 0.0f, 1.0f, 0.0f,//bottom left, color gradiant at bottom left
                0.0f, 0.5f, 0.0, 0.0f, 0.0f, 1.0f,//top, color gradient at top
                0.5f, -0.5f, 0.0, 1.0f, 0.0f, 0.0f//bottom right, color gradient at bottom right
            };
            float indices[] = {0, 2, 1};
            //Setting up the VAO
            glGenVertexArrays(1, &(this->VAO));
            glBindVertexArray(this->VAO);

            //Setting up the VBO
            glGenBuffers(1, &(this->VBO));
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

            //Setting up the EBO
            glGenBuffers(1, &(this->EBO));
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

            //Storing data
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            //Position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
            glEnableVertexAttribArray(0); 

            //Color attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3*sizeof(float)));
            glEnableVertexAttribArray(1);

        }

        void render(Shader ourShader){
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
                glBindVertexArray(this->VAO);
                glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
                
                glfwSwapBuffers(window);
                glfwPollEvents();
            }
            close();
            return;
        }


        void close(){
            glfwTerminate();
        }

        GLFWwindow* setupWindow(int width, int height){
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            GLFWwindow* window = glfwCreateWindow(width, height, "Jonathan Trying Cool Stuff!", NULL, NULL);
            if (window == NULL){
                printf("---Window was not created---");
                glfwTerminate();
                return NULL;
            }
            return window;
        }

        void loadGlad(){
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            printf("---Loading GLAD failed---");
            return;
            }
        }

        void processInput(GLFWwindow* window){
            if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
                glfwSetWindowShouldClose(window, 1);
            }
        }

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
            glViewport(0, 0, width, height);
        }
};



int main(){
    Engine engine(800, 800);
    return 0;
}


