#pragma once

#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Vertice.h"
#include <vector>

using namespace glm;
using namespace std;

class Modelo {
public:
	Modelo();
	GLuint modoDibujo;
	vector<Vertice> vertices;
	GLuint vertexArrayID;
	GLuint bufferID;
	bool conTextura = false;

	vec3 posicion;
	vec3 escala;
	float angulo;
	vec3 ejesRotacion;

	mat4 obtenerMatrizModelo();

	void cargarVertices(vector<Vertice> vertices);
	void cargarVertexArrayBuffer(GLuint posicionID, GLuint colorID);
	void dibujar(GLuint modeloID);
private:
	mat4 modelo;
};