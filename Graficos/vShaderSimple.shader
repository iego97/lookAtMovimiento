#version 330 core
//La primera linea es la version

//Atributos de entrada
layout(location = 0) in vec4 posicion;
in vec4 color;
uniform mat4 modelo;
uniform mat4 vista;
uniform mat4 proyeccion;

//Atributos de salida
out vec4 fragmentColor;



//Funcion main
void main() {


	//CREAR MATRIZ MVP
	mat4 MVP = proyeccion * vista * modelo;

	//La posicion de salida del vertice
	//Se guarda en gl_Position (vec4)
	gl_Position = MVP * posicion;

	//Establecer valor de fragmentColor
	fragmentColor = color;
}

