#include "Window.h"

bool Window::is_vsync_on = false;

Window::Window() {
	width = 800;
	height = 600;
	xChange = 0.0f;
	yChange = 0.0f;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	xChange = 0.0f;
	yChange = 0.0f;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
}

int Window::Initialise() {
	// init glfw
	if (!glfwInit()) {
		printf("glfw init failed");
		glfwTerminate();
		return 1;
	}

	//setup glfw window properties
	// OpenGl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	// core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!mainWindow) {
		printf("GLFW window creation failed");
		glfwTerminate();
		return 1;
	}

	//get buffer size info
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//set context for glfw to use
	glfwMakeContextCurrent(mainWindow);

	// register callbacks
	registerCallbacks();

	//disable cursor
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//set vsync on
	glfwSwapInterval(1);
	is_vsync_on = true;

	//allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("glew init failed :(");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);

	// Transparency blending function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//setup viewport
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);
}

GLfloat Window::getXchange() {
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}
GLfloat Window::getYchange() {
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::PrintGLInfo()
{
	std::cout << "\n=================== :: GL Info :: ===================\n";
	std::cout << "GL Vendor:\t" << glGetString(GL_VENDOR) << "\n";
	std::cout << "GL Renderer:\t" << glGetString(GL_RENDERER) << "\n";
	std::cout << "GL Version:\t" << glGetString(GL_VERSION) << "\n";
	std::cout << "GL Shading ver:\t" << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n\n";

	GLint profile;
	glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);
	if (const auto errorCode = glGetError()) {
		std::cout << "[!] Pending GL error while obtaining profile: " << errorCode << "\n";
		//return;
	}
	if (profile & GL_CONTEXT_CORE_PROFILE_BIT) {
		std::cout << "Core profile" << "\n";
	}
	else {
		std::cout << "Compatibility profile" << "\n";
	}
	std::cout << "=====================================================\n\n";
}

Window::~Window() {
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}