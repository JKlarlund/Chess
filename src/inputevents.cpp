#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "inputevents.h"

class Input{

    public:
        
        bool Input::draggable;
        double Input::x, Input::y;
        float Input::n_x, Input::n_y;
        int Input::width, Input::height;

        Input(GLFWwindow* window, int width, int height){
            glfwSetMouseButtonCallback(window, Input::mouse_button_callback);
            this->width = width;
            this->height = height;

            n_x = 0.0f;
            n_y = 0.0f;
            draggable = 0;
            x = 0;
            y = 0;
        }

    private:

        float Input::normalize(double n){
            return -1+((n/Input::width)*2);
        }

        static void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){

            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
                Input::draggable = 1;
                glfwGetCursorPos(window, &x, &y);
                std::cout << "PRESSED: Cursor x at: " << x << " Cursor y at: " << y << "\n";
            }
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
                Input::draggable = 0;
                glfwGetCursorPos(window, &x, &y);
                std::cout << "RELEASED: Cursor x at: " << x << " Cursor y at: " << y << "\n";
            }

            n_x = normalize(x);
            n_y = normalize(y);
        }

};
