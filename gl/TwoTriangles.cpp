// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "gl_warp.h"
#include <iostream>

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

const char *vertexShaderSource =
"layout (location = 0) in vec3 aPos;"
"void main() {"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
"}";

const char *fragmentShaderSource =
"out vec4 FragColor;"
"void main() {"
"	FragColor = vec4(1.0, 0.2, 0.2, 1.);"
"}";

int main() {
	GLFWwindow *window = gl_warp_init();
	int vertexShader = compile_vertex_shader(vertexShaderSource);
	int fragmentShader = compile_fragment_shader(fragmentShaderSource);
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	gl_warp_LinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices1[] = {
		-.5, +.0, .0,
		-.3, +.5, .0,
		-.3, -.5, .0,
	};
	float vertices2[] = {
		+.5, +.0, .0,
		+.3, +.5, .0,
		+.3, -.5, .0,
	};

	unsigned int vbo1, vbo2, vao1, vao2;
	glGenVertexArrays(1, &vao1);
	glGenVertexArrays(1, &vao2);
	glGenBuffers(1, &vbo1);
	glGenBuffers(1, &vbo2);

	glBindVertexArray(vao1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(vao2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(.25, .25, .25, 1.);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(vao1);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(vao2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &vao2);
	glDeleteVertexArrays(1, &vao1);
	glDeleteBuffers(1, &vbo2);
	glDeleteBuffers(1, &vbo1);
	glfwTerminate();
	return EXIT_SUCCESS;
}

// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "gl_warp.h"
#include <iostream>

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

const char *vertexShaderSource =
"layout (location = 0) in vec3 aPos;"
"void main() {"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
"}";

const char *fragmentShaderSource =
"out vec4 FragColor;"
"void main() {"
"	FragColor = vec4(1.0, 0.2, 0.2, 1.);"
"}";

int main() {
	GLFWwindow *window = gl_warp_init();
	int vertexShader = compile_vertex_shader(vertexShaderSource);
	int fragmentShader = compile_fragment_shader(fragmentShaderSource);
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	gl_warp_LinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices1[] = {
		-.5, +.0, .0,
		-.3, +.5, .0,
		-.3, -.5, .0,
		+.5, +.0, .0,
		+.3, +.5, .0,
		+.3, -.5, .0,
	};

	unsigned int vbo1, vao1;
	glGenVertexArrays(1, &vao1);
	glGenBuffers(1, &vbo1);

	glBindVertexArray(vao1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(.25, .25, .25, 1.);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(vao1);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &vao1);
	glDeleteBuffers(1, &vbo1);
	glfwTerminate();
	return EXIT_SUCCESS;
}
