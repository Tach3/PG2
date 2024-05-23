#include <iostream>

#include "Window.h"

void Window::registerCallbacks() {
    glfwSetKeyCallback(mainWindow, key_callback);
    glfwSetCursorPosCallback(mainWindow, mouse_callback);
}

void Window::error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}
void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_V && action == GLFW_PRESS) {
        is_vsync_on = !is_vsync_on;
        glfwSwapInterval(is_vsync_on);
        std::cout << "VSync: " << is_vsync_on << "\n";
    }

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            theWindow->keys[key] = true;
        }
        else if (action == GLFW_RELEASE) {
            theWindow->keys[key] = false;
        }
    }
}

void Window::mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    
    if (theWindow->mouseFirstMoved) {
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mouseFirstMoved = false;
    }

    theWindow->xChange = xPos - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - yPos;

    theWindow->lastX = xPos;
    theWindow->lastY = yPos;

    //printf("X:%.6f, Y:%.6f\n", theWindow->xChange, theWindow->yChange);
}


