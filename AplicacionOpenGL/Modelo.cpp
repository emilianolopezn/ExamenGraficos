#include "stdafx.h"
#include "Modelo.h"

Modelo::Modelo() {
	modoDibujo = GL_POLYGON;
	posicion = vec3(0, 0, 0);
	escala = vec3(1, 1, 1);
	angulo = 0.0f;
	ejesRotacion = vec3(0, 0, 1);
}

mat4 Modelo::obtenerMatrizModelo() {
	modelo = mat4(1.0f);
	modelo = translate(modelo, posicion);
	modelo = rotate(modelo, angulo, ejesRotacion);
	modelo = scale(modelo, escala);
	return modelo;
}

void Modelo::cargarVertices(vector<Vertice> vertices) {
	this->vertices = vertices;
}

void Modelo::cargarVertexArrayBuffer(GLuint posicionID, GLuint colorID) {
	
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(Vertice)*vertices.size(),
		vertices.data(), GL_STATIC_DRAW);

	
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);
	
	glVertexAttribPointer(posicionID, 4, GL_FLOAT,
		GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT,
		GL_FALSE, sizeof(Vertice), (void *)sizeof(vec4));
}

void Modelo::dibujar(GLuint modeloID) {
	glUniformMatrix4fv(modeloID, 1, GL_FALSE,
		&(obtenerMatrizModelo()[0][0]));
	glBindVertexArray(vertexArrayID);
	glDrawArrays(modoDibujo, 0, vertices.size());
}