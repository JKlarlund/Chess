#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "shaders/shader.h"

#define VERTEX_SIZE 3
#define START_X -1
#define START_Y -1
#define RECT_INDICES_SIZE 6
//A meaningless line to see if Github reindexes.
void framebuffer_size_callback(GLFWwindow*, int, int);

class Engine{

    struct Vector2{double x; double y;};
    unsigned int width, height;
    const int columns = 8;
    const int rows = 8;
    //To draw squares on a column, row grid we need vertices on the edge of the grid. 
    const int boardSize = (columns+1)*(rows+1)*VERTEX_SIZE;
    //We need 6 vertices (2 triangles) for every square.
    const int indicesSize = columns*rows*RECT_INDICES_SIZE;
    public:
        Engine(int width, int height){

            this->width = width;
            this->height = height;

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

            glViewport(0, 0, this->width, this->height);
            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

            float board[boardSize];

            unsigned int indices[indicesSize];

            createBackgroundTiles(board, indices);

            int counter = 0;
            for (int i = 0; i<3*64; i++){
                std::cout << *(board + i) << " ";
                if (i % 3 == 2){std::cout << " " << counter << "\n"; counter++;}
            }
            counter = 0;
            for (int i = 0; i<8*8*6; i++){
                std::cout << *(indices+i) << " ";
                if (i % 3 == 2){ std::cout << " " << counter << "\n"; counter++;}
            }

            unsigned int VBO, EBO, VAO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);            

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(board), board, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            //Renders in wireframe mode
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
                glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);

                glfwSwapBuffers(window);
                glfwPollEvents();
            }

            glfwTerminate();
            return;

        }
    private:
        void loadGlad(){
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
                std::cout << "Failed to initialize GLAD" << std::endl;
            }
        }

        void createBackgroundTiles(float * boardArray, unsigned int * indices){
            //We'll have to do some checks for safety.
            for (int i = 0; i<9; i++){
                for (int j = 0; j<9; j++){
                    int rowShift = i*(columns+1)*VERTEX_SIZE;
                    int colShift = VERTEX_SIZE*j;
                    int positionIncrement = rowShift+colShift;
                    Vector2 vector;
                    vector.x = START_X+j*0.25; //the 0.25 has to go.
                    vector.y = START_Y+i*0.25;
                    *(boardArray + positionIncrement) = vector.x; //pos 1
                    *(boardArray + positionIncrement + 1) = vector.y; //pos 2
                    *(boardArray + positionIncrement + 2) = 0; //pos 3, always 0.
                }
            }

            int counter = 0;
            for (int i = 0; i<8; i++){
                for (int j = 0; j<8; j++){
                    int firstPos = i*(rows+1)+j;
                    int secondPos = (i+1)*(rows+1)+j;
                    int thirdPos = i*(rows+1)+j+1;
                    *(indices+counter++) = firstPos;
                    *(indices+counter++) = secondPos;
                    *(indices+counter++) = thirdPos;
                    //This is the fourth vertex to draw a square, placed one to the right and one up.
                    //Hence taking the third position (one to the right) and adding 9 (one up).
                    *(indices+counter++) = thirdPos+9;
                    *(indices+counter++) = secondPos;
                    *(indices+counter++) = thirdPos;
                }
            }
        }   
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(){

    Engine eng(800, 800);
    eng.createWindow();
    std::cout << "Program has stopped running.";
    return 0;

}
