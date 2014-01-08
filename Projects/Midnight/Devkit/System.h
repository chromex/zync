// Copyright (c) 2013 Loren Hoffman
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

class System
{
public:
	System()
		: _scene(NULL)
		, _window(NULL)
	{

	}

	~System()
	{

	}

	void Setup(int width, int height, int pixelSize, const char* title)
	{
		debug.Assert(width > 0, "Width must be greater than zero");
		debug.Assert(height > 0, "Height must be greater than zero");
		debug.Assert(pixelSize > 0, "Pixel size must be greater than zero");
		debug.Assert(title != NULL, "Title cannot be null");

		glfwSetErrorCallback(__ErrorCallback);

		if(!glfwInit())
		{
			debug.Error("glfwInit failed");
		}

		// Disable window resizing
		glfwWindowHint(GLFW_RESIZABLE, 0);

		_window = glfwCreateWindow(width, height, title, NULL, NULL);

		if(!_window)
		{
			glfwTerminate();
			debug.Error("glfwCreateWindow failed");
		}

		glfwMakeContextCurrent(_window);

		glfwSetKeyCallback(_window, __KeyCallback);

		graphics.Initialize(pixelSize);

		debug.Log("Setup complete");
	}

	void Run(Scene* scene)
	{
		debug.Assert(scene != NULL, "Scene parameter must not be null");
		debug.Assert(_window != NULL, "Setup must be called before Run");

		_scene = scene;

		while(!glfwWindowShouldClose(_window))
		{
			_scene->Update();
			graphics.Render();
	        
	        glfwSwapBuffers(_window);
	        glfwPollEvents();
		}

		delete _scene;
		_scene = NULL;

		glfwDestroyWindow(_window);
		glfwTerminate();
	}

	void GetScreenSize(int* width, int* height)
	{
		debug.Assert(width != NULL, "Width must not be null");
		debug.Assert(height != NULL, "Height must not be null");

		glfwGetFramebufferSize(_window, width, height);
	}

private:
	Scene* _scene;
	GLFWwindow* _window;
};

// GLFW callbacks

static void __ErrorCallback(int error, const char* description)
{
	debug.Log(description);
}

static void __KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// TODO: Pass this on to the system
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}