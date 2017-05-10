#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <vector>
#include "Vertice.h"
#include "Shader.h"
#include "Modelo.h"
#include "Dado.h"
#include <time.h>

using namespace std;
using namespace glm;

GLFWwindow *window;
Dado *dado;
Modelo *piso;
int numAsteroides = 0;

mat4 vista;
mat4 proyeccion;

vec3 posicionCamara;
float anguloCamara = 0.0f;

GLuint posicionID;
GLuint colorID;
GLuint uvID;
GLuint uniformInvertidoID;
GLuint modeloID;
GLuint vistaID;
GLuint proyeccionID;
GLuint conTexturaID;
GLuint coordenadaUVID;
GLuint samplerImagenID;

GLfloat ancho = 1024;
GLfloat alto = 768;

Shader * shader;

bool invertido = false;

GLuint texturaUnoID;

void moverCamara() {
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		anguloCamara += 0.8;
		if (anguloCamara > 360) anguloCamara = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		anguloCamara -= 0.8;
		if (anguloCamara < 0) anguloCamara = 360;
	}
	posicionCamara = vec3(sin(anguloCamara * 3.14159 / 180) * 3, 3, cos(anguloCamara * 3.14159 / 180) * 3);
	vista = lookAt(
		posicionCamara, 
		vec3(0, 0, 0), 
		vec3(0, 1, 0));

}

void actualizar() {
	moverCamara();
}

void dibujar() {
	shader->enlazarShader();
	glUniform1i(uniformInvertidoID, invertido);
	glUniform1i(conTexturaID, false);
	glUniformMatrix4fv(vistaID, 1, GL_FALSE,
		&(vista[0][0]));
	glUniformMatrix4fv(proyeccionID, 1, GL_FALSE,
		&(proyeccion[0][0]));
	piso->dibujar(modeloID);

	dado->dibujar(modeloID, conTexturaID, samplerImagenID, texturaUnoID);

	
	glBindVertexArray(0);
	
	shader->desenlazarShader();
}

void callbackTeclado(GLFWwindow * window, int key, int scancode, int action, int mods) {
	
}

int main()
{
	
	
	posicionCamara = vec3(0, 3, 3);
	vista = lookAt(
		posicionCamara, 
		vec3(0, 0, 0), 
		vec3(0,1,0)); 

	proyeccion = perspective(
		radians(90.0f),
		ancho / alto,
		0.1f,
		100.0f);

	piso = new Modelo;
	dado = new Dado;

	piso->vertices.push_back({ vec4(-6.0f,-1.0f,-6.0f,1.0f), vec4(1.0f,1.0f,1.0f,1.0f) });
	piso->vertices.push_back({ vec4(-6.0f,-1.0f,6.0f,1.0f), vec4(1.0f,1.0f,1.0f,1.0f) });
	piso->vertices.push_back({ vec4(6.0f,-1.0f,6.0f,1.0f), vec4(1.0f,1.0f,1.0f,1.0f) });
	piso->vertices.push_back({ vec4(6.0f,-1.0f,-6.0f,1.0f), vec4(1.0f,1.0f,1.0f,1.0f) });
	
	srand(time(NULL));

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(ancho, alto, "Mi ventana", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, callbackTeclado);
	glewExperimental = true; 
	
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	const GLubyte * version = glGetString(GL_VERSION);
	cout << version << endl;
	
	texturaUnoID = Shader::cargarBMP("estrella.bmp");



	
	const char * rutaVertex = "ShaderSimple.vertexshader";
	const char * rutaFragment = "ShaderSimple.fragmentshader";
	shader = new Shader(rutaVertex, rutaFragment);

	
	posicionID = glGetAttribLocation(shader->getID(), "posicion");
	colorID = glGetAttribLocation(shader->getID(), "color");
	uvID = glGetAttribLocation(shader->getID(), "coordenadaUV");
	uniformInvertidoID = 
		glGetUniformLocation(shader->getID(), "invertido");
	modeloID =
		glGetUniformLocation(shader->getID(), "modelo");
	vistaID =
		glGetUniformLocation(shader->getID(), "vista");
	proyeccionID =
		glGetUniformLocation(shader->getID(), "proyeccion");
	conTexturaID = 
		glGetUniformLocation(shader->getID(), "conTextura");
	samplerImagenID =
		glGetUniformLocation(shader->getID(), "samplerImagen");
	coordenadaUVID =
		glGetAttribLocation(shader->getID(), "coordenadaUV");

	shader->desenlazarShader(); 

	dado->cargarVertexArrayBuffer(posicionID, colorID, uvID);
	piso->cargarVertexArrayBuffer(posicionID, colorID);


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	while (!glfwWindowShouldClose(window)) {
		glViewport(0, 0, ancho, alto);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		actualizar();
		dibujar();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}

