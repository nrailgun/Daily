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
"#version 330 core \n"
"layout (location = 0) in vec3 aPos;"
"void main() {"
"	gl_Position = vec4(aPos, 1.0);"
"}";

const char *fragmentShaderSource =
"#version 330 core \n"
"out vec4 FragColor;"
"uniform vec4 ourColor;"
"void main() {"
"	FragColor = ourColor;"
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

	float vertices[] = {
		+.5, +.5, .0,
		+.5, -.5, .0,
		-.5, -.5, .0,
	};

	unsigned int vbo, vao;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(.25, .25, .25, 1.);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);

		float tv = glfwGetTime();
		float green = sin(tv) / 2. + .5;
		int loc = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(loc, 0., green, 0, 1.);
		
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glfwTerminate();
	return EXIT_SUCCESS;
}
