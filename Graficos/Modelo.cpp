#include "stdafx.h"
#include "Modelo.h"

Modelo::Modelo() {
	modelo = mat4(1.0f);
}

void Modelo::inicializarVertexArray(GLuint posicionID, 
	GLuint colorID, GLuint modeloID, GLuint vistaID, GLuint proyeccionID) {

	this->modeloID = modeloID;
	this->vistaID = vistaID;
	this->proyeccionID = proyeccionID;
	
	//Crear un vertex array
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	//Crear vertex buffer
	glGenBuffers(1, &bufferID);
	//De aqui en adelante se trabja con este buffer
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	//Llenar el buffer
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(Vertice) * vertices.size(),
		vertices.data(), GL_STATIC_DRAW);

	//Habilitar el atributo solo en el vertex array en uso
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);
	
	//Especificar a OpenGL como usar la memoria con ese atributo
	glVertexAttribPointer(posicionID, 4, GL_FLOAT,
		GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE,
		sizeof(Vertice), (void*) sizeof(vec4));

	//Soltarlos
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Modelo::dibujar(GLenum modoDibujo) {
	shader->enlazarShader();
	glBindVertexArray(vertexArrayID);

	glUniformMatrix4fv(modeloID, 1,
		GL_FALSE, &modelo[0][0]);

	glUniformMatrix4fv(vistaID, 1, GL_FALSE, &vista[0][0]);
	glUniformMatrix4fv(proyeccionID, 1, GL_FALSE, &proyeccion[0][0]);


	glDrawArrays(modoDibujo, 0, vertices.size());
	glBindVertexArray(0);
	shader->desenlazarShader();
}