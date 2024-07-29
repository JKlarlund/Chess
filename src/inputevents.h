#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#ifndef inputevents_h
#define inputevents_h

class Input{

    public:
        static bool draggable;
        static double x, y;
        static float n_x, n_y;
        static int width, height;
        Input(GLFWwindow* window, int width, int height);

    private:

        static float normalize(double n);

};

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);




#endif