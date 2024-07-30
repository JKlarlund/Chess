#include <iostream>
#include <GLFW/glfw3.h>

#ifndef inputevents_h
#define inputevents_h

class Input{

    public:
        static bool draggable;
        static double x, y;
        static int width, height;
        Input(GLFWwindow* window, int width, int height);

    private:
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


};




#endif