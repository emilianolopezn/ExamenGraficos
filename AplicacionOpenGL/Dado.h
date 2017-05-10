#pragma once
#include "Modelo.h"
class Dado : public Modelo {
public:
	Dado();
	GLuint uvBufferID;
	vector<vec2> mapaUV;
	void dibujar(GLuint modeloID, GLuint conTexturaID, GLuint samplerImagenID, GLuint texturaID);
	void cargarVertexArrayBuffer(GLuint posicionID, GLuint colorID, GLuint uvID);
};