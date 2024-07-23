#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "shader.h"

#define VERTEX_SIZE 3
#define FLOAT 4
#define START_X -1
#define START_Y -1

void framebuffer_size_callback(GLFWwindow*, int, int);

class Engine{

    struct Vector2{double x; double y;};
    unsigned int width, height;
    double widthIncrement, heightIncrement;
    double widthZeroLine, heightZeroLine;
    float white[3] = {1.0f, 1.0f, 1.0f};
    float black[3] = {0.0f, 0.0f, 0.0f};

    public:
        Engine(int width, int height){

            this->width = width;
            this->height = height;

            this->widthIncrement = width*1.0/8;
            this->heightIncrement = height*1.0/8;

            this->widthZeroLine = width*1.0/2;
            this->heightZeroLine = height*1.0/2;

            std::cout << "width is: " << width << "\n";

        }

        void createWindow(){
            glfwInit();            

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            GLFWwindow* window = glfwCreateWindow(this->width, this->height, "Test", NULL, NULL);


            glfwMakeContextCurrent(window);

            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


            loadGlad();
            
            
            Shader ourShader("shaders/shader.vs", "shaders/shader.fs");


            glViewport(0, 0, 800, 600);
            //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

            float board[64*VERTEX_SIZE];

            createBackgroundTiles(board);

            int counter = 0;
            for (int i = 0; i<3*64; i++){
                std::cout << *(board + i) << " ";
                if (i % 3 == 2){counter++; std::cout << " " << counter << "\n";}
            }

            float newVertices[] = {
                0.5f,  0.5f, 0.0f,  // top right
                0.5f, -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f,  // bottom left
                -0.5f,  0.5f, 0.0f   // top left 
            };

            unsigned int indices[] = {
                0, 1, 3,  // first Triangle
                1, 2, 3   // second Triangle
            };


            unsigned int VBO, EBO, VAO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);            

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(newVertices), newVertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            while(!glfwWindowShouldClose(window)){
                if(glfwGetKey(window, GLFW_KEY_ESCAPE) == 1){
                    glfwSetWindowShouldClose(window, true);
                }
                /** 
                bool changed = false;   
                if (time > 20 && !changed){
                    glBindBuffer(GL_ARRAY_BUFFER, colors);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(black), black, GL_STATIC_DRAW);
                    changed = true;
                    //This freakin' changes the color!!
                }
                **/

                glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                ourShader.use();

                glBindVertexArray(VAO);            
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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

        void createBackgroundTiles(float * boardArray){
            //We'll have to do some checks for safety.
            for (int i = 0; i<8; i++){
                for (int j = 0; j<8; j++){
                    int positionIncrement = (i*24)+(3*j);
                    Vector2 vector;
                    vector.x = j*this->widthIncrement;
                    vector.y = i*this->heightIncrement;
                    vector = normalizeVector(vector);
                    *(boardArray + positionIncrement) = vector.x; //pos 1
                    *(boardArray + positionIncrement + 1) = vector.y; //pos 2
                    *(boardArray + positionIncrement + 2) = 0; //pos 3, always 0.
                }
            }
        }

        Vector2 normalizeVector(Vector2 vector){
            
            vector.x = normalizeCoordinate(vector.x, widthZeroLine, width);
            vector.y = normalizeCoordinate(vector.y, heightZeroLine, height);

            return vector;

        }

        double normalizeCoordinate(double val, double line, double max){
            if (val < line){
                val = -(val / max);
            }
            else if (val > line){
                val = val / max;
            }
            else{val = 0;}

            return correctNegativeZero(val);            
        }

        double correctNegativeZero(double val){
            if (val == -0.0 || val == 0.0){
                return 0.0;
            }
            else{return val;}
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
