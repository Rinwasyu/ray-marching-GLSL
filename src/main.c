/*
 * Copyright 2024 Rinwasyu
 * 
 * This file is part of ray-marching-GLSL.
 * 
 * Ray-marching-GLSL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Ray-marching-GLSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>

char *loadFile(char *file_name, size_t *allocated_size) {
	FILE *fp = fopen(file_name, "rb");
	if (fp == NULL) {
		printf("can't open file: %s\n", file_name);
		return NULL;
	}
	
	struct stat stat_buf;
	stat(file_name, &stat_buf);
	
	char *text = (char *)malloc(sizeof(char) * (stat_buf.st_size + 1));
	if (text == NULL)
		return NULL;
	memset(text, 0, sizeof(char) * (stat_buf.st_size + 1));
	fread(text, sizeof(char) * (stat_buf.st_size), 1, fp);
	fclose(fp);
	
	if (allocated_size)
		*allocated_size = stat_buf.st_size + 1;
	return text;
}

void printCompilerInfoLog(GLuint shader) {
	GLchar *info_log;
	GLsizei buf_size, length;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &buf_size);
	info_log = (GLchar *)malloc(buf_size);
	memset(info_log, 0, buf_size);
	glGetShaderInfoLog(shader, buf_size, &length, info_log);
	fprintf(stderr, "log: %s\n", info_log);
}

GLuint createProgram() {
	GLuint program = glCreateProgram();
	
	char *vertex_shader_src = loadFile("shader.vert", NULL);
	if (vertex_shader_src != NULL) {
		GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, (const char **)&vertex_shader_src, NULL);
		glCompileShader(vertex_shader);
		printCompilerInfoLog(vertex_shader);
		glAttachShader(program, vertex_shader);
		glDeleteShader(vertex_shader);
	}
	
	char *fragment_shader_src = loadFile("shader.frag", NULL);
	if (fragment_shader_src != NULL) {
		GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, (const char **)&fragment_shader_src, NULL);
		glCompileShader(fragment_shader);
		printCompilerInfoLog(fragment_shader);
		glAttachShader(program, fragment_shader);
		glDeleteShader(fragment_shader);
	}
	
	glLinkProgram(program);
	
	return program;
}

int main(void) {
	if (!glfwInit())
		return EXIT_FAILURE;
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow *window = glfwCreateWindow(900, 900, "ray-marching-GLSL", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return EXIT_FAILURE;
	}
	
	glfwMakeContextCurrent(window);
	
	glewInit();
	
	GLfloat vertices[] = {
		-1, -1, 0, 1.0,
		1, -1, 0, 1.0,
		-1, 1, 0, 1.0,
		-1, 1, 0, 1.0,
		1, -1, 0, 1.0,
		1, 1, 0, 1.0
	};
	
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	
	GLuint vertex_vbo;
	glGenBuffers(1, &vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
	
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	GLuint program = createProgram();
	glUseProgram(program);
	
	glBindVertexArray(vao);
	
	GLint ray_vector_location = glGetUniformLocation(program, "ray_vector");
	int frame = 0;
	
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(vao);
		glUniform3f(ray_vector_location, cos((float)frame/100), 0, sin((float)frame/100));
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwSwapBuffers(window);
		glfwPollEvents();
		frame++;
	}
	
	glfwTerminate();
	
	return EXIT_SUCCESS;
}