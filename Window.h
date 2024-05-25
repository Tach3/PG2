#pragma once

#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/wglew.h>

#include <string> 

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	int Initialise();

	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	bool* getKeys() { return keys; }
	bool shoot = false;
	GLfloat getXchange();
	GLfloat getYchange();

	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	void Shoot();

	void PrintGLInfo();

	void SetWindowTitle(int FPS){ glfwSetWindowTitle(mainWindow, std::to_string(FPS).c_str()); }

	~Window();
private:
	GLFWwindow* mainWindow;
	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];

	GLfloat lastX, lastY, xChange, yChange;
	bool mouseFirstMoved;

	static bool is_vsync_on;
	
	//screen stuff
	GLFWmonitor* monitor{};
	const GLFWvidmode* mode{};
	static bool is_fullscreen_on;
	int window_xcor{};
	int window_ycor{};
	int window_width_return_from_fullscreen{};
	int window_height_return_from_fullscreen{};

	void registerCallbacks();
	
	double lastShootTime = 0.0;  // Store the last time Shoot was called
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};

