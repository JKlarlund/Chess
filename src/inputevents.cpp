#include "inputevents.h"

bool Input::draggable;
double Input::x, Input::y;
int Input::width, Input::height;

Input::Input(GLFWwindow* window, int width, int height){
    glfwSetMouseButtonCallback(window, Input::mouse_button_callback);
    this->width = width;
    this->height = height;
    Input::draggable = 0;
    Input::x = 0;
    Input::y = 0;
}

void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
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
}


