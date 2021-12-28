//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
////顶点着色器源码
//const char *vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"layout (location = 1) in vec3 aColor; // 颜色变量的属性位置值为 1\n"
//"out vec3 ourColor; // 向片段着色器输出一个颜色\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos, 1.0);\n"
//"	ourColor = aColor; // 将ourColor设置为我们从顶点数据那里得到的输入颜色\n"
//"}\0";
//
////片段着色器源码
//const char *fragmentShaderSource1 = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec3 ourColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(ourColor, 1.0f);\n"
//"}\n\0";
//
//
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow *window);
//
//
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
//
//	//告诉GLFW我们希望每当窗口调整大小的时候调用这个函数,会在每次窗口大小被调整的时候被调用
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	//GLAD是用来管理OpenGL的函数指针
//	//初始化GLAD
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//
//	//build and compile our shader program
//	// ------------------------------------
//	// vertex shader
//	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	//编译顶点着色器
//	glCompileShader(vertexShader);
//	// check for shader compile errors
//	int success;
//	char infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	// fragment shader
//	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource1, NULL);
//	glCompileShader(fragmentShader);
//	// check for shader compile errors
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	// link shaders
//	int shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//
//	// check for linking errors
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success) {
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//	}
//
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//
//
//
//	float Triangle[] = {
//		0.5f, -0.5f, 0.0f,  // bottom right
//		-0.5f, -0.5f, 0.0f,  // bottom left
//		 0.0f,  0.5f, 0.0f   // top 
//	};
//
//	float vertices[] = {
//		// 位置              // 颜色
//		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
//		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
//		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
//	};
//
//
//	unsigned int VBO, VAO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//
//	//生成一个VEO对象,类似VBO
//	//glGenBuffers(1, &EBO);
//
//	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//	glBindVertexArray(VAO);
//
//	//顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER,使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//把之前定义的顶点数据vertices复制到缓冲的内存中
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	
//	// 位置属性
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// 颜色属性
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	glBindVertexArray(VAO);
//
//
//	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
//	//glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//	//glBindVertexArray(0);
//
//	// uncomment this call to draw in wireframe polygons.
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	// as we only have a single shader, we could also just activate our shader once beforehand if we want to 
//	glUseProgram(shaderProgram);
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
//		// draw our first triangle 激活着色器
//		/*glUseProgram(shaderProgram);
//
//		// update shader uniform  更新uniform颜色
//		float timeValue = glfwGetTime();
//		float greenValue = sin(timeValue) / 2.0f + 0.5f;
//		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/
//
//		// 绘制三角形
//		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//
//		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//		//glBindVertexArray(0); // no need to unbind it every time 
//
//		// 交换缓冲并查询IO事件
//		//会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
//		glfwSwapBuffers(window);
//		//检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
//		glfwPollEvents();
//	}
//
//
//	// optional: de-allocate all resources once they've outlived their purpose:
//	// ------------------------------------------------------------------------
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteProgram(shaderProgram);
//
//
//	//正确释放/删除之前的分配的所有资源
//	glfwTerminate();
//	return 0;
//}
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