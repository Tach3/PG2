#include <iostream>

#include "Window.h"

const GLint WIDTH = 1366, HEIGHT = 768;

void Window::registerCallbacks() {
    glfwSetKeyCallback(mainWindow, key_callback);
    glfwSetCursorPosCallback(mainWindow, mouse_callback);
    glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);
    glfwSetMouseButtonCallback(mainWindow, mouse_button_callback);
}

void Window::error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}
void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }
    if (key == GLFW_KEY_V && action == GLFW_PRESS) {
        is_vsync_on = !is_vsync_on;
        glfwSwapInterval(is_vsync_on);
        std::cout << "VSync: " << is_vsync_on << "\n";
    }

    if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
        theWindow->is_fullscreen_on = !theWindow->is_fullscreen_on;
        if (theWindow->is_fullscreen_on) {
            glfwGetWindowPos(window, &theWindow->window_xcor, &theWindow->window_ycor);
            glfwGetWindowSize(window, &theWindow->window_width_return_from_fullscreen, &theWindow->window_height_return_from_fullscreen);
            if (theWindow->window_height_return_from_fullscreen == 0) theWindow->window_height_return_from_fullscreen++;
            glfwSetWindowMonitor(window, theWindow->monitor, 0, 0, theWindow->mode->width, theWindow->mode->height, theWindow->mode->refreshRate);

        }
        else {
            glfwSetWindowMonitor(window, nullptr, theWindow->window_xcor, theWindow->window_ycor, theWindow->window_width_return_from_fullscreen, theWindow->window_height_return_from_fullscreen, 0);
        }
        std::cout << "Fullscreen toggle\n";
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

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    auto theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    theWindow->width = width;
    theWindow->height = height;
    glViewport(0, 0, width, height);
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    auto theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double currentTime = glfwGetTime();
        if (currentTime - theWindow->lastShootTime >= 1.0) {  // Check if 1 second has passed
            theWindow->Shoot();
            theWindow->PlaySound("Sound/8BitShoot.wav");
            theWindow->lastShootTime = currentTime;  // Update the last shoot time
        }
    }
}


