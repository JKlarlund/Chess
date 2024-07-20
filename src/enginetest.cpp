#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "shader.h"

void framebuffer_size_callback(GLFWwindow*, int, int);

class Engine{

    unsigned int width, height;
    double widthIncrement, heightIncrement;
    float white[3] = {1.0f, 1.0f, 1.0f};
    float black[3] = {0.0f, 0.0f, 0.0f};

    public:
        Engine(int width, int height){

            this->width = width;
            this->height = height;

            this->widthIncrement = width/8;
            this->heightIncrement = height/8;

            glfwInit();            

        }

        void createWindow(){
            GLFWwindow* window = glfwCreateWindow(this->width, this->height, "Test", NULL, NULL);

            glfwMakeContextCurrent(window);

            loadGlad();
            
            
            Shader ourShader("shaders/shader.vs", "shaders/shader.fs");


            //glViewport(0, 0, 800, 600);
            //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

            unsigned int vertex, colors;

            float vertices[] = {
                -1.0, -1.0, 0, 1.0f, 1.0f, 1.0f,
                -1.0, -0.8f, 0, 1.0f, 1.0f, 1.0f,
                //-1.0, -0.8f, 0, 1.0f, 1.0f, 1.0f,
                //-0.8, -0.8f, 0, 1.0f, 1.0f, 1.0f,
                -0.8, -0.8f, 0, 1.0f, 1.0f, 1.0f,
                -0.8f, -1.0, 0, 1.0f, 1.0f, 1.0f
                //1.0, 1.0f, 0, 1.0f, 1.0f, 1.0f
            }; //Doesn't actually have anything to do with this WTF!

            float newVertices[] = {
                -1.0, -1.0, 0,
                -1.0, -0.8f, 0,
                -0.8, -0.8f, 0,
                -0.8f, -1.0, 0
            };

            //Save space by EBO's.
            glGenBuffers(1, &vertex);
            glBindBuffer(GL_ARRAY_BUFFER, vertex);
            glBufferData(GL_ARRAY_BUFFER, sizeof(newVertices), newVertices, GL_STATIC_DRAW);

            glGenBuffers(1, &colors); 
            glBindBuffer(GL_ARRAY_BUFFER, colors);
            glBufferData(GL_ARRAY_BUFFER, sizeof(white), white, GL_STATIC_DRAW);

            GLuint VAO = 0;
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, vertex);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0); //Stride is 0
            glBindBuffer(GL_ARRAY_BUFFER, colors);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);

            int count = 0;


            while(!glfwWindowShouldClose(window)){

                double time = glfwGetTime();
                bool changed = false;
                
                if (time > 20 && !changed){
                    glBindBuffer(GL_ARRAY_BUFFER, colors);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(black), black, GL_STATIC_DRAW);
                    changed = true;
                    //This freakin' changes the color!!
                }
                
                ourShader.use();


                glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                if(glfwGetKey(window, GLFW_KEY_ESCAPE) == 1){
                    glfwSetWindowShouldClose(window, true);
                }
                /**
                if ((count % 2) == 0){
                    glUniform4f(glGetUniformLocation(ourShader.ID, "ourColor"), 1.0f, 1.0f, 1.0f, 1.0f);
                }
                else{
                    glUniform4f(glGetUniformLocation(ourShader.ID, "ourColor"), 0.0f, 0.0f, 0.0f, 1.0f);
                }
                **/
                //This doesn't work for some reason, but might be better.
                count = count + 1;
                glDrawArrays(GL_POLYGON, 0, 4);

                glfwSwapBuffers(window);
                glfwPollEvents();
            }

            glfwTerminate();
            return;

        }

        void loadGlad(){
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
                std::cout << "Failed to initialize GLAD" << std::endl;
            }
        }

        float * getWhite(){
            return this->white;
        }

        float * getBlack(){
            return this->black;
        }

};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(){

    Engine eng(1200, 1200);
    eng.createWindow();
    std::cout << "Program has stopped running.";
    return 0;

}