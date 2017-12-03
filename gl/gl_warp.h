#pragma once

#include <iostream>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

namespace {

	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	GLFWwindow* gl_warp_init() {
		if (!glfwInit()) {
			std::cerr << "Failed to init GLFW" << std::endl;
			exit(EXIT_FAILURE);
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
		if (window == NULL) {
			std::cerr << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cerr << "Failed to initialize GLAD" << std::endl;
			exit(EXIT_FAILURE);
		}
		return window;
	}

	int compile_vertex_shader(const char *src) {
		int compsucc;
		char infolog[BUFSIZ];
		int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &src, NULL);
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compsucc);
		if (!compsucc) {
			glGetShaderInfoLog(vertexShader, BUFSIZ, NULL, infolog);
			std::cerr << "Shader compilation failed: " << infolog << std::endl;
			exit(EXIT_FAILURE);
		}
		return vertexShader;
	}

	int compile_fragment_shader(const char *src) {
		int compsucc;
		char infolog[BUFSIZ];
		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &src, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compsucc);
		if (!compsucc) {
			glGetShaderInfoLog(fragmentShader, BUFSIZ, NULL, infolog);
			std::cerr << "Shader compilation failed: " << infolog << std::endl;
			exit(EXIT_FAILURE);
		}
		return fragmentShader;
	}

	void gl_warp_LinkProgram(int shaderProgram) {
		int lksucc;
		char infolog[BUFSIZ];
		glLinkProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &lksucc);
		if (!lksucc) {
			glGetProgramInfoLog(shaderProgram, BUFSIZ, NULL, infolog);
			exit(EXIT_FAILURE);
		}
	}

	int texture_init() {
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		return texture;
	}

	int texture_load(const char *path) {
		int texture = texture_init();
		int width, height, nrChannels;
		unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		} else {
			std::cerr << "Failed to load texture" << std::endl;
			exit(EXIT_FAILURE);
		}
		stbi_image_free(data);
		return texture;
	}

}; // end anonymous namespace
