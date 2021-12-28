#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	//设置OpenGL渲染窗口的尺寸大小，即视口(Viewport)
	glViewport(0, 0, width, height);
}

//让所有的输入代码保持整洁
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//glfwSetwindowShouldClose使用把WindowShouldClose属性设置为 true的方法关闭GLFW。
		//下一次while循环的条件检测将会失败，程序将会关闭
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	//初始化GLFW
	glfwInit();
	//配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	//创建一个窗口对象，这个窗口对象存放了所有和窗口相关的数据
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//GLAD是用来管理OpenGL的函数指针
	//初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//告诉GLFW我们希望每当窗口调整大小的时候调用这个函数,会在每次窗口大小被调整的时候被调用
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//渲染循环(Render Loop)
	//glfwWindowShouldClose函数在我们每次循环的开始前检查一次GLFW是否被要求退出，
	//如果是的话该函数返回true然后渲染循环便结束了，之后为我们就可以关闭应用程序了。
	while (!glfwWindowShouldClose(window))
	{
		// 输入
		processInput(window);

		//渲染指令

		//设置清空屏幕所用的颜色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//清空屏幕的颜色缓冲
		//它接受一个缓冲位(Buffer Bit)来指定要清空的缓冲，
		//可能的缓冲位有GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT
		glClear(GL_COLOR_BUFFER_BIT);

		//会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
		glfwSwapBuffers(window);
		//检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
		glfwPollEvents();
	}
	//正确释放/删除之前的分配的所有资源
	glfwTerminate();
	return 0;
}

