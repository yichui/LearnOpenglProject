//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//#include "stb_image.h"
//#include "ShaderFactory.h"
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	//设置OpenGL渲染窗口的尺寸大小，即视口(Viewport)
//	glViewport(0, 0, width, height);
//}
//
////让所有的输入代码保持整洁
//void processInput(GLFWwindow *window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//	{
//		//glfwSetwindowShouldClose使用把WindowShouldClose属性设置为 true的方法关闭GLFW。
//		//下一次while循环的条件检测将会失败，程序将会关闭
//		glfwSetWindowShouldClose(window, true);
//	}
//}
//
//int main()
//{
//	// glfw: initialize and configure
//	// ------------------------------
//	//初始化GLFW
//	glfwInit();
//	//配置GLFW
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//	// glfw window creation
//	// --------------------
//	//创建一个窗口对象，这个窗口对象存放了所有和窗口相关的数据
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	//告诉GLFW我们希望每当窗口调整大小的时候调用这个函数,会在每次窗口大小被调整的时候被调用
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	//GLAD是用来管理OpenGL的函数指针
//	//初始化GLAD
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	Shader ourShader("shaders/test_vert_shader.txt", "shaders/test_frag_shader.txt");
//
//	// set up vertex data (and buffer(s)) and configure vertex attributes
//	// ------------------------------------------------------------------
//	float vertices[] = {
//		// positions          // colors           // texture coords
//		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
//		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
//		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
//		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
//	};
//	unsigned int indices[] = {
//		0, 1, 3, // first triangle
//		1, 2, 3  // second triangle
//	};
//	unsigned int VBO, VAO, EBO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	// position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// color attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//	// texture coord attribute
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//
//	//纹理也是使用ID
//	unsigned int texture;
//	glGenTextures(1, &texture);
//
//	glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元
//	//绑定,让之后任何的纹理指令都可以配置当前绑定的纹理
//	glBindTexture(GL_TEXTURE_2D, texture);
//
//	// 为当前绑定的纹理对象设置环绕、过滤方式
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	int width, height, nrChannels;
//	unsigned char *data = stbi_load("resources/container.jpg", &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		/*
//		第一个参数指定了纹理目标(Target)。设置为GL_TEXTURE_2D意味着会生成与当前绑定的纹理对象在同一个目标上的纹理（任何绑定到GL_TEXTURE_1D和GL_TEXTURE_3D的纹理不会受到影响）。
//		第二个参数为纹理指定多级渐远纹理的级别，如果你希望单独手动设置每个多级渐远纹理的级别的话。这里我们填0，也就是基本级别。
//		第三个参数告诉OpenGL我们希望把纹理储存为何种格式。我们的图像只有RGB值，因此我们也把纹理储存为RGB值。
//		第四个和第五个参数设置最终的纹理的宽度和高度。我们之前加载图像的时候储存了它们，所以我们使用对应的变量。
//		下个参数应该总是被设为0（历史遗留的问题）。
//		第七第八个参数定义了源图的格式和数据类型。我们使用RGB值加载这个图像，并把它们储存为char(byte)数组，我们将会传入对应值。
//		最后一个参数是真正的图像数据。
//		*/
//		//调用glTexImage2D时，当前绑定的纹理对象就会被附加上纹理图像
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		//要使用多级渐远纹理,直接在生成纹理之后调用glGenerateMipmap
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//	}
//	//释放图像的内存
//	stbi_image_free(data);
//
//
//
//	//渲染循环(Render Loop)
//	//glfwWindowShouldClose函数在我们每次循环的开始前检查一次GLFW是否被要求退出，
//	//如果是的话该函数返回true然后渲染循环便结束了，之后为我们就可以关闭应用程序了。
//	while (!glfwWindowShouldClose(window))
//	{
//		// 输入
//		processInput(window);
//
//		//渲染指令
//
//		//设置清空屏幕所用的颜色
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		//清空屏幕的颜色缓冲
//		//它接受一个缓冲位(Buffer Bit)来指定要清空的缓冲，
//		//可能的缓冲位有GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// render container
//		ourShader.use();
//		
//		// bind Texture
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glBindVertexArray(VAO);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//		//会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
//		glfwSwapBuffers(window);
//		//检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
//		glfwPollEvents();
//	}
//	//正确释放/删除之前的分配的所有资源
//	glfwTerminate();
//	return 0;
//}
//
